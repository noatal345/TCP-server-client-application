#ifndef EX3_DISTANCE_FUNCTIONS_H
#define EX3_DISTANCE_FUNCTIONS_H
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

//p value for minkowski distance function
const int p_value_minkowski = 2;

//Euclidean distance calculation
double euclideanDistance(vector<double> v1, vector<double> v2);

//Manhattan distance calculation
double manhattanDistance(vector<double> v1, vector<double> v2);

//Chebyshev distance calculation
double chebyshevDistance(vector<double> v1, vector<double> v2);

//Canberra distance calculation
double canberraDistance(vector<double> v1, vector<double> v2);

//Minkowski distance calculation
double minkowskiDistance(vector<double> v1, vector<double> v2);

#endif //EX3_DISTANCE_FUNCTIONS_H
