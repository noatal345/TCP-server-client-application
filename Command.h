#ifndef EX4_COMMAND_H
#define EX4_COMMAND_H
#include <iostream>
#include <string>
#include "DefaultIO.h"
#include "SocketIO.h"
#include "Data.h"
using namespace std;

// this is the Command abstract class
class Command {
public:
    // destructor
    virtual ~Command(){}
    // the command description
    string description;
    // io to write/read from
    DefaultIO* dio;
    // execute function which is implemented in the derived classes and defines the command's behavior
    virtual void execute()=0;
    // algorithm data and settings
    Data* data;
};


#endif //EX4_COMMAND_H
