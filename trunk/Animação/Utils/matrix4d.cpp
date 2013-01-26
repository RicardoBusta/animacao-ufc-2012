#include "matrix4d.h"

Matrix4D::Matrix4D():GenericMatrix(4,4){
}


Matrix4D::Matrix4D(qglviewer::Vec translation):GenericMatrix(4,4)
{
    setIdentity();
    this->set(0,3,translation.x);
    this->set(1,3,translation.y);
    this->set(2,3,translation.z);
}


Matrix4D::Matrix4D(qglviewer::Quaternion orientation):GenericMatrix(4,4)
{

    const GLdouble *matrix = orientation.matrix();
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            set(i,j,matrix[((i*4)+j)]);
        }
    }
}

qglviewer::Vec Matrix4D::apply(qglviewer::Vec op, bool vector)
{
    qglviewer::Vec result;
    double temp[4], res[4];
    temp[0] = op.x;
    temp[1] = op.y;
    temp[2] = op.z;
    if(vector){
        temp[3] = 0;
    }else{
        temp[3] = 1;
    }

    for(int i=0;i<4;i++){
        res[i] = 0;
        for(int k=0;k<4;k++){
            res[i] += ( get(i,k) * temp[k] );
        }
    }

    result.x = res[0];
    result.y = res[1];
    result.z = res[2];

    return result;
}

Matrix4D Matrix4D::operator =(Matrix4D op)
{
    this->rows_ = op.rows_;
    this->cols_ = op.cols_;

    this->data_ = op.data_;

    return *this;
}

Matrix4D Matrix4D::operator *(Matrix4D op)
{
    if( this->cols_ != op.rows_ ) return Matrix4D();

    Matrix4D result;

    for(int i=0;i<this->rows_;i++){
        for(int j=0;j<op.cols_;j++){
            for(int k=0;k<this->cols_;k++){
                result.data_[ ((i*result.cols_) + j) ] += this->data_ [  ((i*this->cols_) + k) ] * op.data_[  ((k*op.cols_) + j) ];
            }
        }
    }

    return result;
}
