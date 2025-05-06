//
// Created by sejal on 5/4/2025.
//

#ifndef MATRIX_H
#define MATRIX_H
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

namespace p_matrix
{

    template<class T = long double>

    class matrix
    {
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

        matrix();

        matrix::matrix(size_t row, size_t col) {

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

        matrix(size_t row, size_t col, T val) : mat(row, col) {

            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < col; ++j) {
                    mat[i][j] = val;
                }
            }
        }

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

        vector<T>& operator[](int i) {
            return mat[i];
        }

        friend matrix operator*(const matrix& A, const matrix& B) {

            if (A.col() != B.row()) {
                throw invalid_argument("Multiplication not possible");
            }

            matrix<T> C(A.row(), B.col());

            for (size_t i = 0; i < A.row(); ++i) {
                for (size_t j = 0; j < B.col(); ++j) {
                    for (size_t k = 0; k < A.col(); ++k) {
                        C.mat[i][j] += A.mat[i][k] * B.mat[k][j];
                    }
                }
            }
            return C;
        }

        vector<vector<T> > Cofactor(vector<vector<T>> &matrix, int a, int b, int n) {

            vector<vector<T>> submatrix(n-1, vector<T>(n-1));

            int i = 0, j = 0;

            for (int row = 0; row < n; ++row) {
                for (int col = 0; col < n; ++col) {
                    if (row != a && col != b)
                        submatrix[i][j++] = matrix[row][col];

                    if (j == n-1) {
                        j = 0;
                        i++;
                    }
                }
            }
            return submatrix;
        }

        T Determinant(vector<vector<T>> &matrix, int n) {

            if (n == 1)
                return matrix[0][0];

            T det = 0;
            int sign = 1;

            for (int i = 0; i < n ; ++i) {
                vector<vector<T> >submatrix = Cofactor(matrix, 0, i, n);
                det += sign * matrix[0][i] * Determinant(submatrix, n-1);
                sign = -sign;
            }
            return det;
        }

        vector<vector<T>> adj(vector<vector<T>> &matrix) {

            size_t mat_size = matrix.size();
            vector<vector<T> > adjoint (mat_size, vector<T>(mat_size));
            if (mat_size == 1) {
                adjoint[0][0] = 1;
                return adjoint;
            }

            int sign = 1;
            vector<vector<T> > submatrix(mat_size, vector<T>(mat_size));
            for (int i = 0; i < mat_size; ++i) {
                for (int j = 0; j < mat_size; ++j) {
                    submatrix = Cofactor(matrix, i, j, mat_size);
                    if ((i + j) % 2 == 0)
                        sign = 1;
                    else
                        sign = -1;
                    adjoint[j][i] = sign * Determinant(submatrix, mat_size - 1);
                }
            }
            return adjoint;
        }

        vector<vector<T>> inverse(vector<vector<T>> &matrix) {
            size_t mat_size = matrix.size();
            int det = Determinant(matrix, mat_size);

            if (det == 0) {
                throw invalid_argument("\n Inverse doesn't exist\n");
            }

            vector<vector<T> > adjoint(mat_size, vector<T>(mat_size));
            adjoint = adj(matrix);
            vector<vector<T>> inverse(mat_size, vector<T>(mat_size));
            for (int i = 0; i < mat_size; ++i) {
                for (int j = 0; j < mat_size; ++j) {
                    inverse[i][j] = adjoint[i][j] / float(det);
                }
            }
            return inverse;
        }

        vector<vector<T>> transpose(vector<vector<T>> &matrix) {

            vector<vector<T>> trans(matrix.size(), vector<T>(matrix.size()));
            for (size_t i = 0; i < matrix.size(); ++i) {
                for (size_t j = 0; j < matrix.size(); ++j) {
                    trans[i][j] = matrix[i][j];
                }
            }
            return trans;
        }
    };
}



#endif //MATRIX_H