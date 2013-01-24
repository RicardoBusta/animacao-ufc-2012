#include "matrix4f.h"
#include <stdio.h>

Matrix4f::Matrix4f()
{
    for(int i=0;i<16;i++){
        if(i%5==0){
            matrix[i]=1;
        }else{
            matrix[i]=0;
        }
    }
}

Matrix4f::Matrix4f(double vet[16])
{
    for(int i=0;i<16;i++) matrix[i] = vet[i];
}

void Matrix4f::setMatrix4f(double vet[16])
{
    for(int i=0;i<16;i++) matrix[i] = vet[i];
}


//void Matrix4f::set(Matrix4f *matrix)
//{
//    memcpy(this->matrix, matrix->matrix, 16*sizeof(float));
//}

double * Matrix4f::getMatrix()
{
    return matrix;
}

void Matrix4f::showMatrix4f()
{
    for(int i=0;i<16;i++){
        if(i%4==0)
            printf("\n");
        printf(" %.3f ",matrix[i]);
    }
    printf("\n");
}

void Matrix4f::get(double output[]) const
{
    memcpy(output, matrix, 16*sizeof(double));
}

double Matrix4f::get(int index) const
{
    if(index > 0 and index < 16){
        return matrix[index];
    }else{
        return 0;
    }
}

void Matrix4f::multMatrix2(Matrix4f a, Matrix4f b, double output[])
{
    Matrix4f m;
    m.matrix[0] = a.matrix[0] * b.matrix[0] + a.matrix[1] * b.matrix[4] + a.matrix[2] * b.matrix[8] + a.matrix[3] * b.matrix[12];
    m.matrix[1] = a.matrix[0] * b.matrix[1] + a.matrix[1] * b.matrix[5] + a.matrix[2] * b.matrix[9] + a.matrix[3] * b.matrix[13];
    m.matrix[2] = a.matrix[0] * b.matrix[2] + a.matrix[1] * b.matrix[6] + a.matrix[2] * b.matrix[10] + a.matrix[3] * b.matrix[14];
    m.matrix[3] = a.matrix[0] * b.matrix[3] + a.matrix[1] * b.matrix[7] + a.matrix[2] * b.matrix[11] + a.matrix[3] * b.matrix[15];

    m.matrix[4] = a.matrix[4] * b.matrix[0] + a.matrix[5] * b.matrix[4] + a.matrix[6] * b.matrix[8] + a.matrix[7] * b.matrix[12];
    m.matrix[5] = a.matrix[4] * b.matrix[1] + a.matrix[5] * b.matrix[5] + a.matrix[6] * b.matrix[9] + a.matrix[7] * b.matrix[13];
    m.matrix[6] = a.matrix[4] * b.matrix[2] + a.matrix[5] * b.matrix[6] + a.matrix[6] * b.matrix[10] + a.matrix[7] * b.matrix[14];
    m.matrix[7] = a.matrix[4] * b.matrix[3] + a.matrix[5] * b.matrix[7] + a.matrix[6] * b.matrix[11] + a.matrix[7] * b.matrix[15];

    m.matrix[8] = a.matrix[8] * b.matrix[0] + a.matrix[9] * b.matrix[4] + a.matrix[10] * b.matrix[8] + a.matrix[11] * b.matrix[12];
    m.matrix[9] = a.matrix[8] * b.matrix[1] + a.matrix[9] * b.matrix[5] + a.matrix[10] * b.matrix[9] + a.matrix[11] * b.matrix[13];
    m.matrix[10] = a.matrix[8] * b.matrix[2] + a.matrix[9] * b.matrix[6] + a.matrix[10] * b.matrix[10] + a.matrix[11] * b.matrix[14];
    m.matrix[11] = a.matrix[8] * b.matrix[3] + a.matrix[9] * b.matrix[7] + a.matrix[10] * b.matrix[11] + a.matrix[11] * b.matrix[15];

    m.matrix[12] = a.matrix[12] * b.matrix[0] + a.matrix[13] * b.matrix[4] + a.matrix[14] * b.matrix[8] + a.matrix[15] * b.matrix[12];
    m.matrix[13] = a.matrix[12] * b.matrix[1] + a.matrix[13] * b.matrix[5] + a.matrix[14] * b.matrix[9] + a.matrix[15] * b.matrix[13];
    m.matrix[14] = a.matrix[12] * b.matrix[2] + a.matrix[13] * b.matrix[6] + a.matrix[14] * b.matrix[10] + a.matrix[15] * b.matrix[14];
    m.matrix[15] = a.matrix[12] * b.matrix[3] + a.matrix[13] * b.matrix[7] + a.matrix[14] * b.matrix[11] + a.matrix[15] * b.matrix[15];

    memcpy(output, m.matrix, 16*sizeof(double));

}

void Matrix4f::translate(double x, double y, double z)
{
    matrix[12] += x;
    matrix[13] += y;
    matrix[14] +=z;
}

void Matrix4f::translate(Vec4 vector)
{
    matrix[12] += vector.x1;
    matrix[13] += vector.x2;
    matrix[14] += vector.x3;
}




Matrix4f Matrix4f::multMatrix(Matrix4f a, Matrix4f b)
{
    Matrix4f m;
    m.matrix[0] = a.matrix[0] * b.matrix[0] + a.matrix[1] * b.matrix[4] + a.matrix[2] * b.matrix[8] + a.matrix[3] * b.matrix[12];
    m.matrix[1] = a.matrix[0] * b.matrix[1] + a.matrix[1] * b.matrix[5] + a.matrix[2] * b.matrix[9] + a.matrix[3] * b.matrix[13];
    m.matrix[2] = a.matrix[0] * b.matrix[2] + a.matrix[1] * b.matrix[6] + a.matrix[2] * b.matrix[10] + a.matrix[3] * b.matrix[14];
    m.matrix[3] = a.matrix[0] * b.matrix[3] + a.matrix[1] * b.matrix[7] + a.matrix[2] * b.matrix[11] + a.matrix[3] * b.matrix[15];

    m.matrix[4] = a.matrix[4] * b.matrix[0] + a.matrix[5] * b.matrix[4] + a.matrix[6] * b.matrix[8] + a.matrix[7] * b.matrix[12];
    m.matrix[5] = a.matrix[4] * b.matrix[1] + a.matrix[5] * b.matrix[5] + a.matrix[6] * b.matrix[9] + a.matrix[7] * b.matrix[13];
    m.matrix[6] = a.matrix[4] * b.matrix[2] + a.matrix[5] * b.matrix[6] + a.matrix[6] * b.matrix[10] + a.matrix[7] * b.matrix[14];
    m.matrix[7] = a.matrix[4] * b.matrix[3] + a.matrix[5] * b.matrix[7] + a.matrix[6] * b.matrix[11] + a.matrix[7] * b.matrix[15];

    m.matrix[8] = a.matrix[8] * b.matrix[0] + a.matrix[9] * b.matrix[4] + a.matrix[10] * b.matrix[8] + a.matrix[11] * b.matrix[12];
    m.matrix[9] = a.matrix[8] * b.matrix[1] + a.matrix[9] * b.matrix[5] + a.matrix[10] * b.matrix[9] + a.matrix[11] * b.matrix[13];
    m.matrix[10] = a.matrix[8] * b.matrix[2] + a.matrix[9] * b.matrix[6] + a.matrix[10] * b.matrix[10] + a.matrix[11] * b.matrix[14];
    m.matrix[11] = a.matrix[8] * b.matrix[3] + a.matrix[9] * b.matrix[7] + a.matrix[10] * b.matrix[11] + a.matrix[11] * b.matrix[15];

    m.matrix[12] = a.matrix[12] * b.matrix[0] + a.matrix[13] * b.matrix[4] + a.matrix[14] * b.matrix[8] + a.matrix[15] * b.matrix[12];
    m.matrix[13] = a.matrix[12] * b.matrix[1] + a.matrix[13] * b.matrix[5] + a.matrix[14] * b.matrix[9] + a.matrix[15] * b.matrix[13];
    m.matrix[14] = a.matrix[12] * b.matrix[2] + a.matrix[13] * b.matrix[6] + a.matrix[14] * b.matrix[10] + a.matrix[15] * b.matrix[14];
    m.matrix[15] = a.matrix[12] * b.matrix[3] + a.matrix[13] * b.matrix[7] + a.matrix[14] * b.matrix[11] + a.matrix[15] * b.matrix[15];

    return m;

}

Matrix4f Matrix4f::transpose()
{
    Matrix4f m;
    m.setMatrix4f(this->matrix);
    for(int i=0;i<4;i++){
        for(int j=i+1;j<4;j++){
            int i1 = i+4*j, i2 = j+4*i;
            double aux = m.matrix[i1];
            m.matrix[i1] = m.matrix[i2];
            m.matrix[i2] = aux;
        }
    }
    return m;
}

Vec4 Matrix4f::vector(Vec4 p)
{
    //p.setVec4(0,0,0,1);
    Vec4 v;
    v.x1 = matrix[0]*p.x1 + matrix[1]*p.x2 + matrix[2]*p.x3 + matrix[3]*p.x4;
    v.x2 = matrix[4]*p.x1 + matrix[5]*p.x2 + matrix[6]*p.x3 + matrix[7]*p.x4;
    v.x3 = matrix[8]*p.x1 + matrix[9]*p.x2 + matrix[10]*p.x3 + matrix[11]*p.x4;
    v.x4 = matrix[12]*p.x1 + matrix[13]*p.x2 + matrix[14]*p.x3 + matrix[15]*p.x4;
    return v;
}

Matrix4f Matrix4f::inverse()
{
    Matrix4f inversa,original;
    original.setMatrix4f(this->matrix);
    original.transpose();
    double det=0;
    det =     original.matrix[0]*(original.matrix[5]*original.matrix[10]-original.matrix[6]*original.matrix[9])
            + original.matrix[1]*(-original.matrix[4]*original.matrix[10]+original.matrix[6]*original.matrix[8])
            + original.matrix[2]*(original.matrix[4]*original.matrix[9]+original.matrix[5]*original.matrix[8]);

    if(det==0){
        inversa.setIdentity();
        return inversa;
    }

    inversa.matrix[0] = (original.matrix[5]*original.matrix[10]-original.matrix[6]*original.matrix[9])/det;
    inversa.matrix[1] = (-original.matrix[4]*original.matrix[10]+original.matrix[6]*original.matrix[8])/det;
    inversa.matrix[2] = (original.matrix[4]*original.matrix[9]+original.matrix[5]*original.matrix[8])/det;
    inversa.matrix[3] = 0;

    inversa.matrix[4] = (original.matrix[1]*original.matrix[10]-original.matrix[2]*original.matrix[9])/det;
    inversa.matrix[5] = (-original.matrix[0]*original.matrix[10]+original.matrix[2]*original.matrix[8])/det;
    inversa.matrix[6] = (original.matrix[0]*original.matrix[9]+original.matrix[2]*original.matrix[8])/det;
    inversa.matrix[7] = 0;

    inversa.matrix[8] = (original.matrix[1]*original.matrix[6]-original.matrix[2]*original.matrix[5])/det;
    inversa.matrix[9] = (-original.matrix[0]*original.matrix[6]+original.matrix[2]*original.matrix[4])/det;
    inversa.matrix[10] = (original.matrix[0]*original.matrix[5]+original.matrix[1]*original.matrix[4])/det;
    inversa.matrix[11] = 0;

    inversa.matrix[12] = 0;
    inversa.matrix[13] = 0;
    inversa.matrix[14] = 0;
    inversa.matrix[15] = 1;
    printf("\nDet: %.3f",det);

    return inversa.transpose();

}

void Matrix4f::setIdentity()
{
    for(int i=0;i<16;i++){
        if(i%5==0){
            matrix[i]=1;
        }else{
            matrix[i]=0;
        }
    }
}

void Matrix4f::setTranslate(Vec4 vector)
{
    matrix[12] = vector.x1;
    matrix[13] = vector.x2;
    matrix[14] = vector.x3;
}
