/** System/libs imports **/

/** Local imports**/
#include "../includes/Server.h"

// ----- Constructors
Server::Server ( const string ip, const ushort port )
    : ip ( ip ), port ( port )
{ }

Server::Server ( const Server & server )
    : ip ( server.ip ), port ( server.port )
{ }

// ------ Methods
JSON Server::toJSON ( ) const
{
    JSON json;
    json["ip"] = ip;
    json["port"] = port;

    return json;
}