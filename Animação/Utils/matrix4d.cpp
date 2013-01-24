#include "matrix4d.h"

Matrix4D::Matrix4D(){
    data = new double[16];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==j){
                data[i+4*j]=1;
            }else{
                data[i+4*j]=0;
            }
        }
    }
}

Matrix4D::Matrix4D(qglviewer::Vec translation)
{
    data = new double[16];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==j){
                data[i+4*j]=1;
            }else{
                data[i+4*j]=0;
            }
        }
    }

    data[3] = translation.x;
    data[7] = translation.y;
    data[11] = translation.z;
}

Matrix4D::Matrix4D(qglviewer::Quaternion orientation)
{
    data = new double[16];
    memcpy(data, orientation.matrix(), sizeof(GLdouble)*16);
}

Matrix4D::~Matrix4D()
{
    if(data !=NULL){
        //delete data;
        data = NULL;
    }
}

Matrix4D Matrix4D::operator *(Matrix4D op)
{
    Matrix4D result;

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            result.data[(i*4)+j] = 0;
            for(int k=0;k<4;k++){
                result.data[(i*4)+j] += this->data[(i*4)+k] * op.data[(k*4)+j];
            }
        }
    }

    return result;
}

Matrix4D Matrix4D::operator =(Matrix4D op)
{
    memcpy(this->data, op.data, sizeof(GLdouble)*16);
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
            res[i] += ( data[(4*i)+k] * temp[k] );
        }
    }

    result.x = res[0];
    result.y = res[1];
    result.z = res[2];

    return result;
}
