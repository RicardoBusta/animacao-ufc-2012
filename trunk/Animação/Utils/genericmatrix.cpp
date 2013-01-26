#include "genericmatrix.h"

#include <cstring>

#include <iostream>

GenericMatrix::GenericMatrix(int rows_, int cols_){
    this->rows_ = rows_;
    this->cols_ = cols_;

    data_.resize(rows_*cols_);
}


void GenericMatrix::setZero()
{
    for(int i=0;i<rows_;i++){
        for(int j=0;j<cols_;j++){
            data_[ ((i*cols_) + j) ] = ((i*cols_) + j);
        }
    }
}


void GenericMatrix::set(int row, int col, double val)
{
    data_[ ((row*cols_) + col) ] = val;
}


double GenericMatrix::get(int row, int col)
{
    return data_[ ((row*cols_) + col) ];
}


GenericMatrix GenericMatrix::transpose()
{
    GenericMatrix result(cols_,rows_);

    for(int i=0;i<rows_;i++){
        for(int j=0;j<cols_;j++){
            result.data_[ ((j*cols_) + i) ] = data_[ ((i*cols_) + j) ];
        }
    }

    return result;
}


GenericMatrix GenericMatrix::operator =(GenericMatrix op)
{
    this->rows_ = op.rows_;
    this->cols_ = op.cols_;

    this->data_ = op.data_;

    return *this;
}


GenericMatrix GenericMatrix::debugPrint()
{
    std::cout << "==matrix==" << std::endl;

    for(int i=0;i<rows_;i++){
        for(int j=0;j<cols_;j++){
            std::cout << data_[ ((i*cols_) + j) ] << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << "==========" << std::endl;
}
