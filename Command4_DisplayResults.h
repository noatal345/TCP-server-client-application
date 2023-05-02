#ifndef EX4_COMMAND4_DISPLAYRESULTS_H
#define EX4_COMMAND4_DISPLAYRESULTS_H
#include "Command.h"

class Command4_DisplayResults:public Command{
public:
    // Constructor
    Command4_DisplayResults(DefaultIO* dio, Data* data);
    // command 4 execute function
    // this function send the results of the classification (command 3) to the client to display
    void execute() override;
};


#endif //EX4_COMMAND4_DISPLAYRESULTS_H
