/**
 * The module <HTTPServer.h> is the main class of the server.
 * It represents the server himself.
 **/

/** System/libs imports **/
#include <string>

/** Personnal includes **/
#include "typedefs.h"
#include "Server.h"

using namespace std;

#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

class HTTPServer
{
    public:
    // ----- Constructors - Destructor

    /**
     * Default consructor of the class HTTPServer
     **/
    HTTPServer ( );

    /**
     * Destructor of the class HTPPServer
     **/
    virtual ~HTTPServer ( );

    // ----- Methods

    private:
    static const string CONFIG_FILENAME;

    const Server catalogServer;

    // ----- Methods
    
    /**
     * Method to configurate the routes for the server to retrieve data.
     **/
    void configurateRoutes ( );

    /**
     * Method to retrieve the content of the server's catalog.
     **/
    string receiveCatalogContent ( );
};

#endif