//
// Created by USER on 21/01/2023.
//

#include "Command5_downloadResults.h"


Command5_downloadResults::Command5_downloadResults(DefaultIO* dio, Data* data){
    this->dio = dio;
    this->data = data;
    this->description = "5. download results\n";
}

void Command5_downloadResults::execute(){
    //check if data was uploaded
    if(this->data->classified.size()==0 || this->data->unclassified.size()==0){
        this->dio->write("please upload data\n");
    }
        //check if data was classified
    else if(this->data->unclassified_labels.size() == 0){
        this->dio->write("please classify the data\n");
    }
    else{
        //write the results
        string results = "$";
        for(int i = 0; i < this->data->unclassified_labels.size(); i++){
                results+=to_string(i+1)+"   "+this->data->unclassified_labels[i].substr(0, this->data->unclassified_labels[i].length()-1) + "\n";
        }
        // send classification with path and file flag word
        results += "*";
        string filepath = this->dio->read();
        results += filepath;
        results += "#";
        this->dio->write(results);
        return;
    }
}