#ifndef EX4_COMMAND2_ALGORITHMSETTINGS_H
#define EX4_COMMAND2_ALGORITHMSETTINGS_H
#include "input_validation.h"
#include "Command.h"

class Command2_AlgorithmSettings : public Command{
public:
    // Constructor
    Command2_AlgorithmSettings(DefaultIO* dio, Data* data);
    // command 2 execute function
    // sent the algorithm settings to the client and update them if needed
    void execute();
};


#endif //EX4_COMMAND2_ALGORITHMSETTINGS_H
