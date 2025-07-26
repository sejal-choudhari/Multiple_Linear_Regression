//
// Created by sejal on 5/4/2025.
//

#include <iostream>

#include "data.h"
#include "linearRegression.h"


using namespace std;
using namespace ::data;
using namespace linReg;

int main() {
    Data obj_data("C:/Users/sejal/CLionProjects/MultipleLinearReg/file.csv");

    initializer_list<string> X = {"R&D Spend", "Administration", "Marketing Spend"};
    obj_data.x_train(X);
    obj_data.y_train("Profit");
    linearRegression regression(obj_data);
    cout << "Intercept: " << regression.intercept() << endl;
    cout << "R2 Score: ";
    regression.r2_score();
}


