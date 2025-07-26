//
// Created by sejal on 5/11/2025.
//

#ifndef MATRIX_H
#define MATRIX_H


#include <cmath>
#include <stdexcept>
#include <vector>


using namespace std;
using namespace data;

namespace p_matrix {
    template<class T = long double>

    class Matrix {
        vector<vector<T> > mat;

    public:
        size_t size() const {
            return mat.size();
        }

        size_t row() const {
            return mat.size();
        }

        size_t col() const {
            return mat[0].size();
        }


        Matrix(size_t row, size_t col) {
            if (row == 0 && col == 0) {
                throw invalid_argument("Invalid Dimensions");
            }

            mat.resize(row);

            for (int i = 0; i < mat.size(); ++i) {
                mat[i].resize(col);
            }

            for (int i = 0; i < mat.size(); ++i) {
                for (int j = 0; j < mat[i].size(); ++j) {
                    mat[i][j] = 0;
                }
            }
        }

        Matrix(size_t row, size_t col, T val) : mat(row, col) {
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < col; ++j) {
                    mat[i][j] = val;
                }
            }
        }

        Matrix() = default;

        void resize(size_t row, size_t col) {
            mat.resize(row);
            for (int i = 0; i < mat.size(); ++i)
                mat[i].resize(col);
        }

        void resize(size_t row, size_t col, T val) {
            resize(row, col);
            for (int i = 0; i < mat.size(); ++i) {
                for (int j = 0; j < col; ++j) {
                    mat[i][j] = val;
                }
            }
        }

        vector<T> &operator[](int i) {
            return static_cast<vector<T> &>(mat[i]);
        }

        friend Matrix operator*(const Matrix<T> &A, const Matrix<T> &B) {
            if (A.col() != B.row()) {
                cout << "Size:" << A.col() << "!=" << B.row() << endl;
                throw invalid_argument("Matrix dimensions mismatch for multiplication");
            }

            Matrix<T> C(A.row(), B.col());

            for (size_t i = 0; i < A.row(); ++i) {
                for (size_t j = 0; j < B.col(); ++j) {
                    for (size_t k = 0; k < A.col(); ++k) {
                        C.mat[i][j] += A.mat[i][k] * B.mat[k][j];
                    }
                }
            }
            return C;
        }

        Matrix &operator=(Matrix<T> const &a) {
            this->resize(a.row(), a.col());
            this->mat = a.mat;
            return *this;
        }


        Matrix<T> transpose() {
            Matrix<T> trans(this->col(), this->row());
            for (size_t i = 0; i < this->row(); ++i) {
                for (size_t j = 0; j < this->col(); ++j) {
                    trans[j][i] = this->mat[i][j];
                }
            }
            return trans;
        }

        Matrix<T> inverse() {
            Matrix<T> inverse(this->row(), this->col());
            size_t size = this->mat.size();
            Matrix<T> augment(size, 2 * size);
            for (size_t i = 0; i < size; ++i) {
                for (size_t j = 0; j < size; ++j) {
                    augment[i][j] = this->mat[i][j];
                }
                //making diagonals 1
                augment[i][i + size] = 1.0;
            }

            for (size_t i = 0; i < size; ++i) {
                T max_element = abs(augment[i][i]);
                size_t max_row = i;
                for (size_t j = i + 1; j < size; ++j) {
                    if (abs(augment[j][i]) > max_element) {
                        max_element = abs(augment[j][i]);
                        max_row = j;
                    }
                }

                if (i != max_row) {
                    swap(augment[i], augment[max_row]);
                }

                if (abs(augment[i][i]) < 1e-10) {
                    throw invalid_argument("Matrix is singular");
                }

                long double pivot = augment[i][i];
                for (size_t j = i; j < 2 * size; ++j) {
                    augment[i][j] = static_cast<T>(augment[i][j] / pivot);
                }

                for (size_t k = 0; k < size; ++k) {
                    if (k != i && abs(augment[k][i]) > 1e-10) {
                        double temp = augment[k][i];
                        for (size_t l = i; l < 2 * size; ++l) {
                            augment[k][l] -= temp * augment[i][l];
                        }
                    }
                }
            }


            for (size_t i = 0; i < size; ++i) {
                for (size_t j = 0; j < size; ++j) {
                    inverse[i][j] = augment[i][j + size];
                }
            }


            return inverse;
        }
    };
}


#endif //MATRIX_H
