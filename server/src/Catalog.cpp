/** System imports **/
#include <sstream>

/** Local imports **/
#include "../includes/Catalog.h"

// ----- Constructors
Catalog::Catalog ( string catalogContent )
{
    parseCatalog ( catalogContent );
}

Catalog::Catalog ( const Catalog & catalog )
    : serverList ( catalog.serverList )
{ }

// ----- Methods
void Catalog::parseCatalog ( string catalogContent )
{
    int count ( 0 );
    string buffer;

    // skip the first two lines
    stringstream stream ( catalogContent );

    while ( getline ( stream, buffer, '\n') )
    {
        if ( count >= 2 )
        {
            // parse the current line
            TCPServer tcpServer = TCPServer::fromString ( buffer );
            serverList[tcpServer.central][tcpServer.attribute][tcpServer.turbine].emplace ( tcpServer.protocol, tcpServer );
        }

        ++count;
    }
}