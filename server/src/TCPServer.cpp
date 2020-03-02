/** System/libs imports **/

/** Local imports**/
#include "../includes/TCPServer.h"

// ------ Static properties
const string TCPServer::TCP_PULL_STRING = "TCP_PULL";
const string TCPServer::TCP_PUSH_STRING = "TCP_PUSH";

// ----- Constructors
TCPServer::TCPServer ( string ip, ushort port, uint _id, string _attribute, string _type, float _frequency, TCPProtocol _protocol, string _central, string _turbine )
    : Server ( ip, port ),
    attribute ( _attribute ),
    type ( _type ),
    frequency ( _frequency ),
    id ( _id ),
    isConnected ( false ),
    protocol ( _protocol ),
    central ( _central ),
    turbine ( _turbine )
{
    // TODO
}

TCPServer::TCPServer ( const TCPServer & server )
    : Server ( server.ip, server.port ), attribute ( server.attribute ),
    type ( server.type ), frequency ( server.frequency ),
    id ( server.id ), isConnected ( server.isConnected ), 
    protocol ( server.protocol ), central ( server.central ),
    turbine ( server.turbine )
{ }

TCPServer TCPServer::fromString ( string data )
{
    string::size_type index;
    string buffer, central, turbine, attribute, type, ip;
    uint id;
    ushort port;
    TCPProtocol protocol;
    float frequency;

    // stream id parsing
    index = data.find_first_of ( "=" ) + 1;
    data = data.substr ( index );
    index = data.find_first_of ( " " );
    buffer = data.substr ( 0, index );
    id = stoul ( buffer, nullptr, 0 );

    // group parsing
    index = data.find_first_of ( "=" ) + 1;
    data = data.substr ( index );

    // exemple : Avignon.Groupe1
    if ( data[0] != ' '  )
    {
        index = data.find_first_of ( "." );
        central = data.substr ( 0, index );
        data = data.substr ( index + 1 );
        index = data.find_first_of ( " " );
        turbine = data.substr ( 0, index - 1);
    } else 
    {
        data = data.substr ( 1 );
        index = data.find_first_of ( " " );
        central = data.substr ( 0, index  );
        turbine = "*";
    }

    // attribute
    index = data.find_first_of ( "=" ) + 1;
    data = data.substr ( index );
    index = data.find_first_of ( " " );
    attribute = data.substr ( 0, index );
    data = data.substr ( index );


    // type
    index = data.find_first_of ( "=" ) + 1;
    data = data.substr ( index );
    index = data.find_first_of ( " " );
    type = data.substr ( 0, index );
    data = data.substr ( index );

    // adress parsing
    index = data.find_first_of ( "=" ) + 1;
    data = data.substr ( index );
    index = data.find_first_of ( " " );
    ip = data.substr ( 0, index );
    data = data.substr ( index );

    // port parsing
    index = data.find_first_of ( "=" ) + 1;
    data = data.substr ( index );
    index = data.find_first_of ( " " );
    buffer = data.substr ( 0, index );
    port = ( ushort ) stoul ( buffer, nullptr, 0 );
    data = data.substr ( index );

    // protocol parsing
    index = data.find_first_of ( "=" ) + 1;
    data = data.substr ( index );
    index = data.find_first_of ( " " );
    buffer = data.substr ( 0, index );
    if (buffer == TCPServer::TCP_PULL_STRING)
    {
        protocol = TCPProtocol::PULL;
    } else if (buffer == TCPServer::TCP_PUSH_STRING)
    {
        protocol = TCPProtocol::PUSH;
    }

    data = data.substr ( index );

    // frequency parsing
    index = data.find_first_of ( "=" ) + 1;
    data = data.substr ( index );
    index = data.find_first_of ( " " );
    buffer = data.substr ( 0, index );
    frequency = stof ( buffer, nullptr );

    return TCPServer ( ip, port, id, attribute, type, frequency, protocol, central, turbine );
}