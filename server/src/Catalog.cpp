/** System imports **/
#include <sstream>

/** Local imports **/
#include "../includes/Catalog.h"

// ----- Constructors
Catalog::Catalog ( )
    : serverList ( )
{ }

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
            if ( buffer.length ( ) > 1 )
            {
                TCPServer tcpServer = TCPServer::fromString ( buffer );
                serverList[tcpServer.central][tcpServer.attribute][tcpServer.turbine].emplace ( tcpServer.protocol, tcpServer );
            }
        }

        ++count;
    }
}

JSON Catalog::toJSON ( ) const
{
    JSON json, attributesJSON, turbinesJSON, turbineJSON;
    IDHydrolic central;
    Attribute attribute;
    IDTurbine turbine;

    for (pair<IDHydrolic, unordered_map<Attribute, unordered_map<IDTurbine, unordered_map<TCPProtocol, TCPServer>>>> centralPair : serverList )
    {
        // central -> attribute -> turbins[]
        central = centralPair.first;
        unordered_map<Attribute, unordered_map<IDTurbine, unordered_map<TCPProtocol, TCPServer>>> attributeMap = centralPair.second;

        for (pair<Attribute, unordered_map<IDTurbine, unordered_map<TCPProtocol, TCPServer>>> attributePair : attributeMap )
        {
            // attribute
            attribute = attributePair.first;
            unordered_map<IDTurbine, unordered_map<TCPProtocol, TCPServer>> turbineMap = attributePair.second;

            for (pair<IDTurbine, unordered_map<TCPProtocol, TCPServer>> turbinePair : turbineMap )
            {
                // turbine
                turbine = turbinePair.first;
                turbinesJSON = JSON ( );

                unordered_map<TCPProtocol, TCPServer> serverMap = turbinePair.second;
    
                for (pair<TCPProtocol, TCPServer> serverPair : serverMap )
                {
                    TCPServer tcpServer = serverPair.second;
                    turbineJSON = JSON ( );
                    turbineJSON["type"] = tcpServer.type;
                    turbineJSON["frequency"] = tcpServer.frequency;

                    turbinesJSON[turbine] = turbineJSON;
                }
            }

            attributesJSON[attribute] = turbinesJSON;
        }

        json[central] = attributesJSON;
    }

    return json;
}