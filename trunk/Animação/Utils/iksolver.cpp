#include "iksolver.h"

#include <QVector4D>

#include <Utils/genericmatrix.h>
#include <Utils/scenecontainer.h>
#include <Utils/matrix4d.h>
#include <Interpolation/objectanimator.h>

#define GOAL_DISTANCE_ERROR 0.001
#define D 0.5;
#define MAX_DISTANCE_FRAME 0.01

static qglviewer::Vec posEf = qglviewer::Vec(0,0.3f,0);

#include <iostream>
using namespace std;

IKSolver::IKSolver()
{
}

void IKSolver::solve(Joint *effector, qglviewer::Vec goal, int type)
{
    qglviewer::Vec posEffector = effector->globalEffectorPosition();

    if ((goal-posEffector).norm()<GOAL_DISTANCE_ERROR) return;

    Joint *root;
    root = effector;
    //    int joint_count=0;
    //    if(!(root==NULL)){
    //        while(root!=NULL){
    //            joint_count++;
    //            root = root->parent();
    //        }
    //    }else{
    //        joint_count=1;
    //    }
    //    root = effector;

    GenericMatrix jacobianMatrix = pseudoJacobian(effector,type);

    qglviewer::Vec e;
    if(type==0){
        if((goal-posEffector).norm()<MAX_DISTANCE_FRAME){
            return;
        }else{
            e = ((goal-posEffector)*MAX_DISTANCE_FRAME);
            //e = ( ((goal-posEffector)*MAX_DISTANCE_FRAME) / ((goal-posEffector).norm()) );
        }

    }else{
        e = (goal-posEffector)*D;
    }

    GenericMatrix position = GenericMatrix(3,1);

    position.set( 0 , 0 , e.x);
    position.set( 1 , 0 , e.y);
    position.set( 2 , 0 , e.z);


    GenericMatrix application = (jacobianMatrix * position);
//    application.debugPrint("application");


    int i = 0;
    while(root!=NULL){
        // Smoothing Factor s
        double s=0.5;
        double angle;
        qglviewer::Vec vector;
        qglviewer::Quaternion qresult = root->orientation();

        vector = qglviewer::Vec(1,0,0);
        angle = ( application.get(i,0)/**(180.0/M_PI)*/ );
        qresult = qresult * qglviewer::Quaternion(vector,angle);
        i++;

        vector = qglviewer::Vec(0,1,0);
        angle = ( application.get(i,0)/**(180.0/M_PI)*/ );
        qresult = qresult * qglviewer::Quaternion(vector,angle);
        i++;

        vector = qglviewer::Vec(0,0,1);
        angle = ( application.get(i,0)/**(180.0/M_PI)*/ );
        qresult = qresult * qglviewer::Quaternion(vector,angle);
        i++;

        root->setNewOrientation( qresult );

        root = root->parent();
    }

}


GenericMatrix IKSolver::jacobian(Joint *effector)
{
    Joint *joint;
    joint = effector;
    int joint_count=0;
    //    if(!(root==NULL)){
    while(joint!=NULL){
        //            if(root->getParent()==NULL){
        //                root->DrawObject();
        //            }
        joint_count++;
        joint = joint->parent();
    }
    //    }else{
    //        joint_count=1;
    //    }
    joint = effector;

    GenericMatrix jacobian = GenericMatrix(3,3*joint_count);

    qglviewer::Vec posEffector = effector->globalEffectorPosition();

    int i = 0;

    while(joint!=NULL){
        qglviewer::Vec derivatex,derivatey,derivatez;
        qglviewer::Vec posJoint = joint->globalPosition();
        qglviewer::Vec posrelative = posEffector - posJoint;

        GenericMatrix globalTransform = joint->globalTransformationMatrix().transpose()/*.transpose()*/;

        derivatex.setValue(globalTransform.get(0),globalTransform.get(1),globalTransform.get(2));
        derivatey.setValue(globalTransform.get(4),globalTransform.get(5),globalTransform.get(6));
        derivatez.setValue(globalTransform.get(8),globalTransform.get(9),globalTransform.get(10));

        // Cross Product
        derivatex = derivatex^posrelative;
        derivatey = derivatey^posrelative;
        derivatez = derivatez^posrelative;

        double vetx[3] = {derivatex.x,derivatey.x,derivatez.x};
        double vety[3] = {derivatex.y,derivatey.y,derivatez.y};
        double vetz[3] = {derivatex.z,derivatey.z,derivatez.z};


        for(int k=0;k<3;k++){
            jacobian.set( 0 , k+(3*i) , vetx[k] );
            jacobian.set( 1 , k+(3*i) , vety[k] );
            jacobian.set( 2 , k+(3*i) , vetz[k] );
        }
        i++;
        joint = joint->parent();
    }

//    jacobian.debugPrint("jacobian");
    return jacobian;
}


GenericMatrix IKSolver::pseudoJacobian(Joint *effector, int type)
{
    GenericMatrix j = jacobian(effector);
//    return j.transpose();
    if(type==0){
        return j.transpose();
    }
    GenericMatrix j_jt_inverse = (j*j.transpose());
    j_jt_inverse.debugPrint("pre-inverse");
    j_jt_inverse = j_jt_inverse.inverse();

    if( j_jt_inverse.cols() == 1 ) return j.transpose();

    j_jt_inverse.debugPrint("jjtinv");

    bool nan= false;
    // If transpose only

    // Pseudo Inverse
    // Verify if there is inverse
//    for(int i=0;i<j_jt_inverse.cols();i++){
//        for(int j=0;j<j_jt_inverse.rows();j++){
//            if (isnan(j_jt_inverse.get(j,i))){
//                nan = true;
//                break;
//            }
//        }
//    }

//    if(nan){
//        return j.transpose();
//    }

    return (j.transpose()*j_jt_inverse);
}
