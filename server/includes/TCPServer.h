/**
 * The module <TCPServer.h> represents the set of data describing 
 * a TCP server 
 **/

#ifndef TCP_SERVER_H
#define TCP_SERVER_H

/** Includes system/libs **/
#include <string>
#include <iostream>

/** Personnal includes **/
#include "typedefs.h"
#include "Server.h"

using namespace std;

enum TCPProtocol { PUSH, PULL };

class TCPServer: public Server
{
    public:
    // ----- Constructors

    /**
     * Constructor of the class TCPServer
     * @param data The raw data for the creation of TCPServer
     **/
    TCPServer ( string data );

    /**
     * Constructor of copy of the class TCPServer
     * @param tcpServer The TCP server for the copy
     **/
    TCPServer ( const TCPServer & tcpServer );

    // ----- Operators
    
    /**
     * Method for the print of the TCPServer
     * @param out The stream to print the server
     * @param server The server to print
     * @return The current stream
     **/
    friend ostream & operator << ( ostream & out, const TCPServer & server )
    {
        out 
            << "Ip : " << server.ip 
            << ", port : " << server.port
            << ", attribute : " << server.attribute 
            << ", type : " << server.type
            << ", frequency : " << server.frequency
            << ", is connected : " << server.isConnected
            << ", protocol : " << server.protocol
            << endl;
        return out;
    }

    // ----- Methods
    virtual JSON toJSON ( ) const;

    // ----- Attributes
    const string attribute;
    const string type;
    const float frequency;
    bool isConnected;
    const TCPProtocol protocol;
};

#endif