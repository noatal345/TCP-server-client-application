#include "DataProcessor.h"
#include "input_validation.h"
using namespace std;

vector<string> DataProcessor::readFile() {
    ifstream file(this->fileName);
    vector<string> data;
    if (file) {
        string line = "";

        while (getline(file, line)) {
            string string_vec;
            string_vec = line.substr(0, line.length()-1);
            data.push_back(string_vec);
        }
        file.close();
        this->trainSamplesNumber = data.size();
    }
    return data;
}

vector<string> DataProcessor::readString() {
    vector<string> data;
    // read fileName line by line
    string line = "";
    for (int i = 0; i < this->fileName.length(); i++) {
        if(this->fileName[i] == '\r'){
            continue;
        }
        else if (this->fileName[i] != '\n') {
            line += this->fileName[i];
        } else {
            data.push_back(line);
            line = "";
        }
    }
    this->trainSamplesNumber = data.size();
    return data;
}

bool DataProcessor::get_train_data(vector<string> data, vector<vector<double>>& train, vector<string>& lables) {

    //convert string row into a vector if possible
    for (int i = 0; i < data.size(); i++) {
        char s = ',';
        string lable = "";
        string vec;
        splitData(data[i], vec, lable);
        vector<double> v;
        if (vectorValidation(vec, v, s)) {
            if (i == 0) {
                this->vectorSize = v.size();
            }
            if (lable.size() > 0 && v.size() == this->vectorSize) {
                lables.push_back(lable);
                train.push_back(v);
            }
            else {
                cout << "The number of features in the sample vectors is not equal or lable is empty." << endl;
                return false;
            }
        }
        else {
            return false;
        }

    }
    return true;
}

void DataProcessor::splitData(string d, string& vec, string& lable) {
    bool flag = 1;
    for (int c = d.length(); c >= 0; c--) {
        if (d[c] == ',' && flag) {
            flag = 0;
        }
        if (flag) {
            lable += d[c];
        }
        else {
            vec += d[c];
        }
    }
    reverse(lable.begin(), lable.end());
    reverse(vec.begin(), vec.end());
}

int DataProcessor::getVectorSize() {
    return this->vectorSize;
}

int DataProcessor::gettrainSamplesNumber() {
    return this->trainSamplesNumber;
}