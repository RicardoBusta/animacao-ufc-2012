#include "matrix4d.h"

#include "Utils/genericmatrix.h"

GenericMatrix Matrix4D::generate()
{
    GenericMatrix matrix(4,4);
    return matrix;
}


GenericMatrix Matrix4D::generate(qglviewer::Vec translation)
{
    GenericMatrix matrix(4,4);
    matrix.setIdentity();
    matrix.set(0,3,translation.x);
    matrix.set(1,3,translation.y);
    matrix.set(2,3,translation.z);
    return matrix;
}


GenericMatrix Matrix4D::generate(qglviewer::Quaternion orientation)
{
    GenericMatrix matrix(4,4);
    const GLdouble *omatrix = orientation.matrix();
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            matrix.set(j,i,omatrix[((i*4)+j)]);
        }
    }
    return matrix;
}

qglviewer::Vec Matrix4D::apply(GenericMatrix matrix, qglviewer::Vec op, bool vector)
{
    qglviewer::Vec result;
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

    res = (matrix * temp);

//    for(int i=0;i<4;i++){
//        double resv = 0;
//        for(int k=0;k<4;k++){
//            resv += ( thisM.get(i,k) * temp.get(k,0) );
//        }
//        res.set(i,0,resv);
//    }

    result.x = res.get(0,0);
    result.y = res.get(1,0);
    result.z = res.get(2,0);

    return result;
}
