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
<<<<<<< HEAD
    testTCPModule();
    // testHTTPServer();
=======
    testHTTPServer();
>>>>>>> d0300fc45b5224607fedcab0d42d9c5b70bc3b43

    return 0;
}