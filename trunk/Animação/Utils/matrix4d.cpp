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
            set(j,i,matrix[((i*4)+j)]);
        }
    }
}

qglviewer::Vec Matrix4D::apply(qglviewer::Vec op, bool vector)
{
    qglviewer::Vec result;
    GenericMatrix thisMatrix = *this;
    GenericMatrix temp = GenericMatrix(4,1);
    GenericMatrix res;
    temp.set(0,0, op.x);
    temp.set(1,0, op.y);
    temp.set(2,0, op.z);
    if(vector){
        temp.set(3,0,0);
    }else{
        temp.set(3,0,1);
    }

    for(int i=0;i<4;i++){
        double resv = 0;
        for(int k=0;k<4;k++){
            resv += ( get(i,k) * temp.get(k,0) );
        }
        res.set(i,0,resv);
    }

    result.x = res.get(0,0);
    result.y = res.get(1,0);
    result.z = res.get(2,0);

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
            double val = 0;
            for(int k=0;k<this->cols_;k++){
                val += this->get(i,k) * op.get(k,j);
            }
            result.set(i,j,val);
        }
    }

    return result;
}
