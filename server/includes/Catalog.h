/**
 * The class <Catalog> represents the list of the TCP servers.
 **/

#ifndef CATALOG_H
#define CATALOG_H

/** System imports **/
#include <string>
#include <map>

/** Local imports **/
#include "typedefs.h"
#include "TCPServer.h"

using namespace std;

using ServerList = unordered_map<IDHydrolic, 
                   unordered_map<Attribute, 
                   unordered_map<IDTurbine, 
                   unordered_map<TCPProtocol, TCPServer>>>>; 

class Catalog
{
    public:
    // ----- Constructors

    /**
     * Constructor of the Catalog
     * @param catalogContent The content of the catalog
     **/
    Catalog ( string catalogContent );

    /**
     * Constructor of the copy of the class Catalog
     **/
    Catalog ( const Catalog & catalog );

    private:
    // ---- Methods

    /**
     * Parse the catalog from a string
     * @param catalogContent The catalog into a string
     **/
    void parseCatalog ( string catalogContent );

    // ---- Attributes
    ServerList serverList;
    
};

#endif