#ifndef EX4_DATA_H
#define EX4_DATA_H

#include <vector>
#include <string>
using namespace std;

// this class holds the data and settings of the algorithm
class Data {
public:
    // the classifies data
    vector<vector<double>> classified;
    // the classified data labels
    vector<string> classified_labels;
    // the test data
    vector<vector<double>> unclassified;
    // the test data labels
    vector<string> unclassified_labels;
    // the k value
    int k = 5;
    // the number of features
    int vec_size = 1000;
    // the distance function
    string distance_metric_name = "AUC";
};


#endif //EX4_DATA_H
