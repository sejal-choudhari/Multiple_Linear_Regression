//
// Created by sejal on 5/4/2025.
//
#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H
#include "matrix.h"
#include "data.h"


using namespace std;
using namespace p_matrix;
using namespace data;

namespace linReg {
    class linearRegression {
    public:
        explicit linearRegression(Data &ds) : d(ds) {
            fit();
            r2();
        }

    private:
        Data d;
        Matrix<long double> x_train, y_train;
        Matrix<long double> beta_;
        Matrix<long double> coef_;
        long double y_mean = 0;
        long double r2_score_ = 0;
        long double intercept_ = 0;


        void fit() {
            x_train.resize(d.X_Train.size(), d.X_Train[0].size() + 1);
            y_train.resize(d.Y_Train.size(), 1);

            //inserting 1
            for (int i = 0; i < x_train.row(); ++i) {
                x_train[i][0] = 1;
            }

            //x-train
            for (int i = 0; i < x_train.row(); ++i) {
                for (int j = 1; j < x_train.col(); ++j) {
                    x_train[i][j] = d.X_Train[i][j - 1];
                }
            }

            //y-train
            for (int i = 0; i < d.Y_Train.size(); ++i) {
                y_train[i][0] = d.Y_Train[i];
            }

            //calculating betas
            Matrix<long double> XT_X = x_train.transpose() * x_train;
            beta_ = (XT_X).inverse() * x_train.transpose() * y_train;

            //calculating coefficients
            coef_.resize(beta_.row() - 1, 1);
            cout << "Coefficients: ";
            for (int i = 1; i < beta_.row(); ++i) {
                coef_[i - 1][0] = beta_[i][0];
                cout << coef_[i - 1][0] << "  ";
            }
            cout << endl;

            //intercept
            intercept_ = beta_[0][0];
        }


        void Mean() {
            for (int i = 0; i < y_train.row(); ++i) {
                y_mean += y_train[i][0];
            }
            y_mean = y_mean / y_train.row();
        }


        void r2() {
            Mean();
            long double sum = 0;
            long double estimated_sum = 0;
            for (int i = 0; i < y_train.row(); ++i) {
                sum += pow(y_train[i][0] - y_mean, 2);
                vector<long double> vec(x_train[i].begin() + 1, x_train[i].end());
                estimated_sum += pow((predict(vec) - y_mean), 2);
            }

            r2_score_ = estimated_sum / sum;
        }


        long double predict(vector<long double> x) {
            Matrix<long double> prediction(1, coef_.row());
            for (int i = 0; i < prediction.col(); ++i) {
                prediction[0][i] = x[i];
            }
            prediction = prediction * coef_;
            prediction[0][0] += intercept_;
            return prediction[0][0];
        }

        Matrix<long double> beta() {
            return beta_;
        }


        Matrix<long double> coef() {
            return coef_;
        }

    public:
        long double intercept() const {
            return intercept_;
        }

        void r2_score() const {
            cout << setprecision(14) << r2_score_ << endl;
        }
    };
}


#endif //LINEARREGRESSION_H
