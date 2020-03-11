/**
 * The module <JSONParsable.h> is an abstract class to represent
 * a class that can be parse in json
 **/

/** System includes **/
#include <string>
#include <map>

/** Personnal includes **/
#include "typedefs.h"
#include "JSONParsable.h"

using namespace std;

#ifndef DATA_MODULE_H
#define DATA_MODULE_H

class DataModule
{
    public:
    // ----- Constructors

    /**
     * Default constructor
     **/
    DataModule ( );

    /**
     * Get the data according to a range.
     * @param begin The begin of the range
     * @param end The end of the range
     * @return The JSON data according to the range
     **/
    JSON GetDataByRange ( int begin, int end, string attribute ) const;

    private:
    // ----- Methods
    /**
     * Parse the data from the file.
     * @param fileContent The content of the file to parse
     **/
    void parseData ( string fileContent );

    static const string DATA_PATH;

    unordered_map<string, JSON> data;
};

#endif