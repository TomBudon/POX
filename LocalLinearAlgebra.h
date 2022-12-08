#ifndef LOCAL_LINEAR_ALGEBRA_H
#define LOCAL_LINEAR_ALGEBRA_H

#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>

class LocalLinearAlgebra
{
public:
    using Vector = std::vector<double>;

    class Matrix
    {
    public :

        int n_row = 0;
        int n_column = 0;
        Vector v;

        Matrix(int nrow, int ncolumn, double value);
        void add_value(int row, int column, double value);
    };


    void static mult(Matrix& A_local, Vector& x_local, Vector& tmp_local);

    void static copy(Vector& tmp_local, Vector& r_local);

    void static axpy(double, Vector& b_local, Vector& r_local);

    double static norm2(Vector& r_local);

};

struct Norm {
    int norm;
    int norm_local;
};


#endif