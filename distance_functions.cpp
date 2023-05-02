#include "distance_functions.h"

double euclideanDistance(vector<double> v1, vector<double> v2) {
    double dist = 0;
    for (int i = 0; i < v1.size(); i++) {
        dist += pow((v1.at(i) - v2.at(i)), 2);
    }
    dist = sqrt(dist);
    return dist;
}

double manhattanDistance(vector<double> v1, vector<double> v2) {
    double dist = 0;
    for (int i = 0; i < v1.size(); i++) {
        dist += abs(v1.at(i) - v2.at(i));
    }
    return dist;
}

double chebyshevDistance(vector<double> v1, vector<double> v2) {
    double max = 0;
    double f;
    for (int i = 0; i < v1.size(); i++) {
        f = abs(v1.at(i) - v2.at(i));
        if (f > max) max = f;
    }
    return max;
}

double canberraDistance(vector<double> v1, vector<double> v2) {
    double dist = 0;
    int d;
    for (int i = 0; i < v1.size(); i++) {
        d = abs(v1.at(i)) + abs(v2.at(i));
        if (d > 0) {
            dist += (abs(v1.at(i) - v2.at(i))) / d;
        }
        else {
            // 0 division problem
            return 1.79769e-308;
        }
    }
    return dist;
}

double minkowskiDistance(vector<double> v1, vector<double> v2) {
    double dist = 0;
    for (int i = 0; i < v1.size(); i++) {
        dist += pow(abs(v1.at(i) - v2.at(i)), p_value_minkowski);
    }
    dist = pow(dist, (1.0 / p_value_minkowski));
    return dist;
}
