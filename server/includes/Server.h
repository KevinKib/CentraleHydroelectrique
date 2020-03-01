/**
 * The module <Server.h> represents the set of data describing a server 
 **/

#ifndef SERVER_H
#define SERVER_H

/** Includes system/libs **/
#include <string>
#include <iostream>

/** Personnal includes **/
#include "typedefs.h"
#include "JSONParsable.h"

using namespace std;

class Server
{   
    public:
    // ----- Constructors

    /**
     * Constructor of the class Server
     * @param ip The ip describing the server
     * @param port The port describing the server
     **/
    Server ( const string ip, const ushort port );

    /**
     * Constructor of copy of the class Server
     * @param server The server for the copy
     **/
    Server ( const Server & server );

    // ----- Operators

    /**
     * Method for the print of the Server
     * @param out The stream to print the server
     * @param server The server to print
     * @return The current stream
     **/
    friend ostream & operator << ( ostream & out, const Server & server )
    {
        out << "Ip : " << server.ip << ", port : " << server.port << endl;
        return out;
    }

    // -------- Attributes
    const string ip;
    const ushort port;
         
};

#endif