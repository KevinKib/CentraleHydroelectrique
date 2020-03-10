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

enum TCPProtocol { PUSH, PULL, INVALID };

class TCPServer: public hc::Server
{
    public:
    // ----- Constructors

    // Default constructor
    TCPServer ( );
    /**
     * Constructor of the class TCPServer
     * @param ip The ip of the server
     * @param port The port of the server
     * @param attribute The attribute for the server
     * @param type The type for the server
     * @param frequency The frequency for the server
     **/
    TCPServer ( string ip, ushort port, uint id, string attribute, string type, float frequency, TCPProtocol protocol, string central, string turbine );

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
            << "Stream ID=" << server.id
            << " group=" << server.central << "." << server.turbine
            << " attribute=" << server.attribute
            << " type=" << server.type
            << " address=" << server.ip
            << " port=" << server.port
            << " protocol=" << server.protocol
            << " frequency=" << server.frequency
            << endl;
        return out;
    }

    /**
     * Create a TCPServer from a raw string.
     * @param data The raw data
     * @return The TCPServer according to the data
     **/
    static TCPServer fromString ( string data );

    // ----- Attributes
    const string attribute;
    const string type;
    const float frequency;
    const uint id;
    bool isConnected;
    const TCPProtocol protocol;
    const string central;
    const string turbine;

    // static attributes
    static const string TCP_PULL_STRING;
    static const string TCP_PUSH_STRING; 
};

#endif