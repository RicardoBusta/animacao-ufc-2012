#ifndef SCENECONTAINER_H
#define SCENECONTAINER_H

#include <vector>
#include "Interpolation/objectanimator.h"

class Joint;
class ObjectAnimator;
class ObjectInfoTree;
class Object3D;
class Viewer;

class SceneContainer
{
public:
    SceneContainer();

    static Viewer *viewer_reference_;

    //! Scene definition
    static void CreateDefaultScene();

    //! Animation parameters
    static int start_frame();
    static int end_frame();
    static int current_frame();
    static void GoToNextFrame();
    static void SetFrameRange(int start, int end);
    static void SetCurrentFrame(int frame);

    //! Objects management
    static Joint* AddObject(QString label, QString objfile, QString texfile, QVector3D position, QQuaternion rotation, Joint *parent);
    static unsigned int HowManyObjects();
    static Joint* ObjectAt(int i);
    static  ObjectInfoTree *GetObjects();
    static bool DrawBones();
    static void SetDrawBones(bool bones);

    //! Selected Object Management
    static Object3D* SelectedObject();
    static void SetSelectedObject(Object3D* selected);
    static void SetSelectedPosition(qglviewer::Vec new_position);
    static void SetSelectedOrientation(qglviewer::Quaternion new_orientation);
    static void DisplaySelectedPositionTrajectory(bool display);
    static void DisplaySelectedOrientationTrajectory(bool display);
    static void AddCurrentPositionKeyframe();
    static void AddCurrentOrientationKeyframe();
    static void RemoveCurrentPositionKeyframe();
    static void RemoveCurrentOrientationKeyframe();



    //! Which to animate
    static void SetAnimated(bool animate_position, bool animate_orientation);
    static void SetOrientationInterpolationType(OriInterpolator::InterpolationType type);
    static void SetPositionInterpolationType(PosInterpolator::InterpolationType type);
    static bool AnimatePosition();
    static bool AnimateOrientation();

    //! Drawing
    static void DrawObjects();
    static void DrawExtras();

    //! Rendering Parameters
    static bool RenderBox();
    static void SetRenderBox(bool box);

private:
    static Object3D* selected_object_;
    static bool animate_position_, animate_orientation_;
    static int start_frame_, end_frame_,current_frame_;
    static bool render_box_over_object_;
    static bool draw_bones_;
    static std::vector<ObjectAnimator*> animators_;
    static std::vector<Joint*> objects_;
    static std::vector<Object3D*> extras_;
};

#endif // SCENECONTAINER_H
