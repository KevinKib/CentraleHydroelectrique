/** System/libs imports **/

/** Local imports**/
#include "../includes/TCPServer.h"

// ----- Constructors
TCPServer::TCPServer ( string data )
    : Server (  "", 0 ),
    attribute ( "" ),
    type ( "" ),
    frequency ( 0.0f ),
    isConnected ( false ),
    protocol ( TCPProtocol::PULL )
{
    // TODO
}

TCPServer::TCPServer ( const TCPServer & server )
    : Server ( server.ip, server.port ), attribute ( server.attribute ),
    type ( server.type ), frequency ( server.frequency ),
    isConnected ( server.isConnected ), protocol ( server.protocol )
{ }