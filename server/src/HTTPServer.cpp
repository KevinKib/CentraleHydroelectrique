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
}

HTTPServer::~HTTPServer()
{ }

// ----- Methods
void HTTPServer::configurateRoutes()
{
    Get(R"(/numbers/(\d+))", [](const httplib::Request &req, httplib::Response &res) {
        cout << req.matches[1] << endl;
        res.set_content("Hello World!", "text/plain");
    });
}

void HTTPServer::Run ( )
{
    cout << "Server running with localhost:8080" << endl;

    listen ( "localhost", 8080 );
}