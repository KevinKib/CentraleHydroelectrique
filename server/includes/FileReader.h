/**
 * The class <FileReader> is an util class to read files.
 **/

#ifndef FILE_READER_H
#define FILE_READER_H

/** System imports **/
#include <string>

using namespace std;

class FileReader
{  
    public:

    // ----- Methods
    
    /**
     * Read a file and return the content of it.
     * @param filename The path of the file
     * @return The content of the file
     **/
    static string ReadFile ( string filename ); 
};

#endif