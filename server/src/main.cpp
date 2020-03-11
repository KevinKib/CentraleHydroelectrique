#include <iostream>

#include "../includes/HTTPServer.h"
#include "../includes/TCPServer.h"
#include "../includes/TCPModule.h"
#include "../includes/Catalog.h"

using namespace std;

void testTCPModule() {
    // hc::Server testServer("127.0.0.1", 8100);
    hc::Server dorianServer("", 8080);
    // hc::Server avignon("127.0.0.1", 8088);      // TCP-PUSH
    hc::Server avignon("127.0.0.1", 11113);  // TCP-PULL

    TCPServer avignon_tcp("127.0.0.1", 8088, 1, "attribute", "type", 0.1, PUSH, "centrale", "turbine");

    TCPModule tcpModule;
    tcpModule.MakeRequest(nullptr, avignon_tcp);
}

void testHTTPServer() {
    HTTPServer httpServer;
    httpServer.Run ( );
}

int main(int argc, const char **argv)
{   
    // testHTTPServer();
    testTCPModule();

    return 0;
}