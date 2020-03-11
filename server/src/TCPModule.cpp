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
    // unordered_map<string, int>::iterator it = sockets.find(server);
    // return (it != map_server_socket.end());

    cout << sockets[server.GetHashKey()] << endl;
    return false;
}

bool TCPModule::connectToServer(const TCPServer & server)
{
    
    // https://www.geeksforgeeks.org/socket-programming-cc/
    cout << "Attempt to connect to the following server : " << endl << server << endl;

    struct sockaddr_in serv_addr; 

    // On crée un socket.
    int serv_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_socket < 0) { 
        cerr << "Socket creation error." << endl;
        return false; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(server.port); 
       
    if(inet_pton(AF_INET, server.ip.c_str(), &serv_addr.sin_addr)<=0)  
    { 
        cerr << "Invalid address/ Address not supported" << endl;
        return false;
    } 

    int connect_val = connect(serv_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (connect_val < 0) 
    { 
        cerr << "Connection failed." << endl;
        return false;
    } 

    // La connexion a réussi.
    string key = server.GetHashKey ( );
    sockets[key] = serv_socket;

    cout << "Key : " << key << endl;

    return true; 
}

// bool TCPModule::DisconnectFromServer(const hc::Server & server)
// {
//     // Envoie une requête de déconnexion au serveur.
//     char disconnectRequest[1024] = "END CRLF CRLF";
//     send(serv_socket, disconnectRequest, strlen(disconnectRequest), 0);

//     // N'attend aucune réponse du serveur; considère qu'il est déconnecté.
//     return true;
// }

TCPResponse TCPModule::MakeRequest(JSON params, const TCPServer & server)
{
    TCPResponse tcpResponse;
    tcpResponse.first = false;

    // Si l'on est pas connecté, on fait un essai de connection.
    if (!isConnected(server)) {
        connectToServer(server);
    }

    // Si l'on est toujours pas connecté, alors on signale que la requête à échoué.
    // if (!isConnected(server)) {
    //     cout << "Could not connect." << endl;
    //     tcpResponse.second = "Could not connect to server.";
    //     return tcpResponse;
    // }

    cout << "Connection (likely) succeeded." << endl;

    // Test de requête
    // TODO : Sélectionner la bonne requête en fonction des paramètres
    

    makeHistoricRequest(params, server);

    // tcpResponse = makePullRequest(server);
    // cout << "Serveur : " << tcpResponse.second << endl;
    return tcpResponse;
}

TCPResponse TCPModule::makePullRequest(const TCPServer & server)
{
    TCPResponse tcpResponse;
    
    // Envoi d'une requête pull au serveur
    char pullRequest[1024] = "GET TS CRLF CRLF";
    string error = "An error occured.";
    string key = server.GetHashKey ( );
    int serv_socket = sockets[key];

    int send_value = send(serv_socket, pullRequest, strlen(pullRequest), 0);
    // On vérifie que le message s'est bien envoyé.
    if (send_value == -1) {
        tcpResponse.first = false;
        // string r = "Send error. Errno = " + errno + ".";
        tcpResponse.second = "Send error.";
        return tcpResponse;
    }

    // Attente de la réponse du serveur
    char response[1024] = {0};
    int read_value = read(serv_socket, response, 1024);

    // On vérifie que le serveur à bien répondu
    if (read_value == 0) {
        tcpResponse.first = false;
        tcpResponse.second = "The server is not running.";
        return tcpResponse;
    }
    else if (read_value == -1) {
        tcpResponse.first = false;
        // tcpResponse.second = "Read error. Errno = " + errno + ".";
        tcpResponse.second = "Read error.";
        return tcpResponse;
       
    }

    // Affichage de la réponse du serveur
    // Réponse attendue :
    // {
    //   Timestamp ts CRLF
    //   Value val CRLF
    //   CRLF
    // }

    tcpResponse.first = true;
    tcpResponse.second = response;

    return tcpResponse;
}

TCPResponse TCPModule::makeHistoricRequest(JSON params, const TCPServer & server)
{
    // TODO : Coder makeHistoricRequest
    // Envoi d'une requête TCP-PUSH au serveur
    // Envoi attendu :
    // {
    //   GET ID CRLF
    //   LISTEN_PORT listen_port CRLF
    //   START_DATE JJ/MM/YYYY HH:mm:ss
    //   END_DATE JJ/MM/YYYY HH:mm:ss CRLF
    //   CRLF
    // }   
    TCPResponse tcpResponse;

    string key = server.GetHashKey();
    string listen_port = "8100";
    string start_date = "09/03/2020 08:00:00";
    string end_date = "10/03/2020 08:00:00";
    string id = "1";

    int serv_socket = sockets[key];

    string pushRequest_1 = "GET " + id + " \r\n LISTEN_PORT " + listen_port + " \r\n START_DATE " + start_date + " \r\n END_DATE " + end_date + " \r\n \r\n";
    string pushRequest_2 = "GET " + id + " \n LISTEN_PORT " + listen_port + " \n START_DATE " + start_date + " \n END_DATE " + end_date + " \n \n";
    string pushRequest_3 = "GET " + id + " \r LISTEN_PORT " + listen_port + " \r START_DATE " + start_date + " \r END_DATE " + end_date + " \r \r";
    string pushRequest_4 = "GET " + id + " LISTEN_PORT " + listen_port + " START_DATE " + start_date + " END_DATE " + end_date + "\n";
    string pushRequest_5 = "GET " + id + "\r\n LISTEN_PORT " + listen_port + "\r\n START_DATE " + start_date + "\r\n END_DATE " + end_date + "\r\n";
    string pushRequest_6 = "GET " + id + " \r\nLISTEN_PORT " + listen_port + " \r\nSTART_DATE " + start_date + " \r\nEND_DATE " + end_date + " \r\n \r\n";

    send(serv_socket, pushRequest_6.c_str(), pushRequest_6.length(), 0);
    cout << "Push init message sent." << endl;
    sleep(3);

    // string startRequest = "START \n \n";
    string startRequest_1 = "START \r\n \r\n";
    string startRequest_2 = "START \r\n";
    string startRequest_3 = "START \n \n";
    string startRequest_4 = "START \n";
    string startRequest_5 = "START";

    string startRequest = startRequest_5;

    send(serv_socket, startRequest.c_str(), startRequest.length(), 0);
    cout << "Start message sent." << endl;

    
    // On n'attend aucune réponse du serveur (?)
    // Le serveur se connecte sur le port du client

    // Attente de la réponse du serveur
    char response[1024] = {0};
    int read_value = read(serv_socket, response, 1024);

    // On vérifie que le serveur à bien répondu
    if (read_value == 0) {
        cout << "The server is not running." << endl;
        tcpResponse.first = false;
        tcpResponse.second = "The server is not running.";
        return tcpResponse;
    }

    // Affichage de la réponse du serveur
    // Réponse attendue :
    // {
    //   Timestamp ts CRLF
    //   Value val CRLF
    //   CRLF
    // }
    cout << "Serveur : " << response << endl;

    return tcpResponse;
}

JSON TCPModule::parseResponse(string & data)
{
    // TODO : Coder parseResponse
    return nullptr;
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
