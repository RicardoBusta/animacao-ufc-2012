#include "iksolve.h"
//#include <qgenericmatrix.h>

//#include <QGenericMatrix>
//#include<QMatrix4x4>
using namespace Eigen;
//static double d=0.5;
//static double dmax=0.0001;
static double d=0.5;
static double dmax=0.0001;
IKSolve::IKSolve()
{

}

void IKSolve::IKSolveKinematicsInverse(Joint* effector, Vec4 goal,int type)
{
    Vec4 posEffector = effector->getPositionEffector();

    if ((goal-posEffector).module()<dmax) return;
    // = (goal-posEffector)*d;
    //while(goal.module()>0.00001){
    Joint *root;
    root = effector;
    Joint *r;
    int qtde_joint=0;
    if(!(root==NULL)){
        while(root!=NULL){
            qtde_joint++;
            r = root;
            root = root->getParent();
        }
    }else{
        qtde_joint=1;
    }
    root = effector;
//    if((goal-posEffector).module()>(r->getPositionAbsolute()).module()){
//        printf("\nMuito distante!");
//        return;
//    }

    MatrixXd jacobiana = pseudo_jacobian(effector,type);





    Vec4 e;
    if(type==0){
        d=0.5;
        dmax=0.01;
        if((goal-posEffector).module()<dmax){
            e = (goal-posEffector);
        }else{
            e = ((goal-posEffector)*dmax)/(goal-posEffector).module();
        }

    }else{
        d=0.05;
        dmax=0.01;
        e = (goal-posEffector)*d;
    }

    MatrixXd position = MatrixXd::Zero(3,1);

    position(0,0) = e.x1;
    position(1,0) = e.x2;
    position(2,0) = e.x3;


    jacobiana = (jacobiana*position);


    int i = 0;
    while(root!=NULL){
        //fator de suavizacao s
        double s=0.5;
        root->applyOrientation(Vec4(1,0,0,s*jacobiana(i,0)*180.0/M_PI));
        root->applyOrientation(Vec4(0,1,0,s*jacobiana(1+i,0)*180.0/M_PI));
        root->applyOrientation(Vec4(0,0,1,s*jacobiana(2+i,0)*180.0/M_PI));
        i+=3;
        root = root->getParent();
    }


}

MatrixXd IKSolve::jacobian(Joint *effector)
{
    Joint *root;
    root = effector;
    int qtde_joint=0;
    if(!(root==NULL)){
        while(root!=NULL){
            if(root->getParent()==NULL){
                root->DrawObject();
            }
            qtde_joint++;
            root = root->getParent();
        }
    }else{
        qtde_joint=1;
    }
    root = effector;

    MatrixXd jacobian = MatrixXd::Zero(3,3*qtde_joint);

    Vec4 posEffector = effector->getPositionEffector();

    int i = 0;

    while(root!=NULL){
        Vec4 derivatex,derivatey,derivatez;
        Vec4 posJoint = root->getPositionAbsolute();
        Vec4 posrelative = posEffector - posJoint;
        //posrelative = posrelative.unitary();

//        if(i==0){
//            derivatex.setVec4(root->orientation_.getMatrix().matrix[0],root->orientation_.getMatrix().matrix[1],root->orientation_.getMatrix().matrix[2]);
//            derivatey.setVec4(root->orientation_.getMatrix().matrix[4],root->orientation_.getMatrix().matrix[5],root->orientation_.getMatrix().matrix[6]);
//            derivatez.setVec4(root->orientation_.getMatrix().matrix[8],root->orientation_.getMatrix().matrix[9],root->orientation_.getMatrix().matrix[10]);
//        }else{

//        derivatex.setVec4(root->orientation_.getMatrix().matrix[0],root->orientation_.getMatrix().matrix[1],root->orientation_.getMatrix().matrix[2]);
//        derivatey.setVec4(root->orientation_.getMatrix().matrix[4],root->orientation_.getMatrix().matrix[5],root->orientation_.getMatrix().matrix[6]);
//        derivatez.setVec4(root->orientation_.getMatrix().matrix[8],root->orientation_.getMatrix().matrix[9],root->orientation_.getMatrix().matrix[10]);

        derivatex.setVec4(root->transform_global.matrix[0],root->transform_global.matrix[1],root->transform_global.matrix[2]);
        derivatey.setVec4(root->transform_global.matrix[4],root->transform_global.matrix[5],root->transform_global.matrix[6]);
        derivatez.setVec4(root->transform_global.matrix[8],root->transform_global.matrix[9],root->transform_global.matrix[10]);

        derivatex = Vec4::crossProduct(derivatex,posrelative);
        derivatey = Vec4::crossProduct(derivatey,posrelative);
        derivatez = Vec4::crossProduct(derivatez,posrelative);
//        }

        double vetx[3] = {derivatex.x1,derivatey.x1,derivatez.x1};
        double vety[3] = {derivatex.x2,derivatey.x2,derivatez.x2};
        double vetz[3] = {derivatex.x3,derivatey.x3,derivatez.x3};

        //        double vetx[3] = {derivatex.x1,derivatex.x2,derivatex.x3};
        //        double vety[3] = {derivatey.x1,derivatey.x2,derivatey.x3};
        //        double vetz[3] = {derivatez.x1,derivatez.x2,derivatez.x3};

        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                if(j==0){
                    jacobian(0,k+(3*i)) =vetx[k];

                }
                if(j==1){
                    jacobian(1,k+(3*i)) =vety[k];
                }
                if(j==2){
                    jacobian(2,k+(3*i)) =vetz[k];

                }
            }
        }
        i++;
        root = root->getParent();
    }
    //imprime a matriz jacobiana
//    for(int i=0;i<jacobian.cols();i++){
//        for(int j=0;j<jacobian.rows();j++){
//            printf("%.3f ",jacobian(j,i));
//        }
//        printf("\n");
//    }
    return jacobian;
}

MatrixXd IKSolve::pseudo_jacobian(Joint* effector,int type)
{
    MatrixXd j = jacobian(effector);
    MatrixXd jjtInv = (j * j.transpose());
    jjtInv = jjtInv.inverse();
    bool nan= false;
    //somente o calculo da transposta
    if(type==0){
        return j.transpose();
    }
    //calculo da pseudo inversa
    //Verifica se existe matriz inversa
    for(int i=0;i<jjtInv.cols();i++){
        for(int j=0;j<jjtInv.rows();j++){

            if (isnan(jjtInv(j,i))){
                nan = true;
                break;
            }
        }

    }

    if(nan){
        return j.transpose();
    }

    return (j.transpose()*jjtInv);
}

