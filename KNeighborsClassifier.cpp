#include "KNeighborsClassifier.h"
using namespace std;

vector<tuple<double,string>> KNeighborsClassifier::DistanceFromData(vector<double> x_sample) {
    vector<tuple<double, string>> distanceOfSampleFromData;

    if (this->distance_metric_name == "AUC") {
        for (int i = 0; i < this->x_train.size(); i++) {
            distanceOfSampleFromData.push_back(make_tuple(euclideanDistance(this->x_train[i], x_sample), this->y_train[i]));
        }
    }
    else if (this->distance_metric_name == "MAN"){
        for (int i = 0; i < this->x_train.size(); i++) {
            distanceOfSampleFromData.push_back(make_tuple(manhattanDistance(this->x_train[i], x_sample), this->y_train[i]));
        }
    }
    else if (this->distance_metric_name == "CHB") {
        for (int i = 0; i < this->x_train.size(); i++) {
            distanceOfSampleFromData.push_back(make_tuple(chebyshevDistance(this->x_train[i], x_sample), this->y_train[i]));
        }
    }
    else if (this->distance_metric_name == "CAN") {
        for (int i = 0; i < this->x_train.size(); i++) {
            distanceOfSampleFromData.push_back(make_tuple(canberraDistance(this->x_train[i], x_sample), this->y_train[i]));
        }
    }
    else if (this->distance_metric_name == "MIN") {
        for (int i = 0; i < this->x_train.size(); i++) {
            distanceOfSampleFromData.push_back(make_tuple(minkowskiDistance(this->x_train[i], x_sample), this->y_train[i]));
        }
    }
    return distanceOfSampleFromData;
}

vector<tuple<double, string>> KNeighborsClassifier::findKNearestNeighbors(vector<tuple<double, string>> distanceOfSampleFromData) {
    // sort by the first item in the tuple- the distance
    sort(distanceOfSampleFromData.begin(), distanceOfSampleFromData.end());
    // create a vector of only the k first elements
    vector<tuple<double, string>> kNearestNeighbors = { distanceOfSampleFromData.begin(),distanceOfSampleFromData.begin() + this->k };
    return kNearestNeighbors;
}

string KNeighborsClassifier::mostFrequentLabel(vector<tuple<double, string>> kNearestNeighbors) {
    unordered_map<string, int> countOfLabel;
    // Count how many times each label appears
    for (int i = 0; i < kNearestNeighbors.size(); i++) {
        countOfLabel[get<1>(kNearestNeighbors[i])]++;
    }
    int maxCount = 0;
    string labelOfMax;
    // find the one that appears the most times
    for (auto i : countOfLabel) {
        if (maxCount < i.second) {
            labelOfMax = i.first;
            maxCount = i.second;
        }
    }
    return labelOfMax;
}

KNeighborsClassifier::KNeighborsClassifier(int n_neighbors, string distance_metric) :
        k(n_neighbors),
        distance_metric_name(distance_metric)
{}

void KNeighborsClassifier::fit(vector<vector<double>> x, vector<string> y) {
    this->x_train = x;
    this->y_train = y;
}

string KNeighborsClassifier::predict(vector<double> x_sample) {
    return mostFrequentLabel(findKNearestNeighbors(DistanceFromData(x_sample)));
}