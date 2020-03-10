#include <iostream>

#include "../includes/HTTPServer.h"
#include "../includes/TCPServer.h"
#include "../includes/TCPModule.h"
#include "../includes/Catalog.h"

using namespace std;

void testTCPModule() {
    hc::Server testServer("127.0.0.1", 8080);
    hc::Server dorianServer("", 8080);
    hc::Server avignon("127.0.0.1", 8088);
    hc::Server avignon_2("127.0.0.1", 11113);
    TCPModule tcpModule;
    tcpModule.MakeRequest(nullptr, avignon_2);
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