#include "Command4_DisplayResults.h"

Command4_DisplayResults::Command4_DisplayResults(DefaultIO* dio, Data* data){
    this->dio = dio;
    this->data = data;
    this->description = "4. display results\n";
}

void Command4_DisplayResults::execute(){
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
        string results = "";
        for(int i = 0; i < this->data->unclassified_labels.size(); i++){
            results+=to_string(i+1)+"   "+this->data->unclassified_labels[i].substr(0, this->data->unclassified_labels[i].length()-1) + "\n";
        }
        this->dio->write(results+"Done.\n");
    }
}