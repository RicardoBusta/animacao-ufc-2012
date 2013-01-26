#include "matrix4d.h"

Matrix4D::Matrix4D(){
    data_.resize(16);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==j){
                data_[((i*4)+j)]=1;
            }else{
                data_[((i*4)+j)]=0;
            }
        }
    }
}


Matrix4D::Matrix4D(qglviewer::Vec translation)
{
    data_.resize(16);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==j){
                data_[((i*4)+j)]=1;
            }else{
                data_[((i*4)+j)]=0;
            }
        }
    }

    data_[3] = translation.x;
    data_[7] = translation.y;
    data_[11] = translation.z;
}


Matrix4D::Matrix4D(qglviewer::Quaternion orientation)
{
    data_.resize(16);
    const GLdouble *matrix = orientation.matrix();
    for(int i=0;i<16;i++){
        data_[i] = matrix[i];
    }
}


Matrix4D::~Matrix4D()
{
    data_.clear();
}


Matrix4D Matrix4D::operator *(Matrix4D op)
{
    Matrix4D result;

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            result.data_[((i*4)+j)]=0;
            for(int k=0;k<4;k++){
                result.data_[((i*4)+j)] += this->data_[((i*4)+k)] * op.data_[((k*4)+j)];
            }
        }
    }

    return result;
}


Matrix4D Matrix4D::operator =(Matrix4D op)
{
    this->data_ = op.data_;
    return *this;
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
            res[i] += ( data_[((i*4)+k)] * temp[k] );
        }
    }

    result.x = res[0];
    result.y = res[1];
    result.z = res[2];

    return result;
}
