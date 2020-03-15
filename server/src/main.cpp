#include <iostream>

#include "../includes/HTTPServer.h"
#include "../includes/TCPServer.h"
#include "../includes/TCPModule.h"
#include "../includes/Catalog.h"

using namespace std;

bool testTCPModule() {
    TCPServer avignon_pull("127.0.0.1", 11113, 1, "attribute", "type", 0.1, PULL, "centrale", "turbine");
    TCPServer avignon_push("127.0.0.1", 8088,  1, "attribute", "type", 0.1, PUSH, "centrale", "turbine");

    try {
        TCPModule tcpModule;
        JSON json = tcpModule.MakeRequest(nullptr, avignon_pull);
    }
    catch (const string & e) {
        cerr << "Error : " << e << endl;
        return false;
    }

    return true;
}

void testHTTPServer() {
    HTTPServer httpServer;
    httpServer.Run ( );
}

int main(int argc, const char **argv)
{   
    testHTTPServer();
    // testTCPModule();

    return 0;
}
