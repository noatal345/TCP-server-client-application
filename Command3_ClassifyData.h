#ifndef EX4_COMMAND3_CLASSIFYDATA_H
#define EX4_COMMAND3_CLASSIFYDATA_H
#include "Command.h"
#include "KNeighborsClassifier.h"


class Command3_ClassifyData: public Command{
public:
    // Constructor
    Command3_ClassifyData(DefaultIO* dio, Data* data);
    // command 3 execute function
    // this function classify the test data using the knn algorithm
    void execute();
};


#endif //EX4_COMMAND3_CLASSIFYDATA_H
