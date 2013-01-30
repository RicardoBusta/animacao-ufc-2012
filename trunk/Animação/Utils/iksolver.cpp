#include "iksolver.h"

#include <QVector4D>

#include <Utils/genericmatrix.h>
#include <Utils/scenecontainer.h>
#include <Utils/matrix4d.h>
#include <Interpolation/objectanimator.h>

#include <iostream>
using namespace std;

IKSolver::IKSolver()
{
}

void IKSolver::solve(std::vector<Joint*>* bones, qglviewer::Vec goal, int type)
{
    Joint* effector = bones->front();
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

    GenericMatrix jacobianMatrix = pseudoJacobian(bones,type);

    qglviewer::Vec e;
    if(type==1){
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
    for(int j = 0 ; j < bones->size() ; j++ ) {
        // Smoothing Factor s
        Joint* root = bones->at(j);
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
    }

}


GenericMatrix IKSolver::jacobian(std::vector<Joint*>* bones)
{
//    Joint * effector =  bones->back();
    Joint * effector =  bones->front();
    Joint * joint = effector;
    int joint_count=0;
    //    if(!(root==NULL)){
    /*while(joint!=NULL){
        //            if(root->getParent()==NULL){
        //                root->DrawObject();
        //            }
        joint_count++;
        joint = joint->parent();
    }*/
    //    }else{
    //        joint_count=1;
    //    }
    //joint = effector;

    GenericMatrix jacobian = GenericMatrix(3,3*bones->size());

    qglviewer::Vec posEffector = effector->globalEffectorPosition();

    for(unsigned int i = 0 ; i < bones->size() ; i++) {
        joint = bones->at(i);
        qglviewer::Vec derivatex,derivatey,derivatez;
        qglviewer::Vec posJoint = joint->globalPosition();
        qglviewer::Vec posrelative = posEffector - posJoint;

        GenericMatrix globalTransform = joint->globalTransformationMatrix().transpose();

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

    }

//    jacobian.debugPrint("jacobian");
    return jacobian;
}


GenericMatrix IKSolver::pseudoJacobian(std::vector<Joint*> *bones, int type)
{
    GenericMatrix j = jacobian(bones);
//    return j.transpose();
    if(type==1){
        return j.transpose();
    }
    GenericMatrix j_jt_inverse = (j*j.transpose());
    //j_jt_inverse.debugPrint("pre-inverse");
    j_jt_inverse = j_jt_inverse.inverse();

    if( j_jt_inverse.cols() == 1 ) return j.transpose();

    //j_jt_inverse.debugPrint("jjtinv");

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
