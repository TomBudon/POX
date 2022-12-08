#include "LocalLinearAlgebra.h"

LocalLinearAlgebra::Matrix::Matrix(int nrow, int ncolumn, double value) {
    n_row = nrow;
    n_column = nrow;

    v = Vector(nrow * ncolumn);

    fill(v.begin(), v.end(), value);
}

void LocalLinearAlgebra::Matrix::add_value(int row, int column, double value) {
    v[row * n_row + column] = value;
}


void LocalLinearAlgebra::mult(Matrix& A_local, Vector& x_local, Vector& tmp_local) {
    for (size_t i = 0; i < x_local.size(); i++)
    {
        double tmp = 0;
        for (size_t j = 0; j < A_local.n_row; j++)
        {
            tmp += x_local[i] * A_local.v[i*A_local.n_row + j];
        }
        tmp_local[i] = tmp;
    }
}

void LocalLinearAlgebra::copy(Vector& tmp_local, Vector& r_local) { 
    // std::copy(tmp_local.begin(), tmp_local.end(), back_inserter(r_local)); 
    for (size_t i = 0; i < r_local.size(); i++)
    {
        r_local[i] = tmp_local[i];
    }
}

void LocalLinearAlgebra::axpy(double value, Vector& b_local, Vector& r_local) {
    for (size_t i = 0; i < r_local.size(); i++)
    {
        r_local[i] += value * b_local[i];
    }
}

double LocalLinearAlgebra::norm2(Vector& r_local) {
    double norm = 0;
    for (size_t i = 0; i < r_local.size(); i++)
    {
        norm += pow( r_local[i], 2);
    }
    return sqrt(norm);   
}