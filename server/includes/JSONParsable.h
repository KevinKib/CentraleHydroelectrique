/**
 * The module <JSONParsable.h> is an abstract class to represent
 * a class that can be parse in json
 **/

/** Personnal includes **/
#include "typedefs.h"

using namespace std;

#ifndef JSON_PARSABLE_H
#define JSON_PARSABLE_H

class JSONParsable
{
    public:
    // ----- Constructors

    /**
     * Default constructor of the class JSONParsable
     **/
    inline JSONParsable ( ) 
    { }

    /**
     * Method that parse an object in JSON
     * @return The representation in JSON of the current object
     **/
    virtual JSON toJSON ( ) const = 0;
};

#endif