/** System imports **/
#include <iostream>
#include <fstream>
#include <sstream>

/** Local imports **/
#include "../includes/FileReader.h"

// ----- Methods
string FileReader::ReadFile ( string filename )
{
    ifstream infile ( filename, ifstream::binary );
    if ( !infile )
    {
        // erreur d'ouverture
        cerr << "Error during the opening of the file " << filename << "." << endl;
        return "";
    }

    stringstream buffer;
    if( ! ( buffer << infile.rdbuf ( ) ) )
    {
        cerr << "Error during reading in the file " << filename << "." << endl;
        infile.close ( );
        return "";
    }

    infile.close ( );

    return buffer.str ( );
}