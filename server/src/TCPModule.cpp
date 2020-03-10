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

//------------------------------------------------------ Include personnel
#include "../includes/TCPModule.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

// bool TCPModule::isConnected(const hc::Server server)
// {
//     unordered_map<hc::Server, int>::iterator it = map_server_socket.find(server);

//     return (it != map_server_socket.end());
// }

bool TCPModule::connectToServer(const hc::Server & server)
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

bool TCPModule::MakeRequest(JSON params, const hc::Server & server)
{
    // Si l'on est pas connecté, on fait un essai de connection.
    if (!isConnected) {
        isConnected = connectToServer(server);
    }

    // Si l'on est toujours pas connecté, alors on signale que la requête à échoué.
    if (!isConnected) {
        cerr << "Could not connect to server." << endl;
        return false;
    }

    cout << "Connection succeeded." << endl;

    // Test de requête
    // TODO : Sélectionner la bonne requête en fonction des paramètres
    // makePullRequest(params, server);

    return true;
}

TCPResponse TCPModule::makePullRequest(JSON params, const hc::Server & server)
{
    TCPResponse tcpResponse;
    // Envoi d'une requête pull au serveur
    char pullRequest[1024] = "GET TS CRLF CRLF";

    string key = server.GetHashKey ( );
    int serv_socket = sockets[key];

    send(serv_socket, pullRequest, strlen(pullRequest), 0);

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

TCPResponse TCPModule::makeHistoricRequest(JSON params, const hc::Server & server)
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

    string key = server.GetHashKey ( );

    int serv_socket = sockets[key];
    char pushRequest[1024] = "GET ID CRLF LISTEN_PORT listen_port CRLF START_FATE JJ/MM/YYYY HH:mm:ss END_DATE JJ/MM/YYYY HH:mm:ss CRLF CRLF";
    send(serv_socket, pushRequest, strlen(pushRequest), 0);

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
