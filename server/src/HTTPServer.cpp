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

    cout << catalog.toJSON () << endl;
}

HTTPServer::~HTTPServer()
{ }

// ----- Methods

void HTTPServer::catalogRoute ( const httplib::Request &req, httplib::Response &res )
{
    res.set_content ( catalog.toJSON ( ).dump ( ), "application/json" );
}

void HTTPServer::configurateRoutes()
{    
    Get ( "/catalog", [this](const httplib::Request &req, httplib::Response &res) { return catalogRoute(req, res); } );
}

void HTTPServer::Run ( )
{
    cout << "Server running with " << HTTPServer::SERVER_IP << ":" << HTTPServer::SERVER_PORT << endl;

    listen ( HTTPServer::SERVER_IP.c_str(), HTTPServer::SERVER_PORT );
}