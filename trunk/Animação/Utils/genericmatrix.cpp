#include "genericmatrix.h"

#include <cstring>
#include <cstdlib>
#include <cmath>

#include <iostream>

GenericMatrix::GenericMatrix(int rows_, int cols_){
    this->rows_ = rows_;
    this->cols_ = cols_;

    data_.resize(rows_*cols_);
}


void GenericMatrix::setIdentity()
{
    for(int i=0;i<rows_;i++){
        for(int j=0;j<cols_;j++){
            if(i!=j)
                data_[ ((i*cols_) + j) ] = 0;
            else
                data_[ ((i*cols_) + j) ] = 1;
        }
    }
}

void GenericMatrix::setZero()
{
    for(int i=0;i<rows_;i++){
        for(int j=0;j<cols_;j++){
            data_[ ((i*cols_) + j) ] = 0;
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

void GenericMatrix::set(int index, double val)
{
    data_[ index ] = val;
}


double GenericMatrix::get(int index)
{
    return data_[ index ];
}


GenericMatrix GenericMatrix::transpose()
{
    GenericMatrix result(cols_,rows_);

    for(int i=0;i<rows_;i++){
        for(int j=0;j<cols_;j++){
            result.data_[ ((j*rows_) + i) ] = data_[ ((i*cols_) + j) ];
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

GenericMatrix GenericMatrix::operator* (GenericMatrix op)
{
    if( this->cols_ != op.rows_ ) return GenericMatrix(1,1);

    GenericMatrix result(this->rows_,op.cols_);

    for(int i=0;i<this->rows_;i++){
        for(int j=0;j<op.cols_;j++){
            for(int k=0;k<this->cols_;k++){
                result.data_[ ((i*result.cols_) + j) ] += this->data_ [  ((i*this->cols_) + k) ] * op.data_[  ((k*op.cols_) + j) ];
            }
        }
    }

    return result;
}


void GenericMatrix::debugPrint()
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


GenericMatrix GenericMatrix::inverse()
{
    // Based on comment from http://forums.codeguru.com/showthread.php?262248-Algorithm-for-matrix-inversion

    // A = input matrix (n x n)
    // n = dimension of A
    // AInverse = inverted matrix (n x n)
    // This function inverts a matrix based on the Gauss Jordan method.
    // The function returns 1 on success, 0 on failure.
    if(rows_ != cols_) return GenericMatrix(1,1);

    //double *AInverse = new double[ (rows_*cols_) ];
    GenericMatrix AInverse(rows_,cols_);

    std::vector<double> A = data_;
    int n = rows_;

    int i, j, iPass, imx, icol, irow;
    double det, temp, pivot, factor;
    double* ac = (double*)calloc(n*n, sizeof(double));
    det = 1;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            AInverse.data_[n*i+j] = 0;
            ac[n*i+j] = A[n*i+j];
        }
        AInverse.data_[n*i+i] = 1;
    }

    // The current pivot row is iPass.
    // For each pass, first find the maximum element in the pivot column.
    for (iPass = 0; iPass < n; iPass++)
    {
        imx = iPass;
        for (irow = iPass; irow < n; irow++)
        {
            if (fabs(A[n*irow+iPass]) > fabs(A[n*imx+iPass])) imx = irow;
        }
        // Interchange the elements of row iPass and row imx in both A and AInverse.
        if (imx != iPass)
        {
            for (icol = 0; icol < n; icol++)
            {
                temp = AInverse.data_[n*iPass+icol];
                AInverse.data_[n*iPass+icol] = AInverse.data_[n*imx+icol];
                AInverse.data_[n*imx+icol] = temp;

                if (icol >= iPass)
                {
                    temp = A[n*iPass+icol];
                    A[n*iPass+icol] = A[n*imx+icol];
                    A[n*imx+icol] = temp;
                }
            }
        }

        // The current pivot is now A[iPass][iPass].
        // The determinant is the product of the pivot elements.
        pivot = A[n*iPass+iPass];
        det = det * pivot;
        if (det == 0)
        {
            free(ac);
            return 0;
        }

        for (icol = 0; icol < n; icol++)
        {
            // Normalize the pivot row by dividing by the pivot element.
            AInverse.data_[n*iPass+icol] = AInverse.data_[n*iPass+icol] / pivot;
            if (icol >= iPass) A[n*iPass+icol] = A[n*iPass+icol] / pivot;
        }

        for (irow = 0; irow < n; irow++)
            // Add a multiple of the pivot row to each row.  The multiple factor
            // is chosen so that the element of A on the pivot column is 0.
        {
            if (irow != iPass) factor = A[n*irow+iPass];
            for (icol = 0; icol < n; icol++)
            {
                if (irow != iPass)
                {
                    AInverse.data_[n*irow+icol] -= factor * AInverse.data_[n*iPass+icol];
                    A[n*irow+icol] -= factor * A[n*iPass+icol];
                }
            }
        }
    }

    free(ac);
    return AInverse;
}


int GenericMatrix::rows()
{
    return rows_;
}

int GenericMatrix::cols()
{
    return cols_;
}
