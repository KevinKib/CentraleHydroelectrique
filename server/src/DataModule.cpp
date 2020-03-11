/** System/libs imports **/
#include <sstream>
#include <vector>
#include <iostream>

/** Local imports**/
#include "../includes/DataModule.h"
#include "../includes/FileReader.h"

// ------ Static properties
const string DataModule::DATA_PATH = "./rsc/data.csv";

// ----- Constructor
DataModule::DataModule ( )
    : data ( )
{
    // recover the test data from the CSV file
    string fileContent = FileReader::ReadFile ( DataModule::DATA_PATH );
    parseData ( fileContent );
}

void DataModule::parseData ( string fileContent )
{
    uint lineCount = 0x0, column = 0x0;
    vector<string> fields; // stroe all of the field stored in the file

    string line, currentValue;
    JSON array;

    stringstream stream ( fileContent );

    while ( getline ( stream, line, '\n' ) ) 
    {
        stringstream lineStream ( line );
        column = 0x0;

        while ( getline ( lineStream, currentValue, ';' ) )
        {
            if ( lineCount == 0 )
            {
                // the first line of the file, fields 
                fields.push_back ( currentValue );
                data[currentValue] = JSON::array ( );
            } else
            {
                string field = fields[column];
                if ( column == 0)
                {
                    // timestamp
                    uint timestamp = (uint)stoul(currentValue, nullptr, 0);
                    data[field].push_back(timestamp);
                } else
                {
                    // other data
                    float rawData = atof(currentValue.c_str());
                    data[field].push_back(rawData);
                }
            }
            
            ++column;
        }

        ++lineCount;
    }
}

JSON DataModule::GetDataByRange ( int begin, int end, string attribute ) const
{
    JSON json, array;

    // error in the range
    if ( begin < 0 || begin > end )
    {
        return json;
    }

    for ( pair<string, JSON> rawData : data )
    {
        array = JSON::array ( );
        JSON currentFieldData = rawData.second;

        // recover the data from current json object
        for ( int i = begin; i < end; ++i )
        {
            array.push_back ( currentFieldData[i] );
        }

        json[rawData.first] = array;
    }

    return json;
}