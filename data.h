//
// Created by sejal on 5/4/2025.
//
#include <iostream>

using namespace std;

#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <bits/stdc++.h>

namespace data {
    inline vector<vector<string> > data;

    class Data {
    public:
        vector<vector<long double> > X_Train;
        vector<long double> Y_Train;

        Data(const string &path) {
            readFile(path);
        };

        //reading csv file
        static void readFile(const string &path) {
            fstream filePtr;
            filePtr.open(path, ios::in);
            if (!filePtr.is_open()) {
                cout << "Error opening file" << endl;
                return;
            }

            string line, num;

            while (getline(filePtr, line)) {
                vector<string> row;
                row.clear();
                stringstream ss(line);

                while (getline(ss, num, ',')) {
                    row.push_back(num);
                }

                data.push_back(row);
            }
            filePtr.close();
        }

        //Copying the content from csv file
        //x-train
        void x_train(initializer_list<string> args) {
            vector<int> index;
            vector<string> x_header;
            vector argvec(args);

            for (const auto &i: argvec) {
                for (int j = 0; j < data[0].size(); ++j) {
                    if (i == data[0][j])
                        index.push_back(j);
                    x_header.push_back(i);
                }
            }

            X_Train.resize(data.size() - 1, vector<long double>(index.size()));

            for (int i = 0; i < index.size(); ++i) {
                for (int j = 1; j < data.size(); ++j) {
                    try {
                        X_Train[j - 1][i] = stold(data[j][index[i]]);
                    } catch (const std::invalid_argument &e) {
                        cout << "Invalid argument for conversion: " << data[j][i] << endl;
                    }catch (const std::out_of_range &e) {
                        cout << "out of range for conversion: " << data[j][i] << endl;
                    }
                }
            }
        }

        string trim(const string &str) {
            size_t first = str.find_first_not_of(' ');
            if (string::npos == first) return ""; // no content
            size_t last = str.find_last_not_of(' ');
            return str.substr(first, (last - first + 1));
        }

        //y-train
        void y_train(const string &y) {
            string y_header = y;
            int index = -1;
            for (int i = 0; i < data.size(); ++i) {
                if (data[0][i] == y_header) {
                    index = i;
                }
            }

            Y_Train.resize(data.size() - 1);
            if (index != -1) {
                for (int i = 1; i < data.size(); ++i) {
                    Y_Train[i - 1] = stold(data[i][index]);
                }
            }
        }
    };
}


#endif //DATA_H
