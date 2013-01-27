#ifndef GENERICMATRIX_H
#define GENERICMATRIX_H

#include <vector>
#include <string>

class GenericMatrix
{
public:
    GenericMatrix(int rows_=4, int cols_=4);

    void setIdentity();
    void setZero();

    void set( int row, int col, double val );
    double get( int row, int col );
    void set( int index, double val );
    double get( int index );

    double setData(std::vector<double> data);

    int rows();
    int cols();

    GenericMatrix transpose();
    GenericMatrix inverse();

    GenericMatrix operator= (GenericMatrix op);
    GenericMatrix operator* (GenericMatrix op);

    void debugPrint(std::string debugtext);
protected:
    int rows_;
    int cols_;

    std::vector<double> data_;
};

#endif // GENERICMATRIX_H
