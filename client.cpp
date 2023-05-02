#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
#include <string>
#include <string.h>
#include <algorithm>
#include "input_validation.h"
#include <fstream>
#include <pthread.h>


bool downloadFile = false;


//this function receive a file path and read the file content into a string.
bool readFileToString(string path, string &outputData) {
    ifstream file(path);
    if (file) {
        string line = "";
        while (getline(file, line)) {
            outputData += line;
            outputData += "\n";
        }
        file.close();
    }
    // problem reading file
    if(outputData.size() == 0) {
        return false;
    } else {
        return true;
    }
}

// this thread is in charge of saving the classified data to the users path
void *saveFileThread(void* d) {
    string *dat = (string*)d;
    string data = *dat;

    if (data.length()>0){
        // get path from the end of the data string
        string path = data.substr(data.find_last_of("*")+1);
        // get data without *path
        data = data.substr(0, data.find_last_of("*"));
//        // add file name to path
//        path += "/classifiedDate.csv";

        // save data to file
        ofstream file(path, ofstream::trunc);
        if (file) {
            file << data;
            file.close();
        } else {
            cout << "invalid path" << endl;
        }

    } else {
        // something went wrong with sending data to thread
        cout << "no data to save" << endl;
    }

}


// this thread is in charge of receiving messages from the server and printing them to the user.
void *receiveThread(void* s) {
    int *sock = (int*)s;
    while(true) {
        // receive info from server
        char buffer[4096];
        //clean buffer

        int expected_data_len = sizeof(buffer);

        string data ="";
        // getting the information part by part-if the info is bigger than the buffer size.
        while(true) {
            // receive
            bzero(buffer, 4096);
            int read_bytes = recv(*sock, buffer, expected_data_len, 0);

            if (read_bytes == 0) {
                // connection is closed
                close(*sock);
                return 0;
            } else if (read_bytes < 0) {
                cout << "Error receiving data from server";
                close(*sock);
                return 0;
            } else if (read_bytes < 4095) {
                //  done receiving the whole message from server.
                data.append(buffer, read_bytes);
                break;
            } else {
                // saving all parts
                data.append(buffer, read_bytes);
            }
        }
        if(downloadFile && data[0]=='$'){
            if(data[data.length()-1]!='#') {
                // if menu was sent with data split it
                string menu = data.substr(data.find_last_of("#") + 1);
                data = data.substr(1, data.find_last_of("#")-1);
                cout << menu << flush;
            }
            else{
                data = data.substr(1, data.length()-2);
            }
            downloadFile = false;
            // the tread identifiers
            pthread_t pthread_fileSave;
            // set of thread attributes
            pthread_attr_t attr;
            // set the default attributes of the thread
            pthread_attr_init(&attr);
            //create the threads
            pthread_create(&pthread_fileSave, &attr, saveFileThread, (void *)&data);
            // wait for the threads to exit;
            pthread_join(pthread_fileSave, NULL);
        } else {
            // print the whole message content to the user
            downloadFile = false;
            cout << data << flush;
        }
    }
}

// this thread is in charge of sending messages to the server.
void *sendThread(void* s) {
    int* sock = (int*)s;
    while(true) {
        int count_bytes_sent = 0;
        // create a buffer to send user input to the server
        char data_addr[4096];
        // clean the buffer
        bzero(data_addr, 4096);
        // get user input
        string userInput = "";
        getline(cin, userInput);
        if(userInput == ""){
            userInput = "enter";
        }
        strcpy(data_addr, userInput.c_str());
        int data_len = strlen(data_addr);
        // send user choice to server
        int sent_bytes = send(*sock, data_addr, data_len, 0);
        if (sent_bytes < 0) {
            //error
            cout << "Error sending data to server" << endl;
            close(*sock);
            return 0;
        }
        // if command number 1 - check for file path
        if (userInput == "1") {
            // get user file path for training data
            string train_path = "";
            getline(cin, train_path);
            // save the file content into a string to pass to the buffer
            string train_data = "";
            if (readFileToString(train_path, train_data)) {
                train_data += "$";
                // if file is found/not empty
                // copy the train_data string into the buffer data_addr
                int init_index = 0;
                // send file content part by part in a loop
                while(true) {
                    // clean the buffer
                    bzero(data_addr, 4096);
                    // substring to send in the size of the buffer
                    string part_of_file_to_send =  train_data.substr(init_index,4095);
                    strcpy(data_addr, part_of_file_to_send.c_str());
                    int data_len = strlen(data_addr);
                    //send

                    int sent_bytes = send(*sock, data_addr, data_len, 0);
                    if (sent_bytes < 0) {
                        //error
                        cout << "Error sending data to server" << endl;
                        close(*sock);
                        return 0;
                    }
                    // update substring start position
                    init_index += 4095;

                    if (part_of_file_to_send.length() < 4095) {
                        // done sending file content
                        break;
                    }
                }
                // get user file path for the validation set
                string test_path = "";
                getline(cin, test_path);
                // save the file into a string to pass to the buffer
                string test_data = "";
                if (readFileToString(test_path, test_data)) {
                    test_data += "$";
                    // if file is found/not empty
                    init_index = 0;
                    // send file content part by part in a loop
                    while(true) {
                        bzero(data_addr, 4096);
                        // substring to send in the size of the buffer
                        string part_of_file_to_send =  test_data.substr(init_index, 4095);
                        strcpy(data_addr, part_of_file_to_send.c_str());
                        int data_len = strlen(data_addr);
                        //send
                        int sent_bytes = send(*sock, data_addr, data_len, 0);
                        if (sent_bytes < 0) {
                            //error
                            cout << "Error sending data to server" << endl;
                            close(*sock);
                            return 0;
                        }
                        // update substring start position
                        init_index += 4095;
                        if (part_of_file_to_send.length() < 4095) {
                            // done sending file content
                            break;
                        }
                    }
                } else {
                    // send "invalid" to server
                    bzero(data_addr, 4096);
                    string word = "invalid";
                    strcpy(data_addr, word.c_str());
                    int data_len = strlen(data_addr);
                    //send
                    int sent_bytes = send(*sock, data_addr, data_len, 0);
                    if (sent_bytes < 0) {
                        //error
                        cout << "Error sending data to server" << endl;
                        close(*sock);
                        return 0;
                    }
                }
            } else {
                // send "invalid" to server
                bzero(data_addr, 4096);
                string word = "invalid";
                strcpy(data_addr, word.c_str());
                int data_len = strlen(data_addr);
                //send
                int sent_bytes = send(*sock, data_addr, data_len, 0);
                if (sent_bytes < 0) {
                    //error
                    cout << "Error sending data to server" << endl;
                    close(*sock);
                    return 0;
                }
            }
        } else if (userInput =="5") {
            //update the global variable for the receive-thread to know.
            downloadFile = true;
            string filepath="";
            getline(cin, filepath);
            bzero(data_addr, 4096);
            // send in the size of the buffer
            strcpy(data_addr, filepath.c_str());
            int data_len = strlen(data_addr);
            //send
            int sent_bytes = send(*sock, data_addr, data_len, 0);
            if (sent_bytes < 0) {
                //error
                cout << "Error sending data to server" << endl;
                close(*sock);
                return 0;
            }
        } else if (userInput == "8") {
            // exit
            close(*sock);
            return 0;
        }
    }
}


//this is the main client program
int main(int argc, char** argv) {
    // check if number of argument is valid
    if (argc != 3) {
        cout << "Expected 2 arguments but " << argc - 1 << " were given" << endl;
        return 0;
    }
    // save the arguments inside the corresponding variables
    const char *ip = argv[1];
    string str_port = argv[2];

    // input validation of ip number and port number
    int clientPort;
    if (!portValidation(str_port, clientPort)) {
        cout << "invalid port number" << endl;
        return 0;
    }
    if (!ip_validation(ip)) {
        cout << "invalid ip number" << endl;
        return 0;
    }
    // socket initialization
    const char *ip_address = ip;
    const int port_no = clientPort;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    //if socket was successfully created
    if (sock < 0) {
        perror("error creating socket");
        return 0;
    }

    // trying to connect to server
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
        return 0;
    }
    // this loop is in charge of creating threads
    while(true) {
        // the tread identifiers
        pthread_t pthread_receive;
        pthread_t pthread_send;
        // set of thread attributes
        pthread_attr_t attr;
        // set the default attributes of the thread
        pthread_attr_init(&attr);
        //create the threads
        pthread_create(&pthread_receive, &attr, receiveThread, (void *)&sock);
        pthread_create(&pthread_send, &attr, sendThread, (void *)&sock);
        // wait for the threads to exit;
        pthread_join(pthread_receive, NULL);
        pthread_join(pthread_send, NULL);
        close(sock);
        return 0;

    }
}