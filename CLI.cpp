#include "CLI.h"

// this is the CLI class
CLI::CLI(DefaultIO* dio){
    this->dio = dio;
    this->data = Data();
    // add the commands to map
    this->commands.insert({"1", new Command1_UploadData(this->dio, &(this->data))});
    this->commands.insert({"2", new Command2_AlgorithmSettings(this->dio, &(this->data))});
    this->commands.insert({"3", new Command3_ClassifyData(this->dio, &(this->data))});
    this->commands.insert({"4", new Command4_DisplayResults(this->dio, &(this->data))});
    this->commands.insert({"5", new Command5_downloadResults(this->dio, &(this->data))});

}
// this is the main program that is in charge of printing the menu and executing the right command
// that the user chooses on the server side.
void CLI::start(){
    string menu;
    vector<string> v{"1", "2", "3", "4", "5"};
    //loop the commands and create a menu string
    for(int i=0; i<5; i++){
        menu += this->commands[v[i]]->description;
    }
    menu += "8. exit\n";

    string command_num = "";
    while(true) {
        // write menu to client
        this->dio->write(menu);
        if(this->dio->error) return; // check if write was successful
        // get command number from client
        command_num = this->dio->read();
        if(this->dio->error) return; // check if read was successful
        //check if command_num is 8
        if (command_num == "8"){
            break;
        }
        // check if command_num is valid
        else if (count(v.begin(), v.end(), command_num)) {
            this->commands[command_num]->execute();
            if(this->dio->error) return; // check if write/read inside commands was successful
        }
        // if command is not valid
        else{
            this->dio->write("Invalid selection\n");
            if(this->dio->error) return; // check if write was successful
        }

    }
}
CLI::~CLI(){
    //delete commands
    for(auto it = this->commands.begin(); it != this->commands.end(); ++it) {
        delete it->second;
    }
}