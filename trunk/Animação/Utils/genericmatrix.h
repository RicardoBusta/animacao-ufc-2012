#ifndef GENERICMATRIX_H
#define GENERICMATRIX_H

#include <vector>

class GenericMatrix
{
public:
    GenericMatrix(int rows_=4, int cols_=4);

    void setZero();

    void set( int row, int col, double val );
    double get( int row, int col );

    GenericMatrix transpose();

    GenericMatrix operator=(GenericMatrix op);

    GenericMatrix debugPrint();
private:
    int rows_;
    int cols_;

    std::vector<double> data_;
};

#endif // GENERICMATRIX_H
