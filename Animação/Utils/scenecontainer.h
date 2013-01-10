#ifndef SCENECONTAINER_H
#define SCENECONTAINER_H

#include <vector>
#include "Interpolation/objectanimator.h"

class Joint;
class ObjectAnimator;
class ObjectInfoTree;
class Object3D;

class SceneContainer
{
public:
    SceneContainer();

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
    static unsigned int HowManyObjects();
    static Joint* ObjectAt(int i);
    static  ObjectInfoTree *GetObjects();
    static int SelectedObject();

    //! Which to animate
    static void SetAnimated(bool animate_position, bool animate_orientation);
    static void SetOrientationInterpolationType(OriInterpolator::InterpolationType type);
    static void SetPositionInterpolationType(PosInterpolator::InterpolationType type);
    static bool AnimatePosition();
    static bool AnimateOrientation();

    static void DrawObjects();

private:
    static bool animate_position_, animate_orientation_;
    static int start_frame_, end_frame_,current_frame_;
    static int selected_object_;
    static std::vector<ObjectAnimator*> animators_;
    static std::vector<Joint*> objects_;
    static std::vector<Object3D*> extras_;
};

#endif // SCENECONTAINER_H
