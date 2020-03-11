/*************************************************************************
                            TCPModule  -  description
                              --------------------
   début                : 03/03/2020
   copyright            : (C) 2020 par name
*************************************************************************/

//---------- Interface de la classe <TCPModule> (fichier <TCPModule.h>) ------

#if ! defined ( TCPMODULE_H )
#define TCPMODULE_H
//--------------------------------------------------- Interfaces utilisées
#include <map>
#include <string>

#include "../libs/json/single_include/nlohmann/json.hpp"
#include "Server.h"
#include "TCPServer.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TCPModule>
//
//------------------------------------------------------------------------
class TCPModule
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    string MakeRequest(JSON params, const TCPServer & server);
    // Envoie une requête afin d'obtenir des informations
    // d'un serveur.

    bool DisconnectFromServer(const TCPServer & server);
    // Gère la déconnection d'un serveur.

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    TCPModule ( );
    // Mode d'emploi :
    // Constructeur par défaut de la classe <TCPModule>

    TCPModule ( const TCPModule & source );
    // Mode d'emploi :
    // Constructeur par copie de la classe <TCPModule>

    virtual ~TCPModule ( );
    // Mode d'emploi :
    // Destructeur de la classe <TCPModule>

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

    string makePullRequest(const TCPServer & server);
    // Réalise une requête d'informations en temps réel
    // sur une centrale hydraulique.

    string makeHistoricRequest(JSON params, const TCPServer & server);
    // Réalise une requête d'historique sur une centrale.

    /**
     * Connect to a TCP server
     * @param server The target server to connect with it
     * @return true if the connection has failed, else true
     **/
    bool connectToServer(const TCPServer & server);
    // Gère la connection à un serveur contenant des informations
    // sur une centrale hydraulique.

    JSON parseResponse(string & data);
    // Transforme une réponse d'un serveur en un objet de format JSON.

    bool isConnected(const TCPServer server);
    // Retourne true si le serveur passé en paramètre est connecté ou non.

//----------------------------------------------------- Attributs protégés

    // map with key ip:port and the value is the corresponding socket
    unordered_map<string, int> sockets;
};

//--------------------------- Autres définitions dépendantes de <TCPModule>

#endif // TCPMODULE_H