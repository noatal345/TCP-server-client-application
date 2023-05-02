
#ifndef EX4_CLI_H
#define EX4_CLI_H

#include "DefaultIO.h"
#include "Command.h"
#include <map>
#include "Command2_AlgorithmSettings.h"
#include "Command1_UploadData.h"
#include "Command3_ClassifyData.h"
#include "Command4_DisplayResults.h"
#include "Command5_downloadResults.h"
#include "Data.h"
#include <algorithm>
// this is the CLI class
class CLI {
private:
    // io to write/read from
    DefaultIO* dio;
    // algorithm data and settings
    Data data;
    // map of commands
    map<string, Command*> commands;

public:
    // constructor
    CLI(DefaultIO* dio);
    // this is the main program that is in charge of printing the menu and executing the right command
    void start();
    // destructor
    ~CLI();
};


#endif //EX4_CLI_H
