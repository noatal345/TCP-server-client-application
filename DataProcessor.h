#ifndef EX3_DATAPROCESSOR_H
#define EX3_DATAPROCESSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//This is the dataprocessor class.
class DataProcessor {
private:
    string fileName;
    string delimeter;
    int vectorSize = 0;
    int trainSamplesNumber = 0;

    //This function split the data of one string sample into 2 strings features and label.
    void splitData(string d, string& vec, string& lable);

public:
    //constructor
    DataProcessor(const string& fileName, const string& delimeter = ","):
            fileName(fileName),
            delimeter(delimeter) {}

    //This function reads a CSV file into a vector of strings if possible.
    vector<string> readFile();

    //This function reads a String into a vector of strings if possible.
    vector<string> readString();

    // This function gets a data vector of strings and calls a function that splits
    // the data for every sample if it's possible.
    // if the number of features in a sample is not consistent with the others the
    // function will return false.
    bool get_train_data(vector<string> data, vector<vector<double>>& train, vector<string>& lables);

    //This function returns the size of a sample in the training set.
    int getVectorSize();

    //This function returns the number of a samples in the training set.
    int gettrainSamplesNumber();
};


#endif //EX3_DATAPROCESSOR_H
