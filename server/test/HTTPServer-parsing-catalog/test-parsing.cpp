#include "../../includes/HTTPServer.h"
#include "../../libs/http/httplib.h"

#include <iostream>
#include <string>

using namespace std;

bool testParsingCatalogWhenServerConnected()
{
    try {
        HTTPServer s;
        return true;
    } catch(string err)
    {
        return false;
    }
}

bool testParsingCatalogWhenServerDisconnected()
{
    try {
        HTTPServer s;
        return false;
    } catch(string err)
    {
        return true;
    }
}

int main(int argc, const char **argv)
{
    if ( ! testParsingCatalogWhenServerConnected ( ) )
    {
        cerr << "The parsing of catalog when the server is connected has failed !" << endl;
        return 1;
    }

    cout << "All tests are passed" << endl;

    return 0;
}