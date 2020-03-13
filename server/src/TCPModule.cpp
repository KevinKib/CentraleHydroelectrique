/*************************************************************************
                            TCPModule  -  description
                              --------------------
   début                : 03/03/2020
   copyright            : (C) 2020 par name
*************************************************************************/

//---------- Réalisation de la classe <TCPModule> (fichier TCPModule.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <unistd.h>
#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 

#include <netinet/in.h> 
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <errno.h>

//------------------------------------------------------ Include personnel
#include "../includes/TCPModule.h"
#include "../includes/TCPServer.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

bool TCPModule::isConnected(const TCPServer server)
{
    return sockets[server.GetHashKey()] > 0;
}

bool TCPModule::connectToServer(const TCPServer & server)
{
    // https://www.geeksforgeeks.org/socket-programming-cc/
    cout << "Attempt to connect to the following server : " << endl << server << endl;

    struct sockaddr_in serv_addr; 

    // On crée un socket.
    int serv_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_socket < 0) { 
        throw string("Socket creation error.");
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(server.port); 
       
    if(inet_pton(AF_INET, server.ip.c_str(), &serv_addr.sin_addr)<=0)  
    { 
        throw string("Invalid address/ Address not supported");
    } 

    int connect_val = connect(serv_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (connect_val < 0) 
    { 
        throw string("Connection failed.");
    } 

    // La connexion a réussi.
    string key = server.GetHashKey ( );
    sockets[key] = serv_socket;
    cout << "Successful connection." << endl;

    return true; 
}

bool TCPModule::DisconnectFromServer(const TCPServer & server)
{
    int serv_socket = sockets[server.GetHashKey()];

    // Envoie une requête de déconnexion au serveur.
    char disconnectRequest[1024] = "END\r\n\r\n";
    send(serv_socket, disconnectRequest, strlen(disconnectRequest), 0);

    // N'attend aucune réponse du serveur; considère qu'il est déconnecté.
    return true;
}

string TCPModule::MakeRequest(JSON params, const TCPServer & server)
{

    // Si l'on est pas connecté, on fait un essai de connection.
    if (!isConnected(server)) {
        connectToServer(server);
    }

    // Si l'on est toujours pas connecté, alors on signale que la requête à échoué.
    if (!isConnected(server)) {
        throw string("Could not connect to server.");
    }

    string response = "";

    if (server.protocol == TCPProtocol::PULL) {
        response = makePullRequest ( server );
    }
    else {
        throw string("TCP-PUSH protocol is unimplemented.");
    }

    return response;
}

string TCPModule::makePullRequest(const TCPServer & server)
{
    cout << "Do we enter" << endl;

    // Envoi d'une requête pull au serveur
    char pullRequest[1024] = "GET TS \r\n\r\n";
    int serv_socket = sockets[server.GetHashKey()];

    int send_value = send(serv_socket, pullRequest, strlen(pullRequest), 0);

    // On vérifie que le message s'est bien envoyé.
    if (send_value == -1) {
        throw string("Send error. Errno = " + to_string(errno) + ".");
    }

    // Attente de la réponse du serveur
    char response[1024] = {0};
    int read_value = read(serv_socket, response, 1024);

    // On vérifie que le serveur à bien répondu
    if (read_value == 0) {
        throw string("The server is not running.");
    }
    else if (read_value == -1) {
        throw string("Read error. Errno = " + to_string(errno) + ".");
    }

    cout << response << endl;
    string response_str = response;
    JSON json = parseResponse(response_str);

    return response;
}

string TCPModule::makeHistoricRequest(JSON params, const TCPServer & server)
/*
    Le protocole TCP-PUSH n'est désormais plus utilisé.

    Envoi d'une requête TCP-PUSH au serveur
    Envoi attendu :
    {
      GET ID CRLF
      LISTEN_PORT listen_port CRLF
      START_DATE JJ/MM/YYYY HH:mm:ss CRLF
      END_DATE JJ/MM/YYYY HH:mm:ss CRLF
      CRLF
    }
*/
{
    string listen_port = "8090";
    string start_date = "09/03/2020 08:00:00";
    string end_date = "10/03/2020 08:00:00";
    string id = "1";

    int serv_socket = sockets[server.GetHashKey()];
    
    // On envoie une requête pour demander au serveur de se connecter sur le port spécifié par le client.
    string pushRequest = "GET " + id + "\r\nLISTEN_PORT " + listen_port + "\r\nSTART_DATE " + start_date + "\r\nEND_DATE " + end_date + "\r\n\r\n";
    send(serv_socket, pushRequest.c_str(), pushRequest.length(), 0);
    cout << "Push init message sent." << endl;

    // On attend, pour s'assurer que les deux sockets ne sont envoyées en même temps.
    sleep(1);

    // On envoie le message START.
    string startRequest = "START\r\n\r\n";
    send(serv_socket, startRequest.c_str(), startRequest.length(), 0);
    cout << "Start message sent." << endl;

    return string("Historic request return");
}

JSON TCPModule::parseResponse(string & data)
{
    // TODO : Coder parseResponse
    JSON json;
    string buffer;
    int index;

    // json["time"] = data.substr(0, data.length()-4);

    index = data.find_first_of ( "/" );
    buffer = data.substr(0, index);
    data = data.substr ( index+1 );
    json["day"] = buffer;

    index = data.find_first_of ( "/" );
    buffer = data.substr(0, index);
    data = data.substr ( index+1 );
    json["month"] = buffer;

    index = data.find_first_of ( " " );
    buffer = data.substr(0, index);
    data = data.substr ( index+1 );
    json["year"] = buffer;

    index = data.find_first_of ( ":" );
    buffer = data.substr(0, index);
    data = data.substr ( index+1 );
    json["hour"] = buffer;

    index = data.find_first_of ( ":" );
    buffer = data.substr(0, index);
    data = data.substr ( index+1 );
    json["minute"] = buffer;

    index = data.find_first_of ( " " );
    buffer = data.substr(0, index);
    data = data.substr ( index+1 );
    json["second"] = buffer;

    index = data.find_first_of ( "\r" );
    buffer = data.substr(0, index);
    data = data.substr ( index+1 );
    json["value"] = buffer;

    return json;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
TCPModule::TCPModule ( const TCPModule & unTCPModule )
// Algorithme :
//
    : sockets ( unTCPModule.sockets )
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <TCPModule>" << endl;
#endif

    // map_server_socket = unTCPModule.map_server_socket;

} //----- Fin de TCPModule (constructeur de copie)

TCPModule::TCPModule ( )
// Algorithme :
//
    : sockets ( )
{
#ifdef MAP
    cout << "Appel au constructeur de <TCPModule>" << endl;
#endif

} //----- Fin de TCPModule

TCPModule::~TCPModule ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TCPModule>" << endl;
#endif
} //----- Fin de ~TCPModule

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
