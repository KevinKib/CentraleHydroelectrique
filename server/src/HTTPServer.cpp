/** System/libs imports **/
#include <string>
#include <iostream>
#include "../libs/json/single_include/nlohmann/json.hpp"

/** Local imports**/
#include "../includes/HTTPServer.h"
#include "../includes/FileReader.h"

using namespace std;

// ------ Static properties
const string HTTPServer::CONFIG_FILENAME = "server.config.json";
const ushort HTTPServer::SERVER_PORT = 8082;
const string HTTPServer::SERVER_IP = "127.0.0.1";

// ----- Constructors
HTTPServer::HTTPServer()
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

// ----- Routes
void HTTPServer::configurateRoutes()
{    
    Get ( "/hydraulics", [&](const httplib::Request &req, httplib::Response &res)
    { 
        res.set_content ( catalog.GetHydraulics ( ).dump ( ), "application/json" );
    } );


    Get ( "/historic-data",
        [&](const httplib::Request &req, httplib::Response &res)
        { 
            JSON result;
        // retrieve the central, turbine, attribute and date
        auto centralIterator = req.params.find ( "centralID" );
        auto turbineIterator = req.params.find ( "turbineID" );
        auto attributeIterator = req.params.find ( "attribute" );
        auto dateIterator = req.params.find ( "date" );

        if (centralIterator == req.params.end ( ) || 
            turbineIterator == req.params.end ( ) ||
            attributeIterator == req.params.end ( ) ||
            dateIterator == req.params.end (  ) )
            {
                // error in the params of the request
                result["content"] = "Error with the parameters of the request at the path " + req.path; 
                res.status = 403;
                res.set_content ( result.dump ( ), "application/json" );
            }
        } 
    );
}

void HTTPServer::Run ( )
{
    cout << "Server running with " << HTTPServer::SERVER_IP << ":" << HTTPServer::SERVER_PORT << endl;

    listen ( HTTPServer::SERVER_IP.c_str(), HTTPServer::SERVER_PORT );
}