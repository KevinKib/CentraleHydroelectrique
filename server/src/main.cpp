#include <iostream>

#include "../includes/HTTPServer.h"
#include "../includes/TCPServer.h"
#include "../includes/Catalog.h"

using namespace std;

int main(int argc, const char **argv)
{
    Catalog catalog ( "ServerAddress: 134.213.23.12\r\nServerPort: 8080\r\nStreamID=1 group=Avignon.Groupe1 attribute=Debit type=RT address=134.213.23.12 port=8012 protocol=TCP_PULL frequency=0.1\r\n" );


    return 0;
}