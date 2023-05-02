#ifndef EX4_COMMAND1_UPLOADDATA_H
#define EX4_COMMAND1_UPLOADDATA_H
#include <iostream>
#include <string>
#include "DefaultIO.h"
#include "SocketIO.h"
#include "Command.h"
#include <fstream>

#include <string.h>
#include <vector>
#include "input_validation.h"

class Command1_UploadData : public Command {
public:
    // Constructor
    Command1_UploadData(DefaultIO *dio, Data *data);
    // command 1 execute function
    // this function uploads the train and test data from the client to the server and save it in the data object
    void execute();
};

#endif //EX4_COMMAND1_UPLOADDATA_H
