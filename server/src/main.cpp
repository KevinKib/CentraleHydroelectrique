#include <iostream>

#include "../includes/HTTPServer.h"
#include "../includes/TCPServer.h"
#include "../includes/TCPModule.h"
#include "../includes/Catalog.h"

using namespace std;

void testTCPModule() {
    hc::Server testServer("127.0.0.1", 8081);
    hc::Server dorianServer("", 8081);
    TCPModule tcpModule;
    tcpModule.MakeRequest(nullptr, testServer);
}

void testHTTPServer() {
    HTTPServer httpServer;
    httpServer.Run ( );
}

int main(int argc, const char **argv)
{   
    testTCPModule();
    // testHTTPServer();

    return 0;
}