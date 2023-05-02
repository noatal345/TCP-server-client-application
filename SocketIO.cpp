#include "SocketIO.h"

SocketIO::SocketIO(int client_sock){
    this->client_sock = client_sock;
}

string SocketIO::read(){
    // receive
    char dataFromClient[4096];
    bzero(dataFromClient, 4096);
    int expected_data_len = sizeof(dataFromClient);
    bool is_file_flag = false;
    string data ="";
    while(true) {
        bzero(dataFromClient, 4096);
        int read_bytes = recv(this->client_sock, dataFromClient, expected_data_len, 0);
        // connection is closed
        if (read_bytes == 0) {
            perror("connection is closed");
            this->error = true;
            return "error1";
        }// error receiving from client
        else if (read_bytes < 0) {
            perror("error receiving from client");
            this->error = true;
            return "error2";
        } else if (read_bytes < 4095 && !is_file_flag) {
            data.append(dataFromClient, read_bytes);
            if (data[data.length()-1] == '$') data = data.substr(0, data.length()-1);
            break;
        }
        else if (is_file_flag && dataFromClient[read_bytes-1] == '$'){
            data.append(dataFromClient, read_bytes);
            data = data.substr(0, data.length()-1);
            break;
        }
        else {
            is_file_flag = true;
            data.append(dataFromClient, read_bytes);
        }
    }
    // return the data the client sent
    return data;
}

void SocketIO::write(string str) {
    // if the string is too long, send it in a loop
    if (str.length() > 4095){
        int init_index = 0;
        // send file content in a loop
        while(true) {
            // substring to send
            string part_of_data_to_send =  str.substr(init_index, 4095);
            // create char array for this part of data
            char str_to_char_arr[(part_of_data_to_send).length()];
            // copy the string part to the char array
            strcpy(str_to_char_arr, part_of_data_to_send.c_str());

            int sent_bytes = send(this->client_sock, str_to_char_arr, sizeof(str_to_char_arr), 0);
            if (sent_bytes < 0) {
                perror("error sending to client");
                this->error = true;
            }
            // update substring start position
            init_index += 4095;
            if (sent_bytes < 4095) {
                // done sending file content
                break;
            }
        }
    } else { // send the string
        char str_to_char_arr[(str).length()];
        strcpy(str_to_char_arr, str.c_str());
        int sent_bytes = send(this->client_sock, str_to_char_arr, sizeof(str_to_char_arr), 0);
        if (sent_bytes < 0) {
            perror("error sending to client");
            this->error = true;
        }
    }
}