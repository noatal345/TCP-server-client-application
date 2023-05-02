#include "Command3_ClassifyData.h"

Command3_ClassifyData::Command3_ClassifyData(DefaultIO* dio, Data* data){
    this->dio = dio;
    this->data = data;
    this->description = "3. classify data\n";
}

void Command3_ClassifyData::execute(){
    //check if data was uploaded

    if(this->data->classified.size() != 0 && this->data->unclassified.size() != 0){
        // create knn classifier, fit and predict.
        KNeighborsClassifier model(this->data->k, this->data->distance_metric_name);
        model.fit(this->data->classified, this->data->classified_labels);

        for(int i = 0; i < this->data->unclassified.size(); i++){
            string ans = model.predict(this->data->unclassified[i]);
            this->data->unclassified_labels.push_back(ans);
        }
        this->dio->write("classifying data complete\n");
    }
    else{
        this->dio->write("please upload data\n");
    }
}