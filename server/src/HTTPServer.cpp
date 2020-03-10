/** System/libs imports **/
#include <string>
#include <iostream>
#include <utility>

#include "../libs/json/single_include/nlohmann/json.hpp"

/** Local imports**/
#include "../includes/HTTPServer.h"
#include "../includes/FileReader.h"

using namespace std;

// ------ Static properties
const string HTTPServer::CONFIG_FILENAME = "server.config.json";
const ushort HTTPServer::SERVER_PORT = 8070;
const string HTTPServer::SERVER_IP = "127.0.0.1";

// ----- Constructors
HTTPServer::HTTPServer()
    : tcp ( )
{
    // read the config file
    string data = FileReader::ReadFile ( HTTPServer::CONFIG_FILENAME );
    if ( data.empty ( ) )
    {
        throw runtime_error("Error during the reading of the config file " + HTTPServer::CONFIG_FILENAME);
    }

    JSON config = JSON::parse(data);

    catalogServer = hc::Server( config["ip"].get<string>( ), config["port"].get<ushort>( ) );

    configurateRoutes ( );

    // retrieve the catalog content
    httplib::Client client ( catalogServer.ip, catalogServer.port );
    auto get = client.Get("/");

    if (!get)
    {
        throw runtime_error("Error during the retrieving of catalog");
    }

    string catalogContent = get->body;
    catalog = Catalog ( catalogContent );
}

HTTPServer::~HTTPServer()
{ }

// ----- Methods

TCPResponse HTTPServer::proceedDataRequest ( const httplib::Request &req, TCPProtocol protocol ) const
{
    TCPResponse response;
    // retrieve the central, turbine, attribute and date
    auto centralIterator = req.params.find ( "hydraulic" );
    auto turbineIterator = req.params.find ( "turbine" );
    auto attributeIterator = req.params.find ( "attribute" );
    auto dateIterator = req.params.find ( "date" );


    if (centralIterator == req.params.end ( ) || 
        turbineIterator == req.params.end ( ) ||
        attributeIterator == req.params.end ( ) ||
        dateIterator == req.params.end (  ) )
    {
        // error in the params of the request
        response.second = "Error with the parameters of the request at the path " + req.path; 
        response.first = false;
        return response;
    }

    string hydraulic = centralIterator->second;
    string turbine = turbineIterator->second;
    string attribute = attributeIterator->second;
    string date = dateIterator->second;


    // retrieve the server with the given parameters
    pair<TCPServer, bool> tcpServerResult = catalog.GetTCPServer ( hydraulic, turbine, attribute, protocol );
    if ( ! tcpServerResult.second )
    {
        response.second = "Error during the retrieving of the TCPServer with your params. Please verify your params";
        response.first = false;
        return response;
    }

    // temporary
    response.first = true;
    response.second = "Success";

    return response;
}


// ----- Routes
void HTTPServer::configurateRoutes()
{    
    Get ( "/hydraulics", [&](const httplib::Request &req, httplib::Response &res)
    { 
        res.set_content ( catalog.GetHydraulics ( ).dump ( ), "application/json" );
        res.set_header ( "Access-Control-Allow-Origin", "*" );
    } );

    /**
     * Waiting params : {
     *      hydraulic: string,
     *      turbine: string,
     *      attribute: string,
     *      date: uint
     * }
     * 
     **/
    Get ( "/historic-data",
        [&](const httplib::Request &req, httplib::Response &res)
        { 
            JSON result;

            TCPResponse response = proceedDataRequest ( req, TCPProtocol::PUSH );

            result["success"] = response.first;
            result["content"] = response.second;
            res.set_content ( result.dump ( ), "application/json" );
            res.set_header ( "Access-Control-Allow-Origin", "*" );
        }
    );

    Get ( "current-data", 
        [&](const httplib::Request &req, httplib::Response &res)
        {
            JSON result;

            TCPResponse response = proceedDataRequest ( req, TCPProtocol::PULL );

            result["success"] = response.first;
            result["content"] = response.second;

            res.set_content ( result.dump ( ), "application/json" );
            res.set_header ( "Access-Control-Allow-Origin", "*" );
        }
    );
}

void HTTPServer::Run ( )
{
    cout << "Server running with " << HTTPServer::SERVER_IP << ":" << HTTPServer::SERVER_PORT << endl;

    listen ( HTTPServer::SERVER_IP.c_str(), HTTPServer::SERVER_PORT );
}