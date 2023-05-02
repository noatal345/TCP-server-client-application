#include "Command2_AlgorithmSettings.h"

Command2_AlgorithmSettings::Command2_AlgorithmSettings(DefaultIO* dio, Data* data){
    this->dio = dio;
    this->data = data;
    this->description = "2. algorithm settings\n";
}

void Command2_AlgorithmSettings::execute(){
    string currSettings = "The current KNN parameters are: K = " + to_string(this->data->k) + ", distance metric = " + this->data->distance_metric_name + "\n";
    dio->write(currSettings);
    if(this->dio->error) return; // check if write was successful

    string user_input = dio->read();
    if(this->dio->error) return; // check if read was successful

    //check if user entered "enter" or not
    if(user_input != "enter"){
        string distance_metric_name = "";
        string str_k = "";
        int k;
        splitAlgorithmSettings(user_input, distance_metric_name, str_k);
        // validation

        string message = "";
        if (!DistFuncValid(distance_metric_name)){
            message+= "invalid value for metric\n";
        }

        //check if k is valid
        if(!kValidation(str_k, this->data->vec_size ,k)){
            message+= "invalid value for K\n";
        }

        //set the distance metric name inside data
        if(message == ""){
            this->data->k = k;
            this->data->distance_metric_name = distance_metric_name;
            return;
        }

        //write error message otherwise
        dio->write(message);
        return;
    }
}
