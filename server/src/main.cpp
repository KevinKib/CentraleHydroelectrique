#include <iostream>

#include "../includes/HTTPServer.h"
#include "../includes/TCPServer.h"
#include "../includes/Catalog.h"

using namespace std;

int main(int argc, const char **argv)
{
    HTTPServer server;

    server.Run ( );

    return 0;
}