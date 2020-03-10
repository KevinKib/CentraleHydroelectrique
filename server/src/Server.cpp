/** System/libs imports **/

/** Local imports**/
#include "../includes/Server.h"

// ----- Constructors
hc::Server::Server ( )
    : ip ( "" ), port ( 0 )
{ }

hc::Server::Server ( const string _ip, const ushort _port )
    : ip ( _ip ), port ( _port )
{ }

hc::Server::Server ( const Server & server )
    : ip ( server.ip ), port ( server.port )
{ }

hc::Server::~Server ( )
{ }