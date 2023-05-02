#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <vector>
#include <unistd.h>
#include "input_validation.h"
#include "DefaultIO.h"
#include "SocketIO.h"
#include "CLI.h"
#include <pthread.h>
using namespace std;

void *threadPerClient(void* c) {
    int* client_sock = (int*)c;
    // create a socketIO object for the client
    DefaultIO* dio = new SocketIO(*client_sock);
    // create a CLI object for the client
    CLI cli = CLI(dio);
    // start the CLI
    cli.start();
    //free memory and close socket
    delete dio;
    close(*client_sock);
    delete client_sock;
}

// this is the main server program
int main(int argc, char** argv){
    // check if number of argument is valid
    if (argc != 2) {
        cout << "Expected 1 arguments but " << argc-1 << " were given" <<  endl;
        return 0;
    }
    // get port value + validation
    string port_str = argv[1];
    int server_port;
    if(!portValidation(port_str, server_port)){
        return 0;
    }
    // Create server socket
    int sock = socket(AF_INET, SOCK_STREAM,0);
    // Check If the socket is created
    if (sock < 0){
        perror("error creating socket");
        return 0;
    }

    // Address info to bind socket
    struct sockaddr_in sin;
    memset(&sin,0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    // Bind socket
    if (bind(sock,(struct sockaddr*)&sin, sizeof(sin))<0){
        perror("error binding socket");
        close(sock);
        return 0;
    }

    // Start listening
    if (listen(sock,5)<0){
        perror("error listening to a socket");
        close(sock);
        return 0;
    }
    while(true) {
        // accept client
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {
            perror("error accepting client");
            continue;
        }
        //create a new thread to a new connected client
        // the tread identifiers
        pthread_t pthread_client;
        // set of thread attributes
        pthread_attr_t attr;
        // set the default attributes of the thread
        pthread_attr_init(&attr);
        // save the client socket in the heap memory
        int* client_sock_ptr = new int(client_sock);
        //create the thread
        int ret = pthread_create(&pthread_client, &attr, threadPerClient, (void *) client_sock_ptr);
        if (ret != 0) {
            perror("Error creating thread");
            close(client_sock);
            delete client_sock_ptr;
            continue;
        }
        // detach the thread from the main program to create a new thread for each client
        // and dispose of the thread when it is done
        pthread_detach(pthread_client);
    }
    close(sock);
}