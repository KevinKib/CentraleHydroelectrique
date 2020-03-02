#include <iostream>

#include "../includes/HTTPServer.h"
#include "../includes/TCPServer.h"

using namespace std;

int main(int argc, const char **argv)
{
    HTTPServer server;

    TCPServer tcpServer = TCPServer::fromString ( "StreamID=2 group=Avignon.Group1 attribute=HauteurChute type=H address=134.213.23.12 port=8013 protocol=TCP_PUSH frequency=2" );

    cout << tcpServer << endl;

    server.Run ( );

    return 0;
}