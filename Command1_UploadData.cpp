#include "Command1_UploadData.h"

//this is the first command class
Command1_UploadData::Command1_UploadData(DefaultIO *dio, Data* data) {
    this->dio = dio;
    this->data = data;
    this->description = "1. upload an unclassified csv data file\n";
}

void Command1_UploadData::execute() {
    // train file part
    this->dio->write("Please upload your local train CSV file.\n");
    if(this->dio->error) return; // check if write was successful

    //get the training data file as a string from the client sock
    string train_data = this->dio->read();
    if(this->dio->error) return; // check if read was successful

    if(train_data!="invalid"){

        vector<string> training_data;
        vector<vector<double>> train;
        vector<string> train_labels;
        int vecSize = 0;
        int numberOfSamples = 0;
        // read the train_data string to string vector and then to vector of vectors (train data) and vector of strings (train labels)
        if (!fileReader(train_data, training_data, train, train_labels, vecSize, numberOfSamples)) {
            //problem reading train_data string
            this->dio->write("invalid input\n");
            return;
        }
        else{
            this->dio->write("Upload complete.\n");
            if(this->dio->error) return; // check if write was successful
            // save the train data in the data object


            // test file part
            this->dio->write("Please upload your local test CSV file.\n");
            if(this->dio->error) return; // check if write was successful

            //get the test_data data file as a string from the client sock
            string test_data = this->dio->read();
            if(this->dio->error) return; // check if read was successful

            if(test_data!="invalid"){

                vector<vector<double>> test_data_vec;
                // read the test_data string to vector of vectors (test data)
                if (!unclassifiedFileValidation(test_data ,test_data_vec,vecSize)){
                    //test string is invalid
                    this->dio->write("invalid input\n");
                }
                else{
                    this->data->unclassified = test_data_vec;
                    this->data->classified = train;
                    this->data->classified_labels = train_labels;
                    this->data->vec_size = vecSize;
                    // empty the unclassified labels vector
                    this->data->unclassified_labels.clear();
                    this->dio->write("Upload complete.\n");
                }
            } else {
                // invalid path/ file is empty
                this->dio->write("invalid input\n");
                return;
            }
        }
    } else {
        // invalid path/ file is empty
        this->dio->write("invalid input\n");
        return;
    }
}