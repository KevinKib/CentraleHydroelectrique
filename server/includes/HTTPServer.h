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
     * The function called for the request at the url "/hydraulics"
     * @param req The current request
     * @param res The final result for the request
     **/
    void hydraulicsRoute ( const httplib::Request &req, httplib::Response &res );

    /**
     * The function called for the request at the url "/turbines{centralID}"
     * @param req The current request
     * @param res The final result for the request
     **/
    void turbinesByCentralRoute ( const httplib::Request & req, httplib::Response res );

    /**
     * The function called for the request at the url "/historic-data/{centralID}/{turbineID}/{attribute}/{date}"
     * The request must have four parameters : centralID, turbineID, attribute, date
     * @param req The current request
     * @param res The final result for the request
     **/
    void historicDataRoute ( const httplib::Request & req, httplib::Response res );

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