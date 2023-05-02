#ifndef EX3_KNEIGHBORSCLASSIFIER_H
#define EX3_KNEIGHBORSCLASSIFIER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <unordered_map>
#include "distance_functions.h"
using namespace std;

class KNeighborsClassifier {
private:
    int k;
    string distance_metric_name;
    vector<vector<double>> x_train;
    vector<string> y_train;

    /**
     * Find distances from one vector to all others in the training set
     *
     * \param x_sample The sample we want to classify (A vector of doubles)
     * \return A vector of tuples where each tuple contain the distance of
     *         the sample from a vector in the training set (double) and the vector label (string)
     */
    vector<tuple<double, string>> DistanceFromData(vector<double> x_sample);

    /**
     * Find the k nearest neighbors to the sample we want to classify
     *
     * \param distanceOfSampleFromData A vector of tuples where each tuple contain the distance of
     *								   the sample we want to classify from a vector in the training
     *								   set (double) and the vector label (string)
     * \return A vector of tuples that is a subset of the input vector that contains only the k
     *		   neighboring vectors from the training set
     */
    vector<tuple<double, string>> findKNearestNeighbors(vector<tuple<double, string>> distanceOfSampleFromData);

    /**
     * Finds the most common label
     *
     * \param kNearestNeighbors A vector of the k neareat neighbors. Each neighbor is represented
     *						    by a tuple that contains the distance from the sample and the label
     * \return the most common label among the k neareat neighbors
     */
    string mostFrequentLabel(vector<tuple<double, string>> kNearestNeighbors);

public:
    /**
     * constructor.
     *
     * \param n_neighbors The k parameter that will be used in the model (The number of
     *					  nearest neighbors according to which the classification is chosen)
     * \param distance_metric The distance metric according to which the neighbors of the
     *						  sample from the tarining set will be calculated
     */
    KNeighborsClassifier(int n_neighbors, string distance_metric);

    /**
     * Saves the data vectors ​​of the training set and their labeling
     *
     * \param x the data vectors ​​of the training set
     * \param y the labels of the training set
     */
    void fit(vector<vector<double>> x, vector<string> y);

    /**
     * predict label of a sample vector according to KNN algorithm.
     *
     * \param The sample vector we want to classify
     * \return The predicted label
     */
    string predict(vector<double> x_sample);
};


#endif //EX3_KNEIGHBORSCLASSIFIER_H
