#ifndef SCENECONTAINER_H
#define SCENECONTAINER_H

#include <vector>
#include <QVector3D>
#include <QQuaternion>
#include "Interpolation/objectanimator.h"

class Joint;
class ObjectAnimator;
class ObjectInfoTree;
class Object3D;
class Viewer;

enum RENDER_OPTIONS{ RENDER_NONE=0, RENDER_SHADER=1, RENDER_OPT2=2, RENDER_OPT3=4, RENDER_OPT4=8, RENDER_OPT5=16, RENDER_OPT6=32, RENDER_OPT7=64, RENDER_OPT8=128 };

class SceneContainer
{
public:
    SceneContainer();

    static Viewer *viewer_reference_;

    //! Animation parameters
    static int start_frame();
    static int end_frame();
    static int current_frame();
    static void goToNextFrame();
    static void setFrameRange(int start, int end);
    static void setCurrentFrame(int frame);

    //! Objects management
    static Joint* addObject(QString label, QString objfile, QString texfile, QVector3D position, QQuaternion rotation, Joint *parent, QVector3D objPos = QVector3D(0,0,0), QQuaternion objRot = QQuaternion(1,0,0,0));
    static unsigned int howManyObjects();
    static Joint* objectAt(int i);
    static  ObjectInfoTree *getObjects();
    static bool drawBones();
    static void setDrawBones(bool bones);

    //! Selected Object Management
    static Object3D* selectedObject();
    static void setSelectedObject(Object3D* selected);
    static void setSelectedPosition(qglviewer::Vec new_position);
    static void setSelectedOrientation(qglviewer::Quaternion new_orientation);
    static void displaySelectedPositionTrajectory(bool display);
    static void displaySelectedOrientationTrajectory(bool display);
    static void addCurrentPositionKeyframe();
    static void addCurrentOrientationKeyframe();
    static void removeCurrentPositionKeyframe();
    static void removeCurrentOrientationKeyframe();

    //! Which to animate
    static void setAnimated(bool animate_position, bool animate_orientation);
    static void setOrientationInterpolationType(OriInterpolator::InterpolationType type);
    static void setPositionInterpolationType(PosInterpolator::InterpolationType type);
    static bool animatePosition();
    static bool animateOrientation();

    //! Drawing
    static void drawObjects();
    static void drawObjectsNoShader();
    static void drawExtras();

    //! Rendering Parameters
    static bool renderBox();
    static void setRenderBox(bool box);

    static bool renderOptions(int options_mask);

    //! I/O
    static QString genOutput();

    //! Scene Manipulation
    static void createMonkeyHeadScene();
    static void createArmScene();
    static void createMonkeySnakeScene();
    static void createRobotScene();
    static void updateCurrentScene(int scene);

    static void clearScene();

    static bool getDrawWithNames();
    static void setDrawWithNames(bool draw_with_names);

    static bool alternateColors();
    static void setAlternateColors(bool alternate);

    static std::vector<ObjectAnimator *> *getAnimators();

private:
    static Object3D* selected_object_;
    static bool animate_position_, animate_orientation_;
    static int start_frame_, end_frame_,current_frame_;
    static bool render_box_over_object_;
    static bool draw_bones_;

    static unsigned int render_options_;

    static bool draw_with_names_;

    static bool alternate_colors_;

    static std::vector<ObjectAnimator*> animators_;
    static std::vector<Joint*> objects_;
    static std::vector<Object3D*> extras_;
};

#endif // SCENECONTAINER_H
