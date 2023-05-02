#ifndef EX4_DEFAULTIO_H
#define EX4_DEFAULTIO_H

#include <iostream>
#include <string>
using namespace std;

class DefaultIO {
public:
    // bool to check if read/write failed
    bool error = false;
    // read function to implement in the derived classes
    virtual string read()=0;
    // write function to implement in the derived classes
    virtual void write(string str)=0;
};


#endif //EX4_DEFAULTIO_H
