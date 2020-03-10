/**
 * The module <HTTPServer.h> is the main class of the server.
 * It represents the server himself.
 **/

/** System/libs imports **/
#include <string>
#include "../libs/http/httplib.h"

/** Personnal includes **/
#include "typedefs.h"
#include "Server.h"
#include "Catalog.h"

#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

class HTTPServer: public httplib::Server
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

    /**
     * Run the server.
     **/
    void Run ( );

    private:
    // ----- Attributes
    static const string CONFIG_FILENAME;
    static const string SERVER_IP;
    static const ushort SERVER_PORT;

    hc::Server catalogServer;

    Catalog catalog;

    // ----- Methods for the routes

    /**
     * Method to configurate the routes for the server to retrieve data.
     **/
    void configurateRoutes ( );

    /**
     * Method to retrieve the content of the server's catalog.
     * @return The content of the catalog.
     **/
    string receiveCatalogContent ( );
};

#endif