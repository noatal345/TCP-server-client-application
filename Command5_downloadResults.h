#ifndef EX4_AP_COMMAND5_DOWNLOADRESULTS_H
#define EX4_AP_COMMAND5_DOWNLOADRESULTS_H
#include "Command.h"

class Command5_downloadResults :public Command{
public:
    // Constructor
    Command5_downloadResults(DefaultIO* dio, Data* data);
    // command 5 execute function
    // this function send the results of the classification (command 3) to the client to save to path
    void execute();
};


#endif //EX4_AP_COMMAND5_DOWNLOADRESULTS_H
