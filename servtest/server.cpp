#include <iostream>
#include <unistd.h> 
#include <stdio.h> 
#include <string.h> 

// Sockets
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

using namespace std;

#define PORT 8100 

int main() {
    cout << "Attempt to connect." << endl;

    // Variables init
    int server_fd;  // ?
    int new_socket; // ?
    int valread;    // ? Apparently unused
    int opt = 1;    // ?
    
    // Stores the message recieved from the client.
    char buffer[1024] = {0}; 

    // Stores the message that will be sent to the client.
    char hello[1024] = "Hello from server !"; 

    // Adresse locale au socket
    sockaddr_in addr;
    int addrlen = sizeof(addr); 
    addr.sin_addr.s_addr = INADDR_ANY; // indique que toutes les sources seront acceptées
    addr.sin_port = htons(PORT); // toujours penser à traduire le port en réseau
    addr.sin_family = AF_INET; // notre socket est TCP

    // Creating socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) 
    { 
        perror("Socket creation failed."); 
        exit(1); 
    } 
       
    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("Setsockopt failed."); 
        exit(1); 
    }

    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr))<0) 
    { 
        perror("Bind failed."); 
        exit(1);  
    } 

    if (listen(server_fd, 3) < 0) 
    { 
        perror("Listen failed."); 
        exit(1);
    } 

    cout << "Test server started on port " << PORT << "." << endl;


    while(true) {

        //
        new_socket = accept(server_fd, (struct sockaddr *)&addr, (socklen_t*)&addrlen);
        if (new_socket < 0) 
        { 
            perror("Socket failed."); 
            exit(1); // EXIT_FAILURE
        }

        // Attend un message du client, et l'affiche dans la console.
        valread = read(new_socket, buffer, 1024); 
        cout << "Client : " << buffer << endl; 

        // // Répond au client.
        // send(new_socket, hello, strlen(hello), 0); 
        // cout << "Hello message sent." << endl;
    }
     
    return 0;
}