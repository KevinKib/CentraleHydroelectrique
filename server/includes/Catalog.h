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
#include "JSONParsable.h"

using namespace std;

using ServerList = unordered_map<IDHydraulic, 
                   unordered_map<Attribute, 
                   unordered_map<IDTurbine, 
                   unordered_map<TCPProtocol, TCPServer>>>>; 

class Catalog : public JSONParsable
{
    public:
    // ----- Constructors

    /**
     * default constructor of the class Catalog
     **/
    Catalog ( );

    /**
     * Constructor of the Catalog
     * @param catalogContent The content of the catalog
     **/
    Catalog ( string catalogContent );

    /**
     * Constructor of the copy of the class Catalog
     **/
    Catalog ( const Catalog & catalog );

    // ----- Operators

    /**
     * Overload the operator =
     * @param catalog The catalog to copy
     * @return The current catalog
     **/
    inline Catalog & operator = ( const Catalog & catalog )
    {
        serverList = catalog.serverList;
        return *this;
    }

    // ----- Methods
    
    // @Override
    virtual JSON toJSON ( ) const;

    /**
     * Get all names of the hydraulics in a JSON array.
     * @return A JSON array with all names
     */
    virtual JSON GetHydraulics ( ) const;

    /**
     * Get the information of all turbins by an hydraulic name
     * @param hydraulicName The name of the hydrolic
     * @return A JSON array with information of each turbine
     **/
    virtual JSON GetTurbinesByHydraulicName ( string hydraulicName );

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