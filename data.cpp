//
// Created by sejal on 5/4/2025.
//
#include <iostream>

using namespace std;

#ifndef DATA_H
#define DATA_H

#include <stdlib.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <cstdlib>
#include <stdexcept>

vector<vector<string>> Data;

class data {

    public:
    vector<vector<long double>> X_Train;
    vector<long double> Y_Train;

    //Copying the content of 1st column from csv file
    void x_train(initializer_list<string> args) {
        vector<int> index;
        vector<string> x_header;
        vector<string> argvec(args);
        for (int i = 0; i < argvec.size(); ++i) {
            for (int j = 0; j < Data[0].size(); ++j) {
                if (argvec[i] == Data[0][j])
                    index.push_back(j);
                x_header.push_back(argvec[i]);
            }
        }

        X_Train.resize(Data.size() - 1, vector<long double>(index.size()));
    }

};



#endif //DATA_H
