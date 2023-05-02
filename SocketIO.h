#ifndef EX4_SOCKETIO_H
#define EX4_SOCKETIO_H
#include "DefaultIO.h"
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

class SocketIO : public DefaultIO{
    // the client socket
    int client_sock;
public:
    // Constructor
    SocketIO(int client_sock);
    // read from the client through socket using recv()
    string read();
    // write to the client through socket using send()
    void write(string str);
};


#endif //EX4_SOCKETIO_H
