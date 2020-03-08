#include <iostream>

#include "../includes/HTTPServer.h"
#include "../includes/TCPServer.h"
#include "../includes/TCPModule.h"
#include "../includes/Catalog.h"

using namespace std;

int testTCPModule() {
    hc::Server testServer("127.0.0.1", 8081);
    TCPModule tcpModule;
    tcpModule.MakeRequest(nullptr, testServer);
}

int main(int argc, const char **argv)
{
    HTTPServer httpServer;

    TCPServer tcpServer = TCPServer::fromString ( "StreamID=2 group=Avignon.Group1 attribute=HauteurChute type=H address=134.213.23.12 port=8013 protocol=TCP_PUSH frequency=2" );

    cout << tcpServer << endl;

    cout << "S" << endl;
    httpServer.Run ( );
    

    return 0;
}