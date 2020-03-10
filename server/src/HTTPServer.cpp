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
const ushort HTTPServer::SERVER_PORT = 8080;
const string HTTPServer::SERVER_IP = "localhost";

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
void HTTPServer::hydraulicsRoute ( const httplib::Request &req, httplib::Response &res )
{
    res.set_content ( catalog.GetHydraulics ( ).dump ( ), "application/json" );
}

void HTTPServer::turbinesByCentralRoute ( const httplib::Request & req, httplib::Response res )
{
    // retrieve the params of central
    IDHydraulic hydraulic = req.matches[1];

    JSON result = catalog.GetTurbinesByHydraulicName ( hydraulic );

    cout << result.dump ( ) << endl;
    res.set_content ( result.dump ( ), "application/json" );
}

void HTTPServer::configurateRoutes()
{    
    Get ( "/hydraulics", [this](const httplib::Request &req, httplib::Response &res) { return hydraulicsRoute ( req, res ); } );
    Get ( R"(/turbines/((\w[-']?)+))", [this](const httplib::Request &req, httplib::Response &res) { return turbinesByCentralRoute ( req, res ); }  );
}

void HTTPServer::Run ( )
{
    cout << "Server running with " << HTTPServer::SERVER_IP << ":" << HTTPServer::SERVER_PORT << endl;

    listen ( HTTPServer::SERVER_IP.c_str(), HTTPServer::SERVER_PORT );
}