#include "iksolver.h"

#include <QVector4D>

#include <Utils/genericmatrix.h>
#include <Utils/scenecontainer.h>
#include <Utils/matrix4d.h>
#include <Interpolation/objectanimator.h>

#define D 0.5;
#define DMAX 0.0001

IKSolver::IKSolver()
{
}

void IKSolver::solve(Joint *effector, qglviewer::Vec goal, int type)
{
    qglviewer::Vec posEffector = effector->globalTransformationMatrix().apply(qglviewer::Vec(0,0,0),true);

    if ((goal-posEffector).norm()<DMAX) return;

    Joint *root;
    root = effector;
    Joint *r;
    int joint_count=0;
    if(!(root==NULL)){
        while(root!=NULL){
            joint_count++;
            r = root;
            root = root->parent();
        }
    }else{
        joint_count=1;
    }
    root = effector;

    GenericMatrix jacobiana = pseudoJacobian(effector,type);

    qglviewer::Vec e;
    if(type==0){
        if((goal-posEffector).norm()<DMAX){
            e = (goal-posEffector);
        }else{
            e = ((goal-posEffector)*DMAX)/(goal-posEffector).norm();
        }

    }else{
        e = (goal-posEffector)*D;
    }

    GenericMatrix position = GenericMatrix(3,1);

    position.set( 0 , 0 , e.x);
    position.set( 1 , 0 , e.y);
    position.set( 2 , 0 , e.z);


    jacobiana = (jacobiana*position);


    int i = 0;
    while(root!=NULL){
        // Smoothing Factor s
        double s=0.5;
        root->setNewOrientation(qglviewer::Quaternion(1,0,0,s*jacobiana.get(i,0)*180.0/M_PI));
        root->setNewOrientation(qglviewer::Quaternion(0,1,0,s*jacobiana.get(1+i,0)*180.0/M_PI));
        root->setNewOrientation(qglviewer::Quaternion(0,0,1,s*jacobiana.get(2+i,0)*180.0/M_PI));
        i+=3;
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

    qglviewer::Vec posEffector = effector->globalTransformationMatrix().apply(qglviewer::Vec(0,0,0),true);

    int i = 0;

    while(joint!=NULL){
        qglviewer::Vec derivatex,derivatey,derivatez;
        qglviewer::Vec posJoint = joint->getAnimator()->globalPositionAt(SceneContainer::current_frame());
        qglviewer::Vec posrelative = posEffector - posJoint;

        Matrix4D globalTransform = joint->getAnimator()->globalTransformationMatrix(SceneContainer::current_frame());

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

        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                if(j==0){
                    jacobian.set( 0 , k+(3*i) , vetx[k] );

                }
                if(j==1){
                    jacobian.set( 1 , k+(3*i) , vety[k] );
                }
                if(j==2){
                    jacobian.set( 2 , k+(3*i) , vetz[k] );

                }
            }
        }
        i++;
        joint = joint->parent();
    }

    return jacobian;
}


GenericMatrix IKSolver::pseudoJacobian(Joint *effector, int type)
{
    GenericMatrix j = jacobian(effector);
    GenericMatrix j_jt_inverse = (j * j.transpose());
    j_jt_inverse = j_jt_inverse.inverse();
    bool nan= false;
    // If transpose only
    if(type==0){
        return j.transpose();
    }
    // Pseudo Inverse
    // Verify if there is inverse
    for(int i=0;i<j_jt_inverse.cols();i++){
        for(int j=0;j<j_jt_inverse.rows();j++){
            if (isnan(j_jt_inverse.get(j,i))){
                nan = true;
                break;
            }
        }
    }

    if(nan){
        return j.transpose();
    }

    return (j.transpose()*j_jt_inverse);
}
