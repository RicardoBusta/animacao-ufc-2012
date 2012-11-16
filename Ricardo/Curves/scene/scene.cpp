#include "scene.h"

#include "graphics/camera.h"

#include "graphics/glprimitive.h"
#include "graphics/material.h"
#include "math/matrix4f.h"
#include "math/vector3f.h"

#include "graphics/glmathelements.h"
#include "graphics/glvectorfunctions.h"

#include "graphics/curve.h"

#include <QtOpenGL>

Scene::Scene()
{
    rotx = 0;
    roty = 0;

    curve.addPoint( new Vector3f( 10, 10, 10) );
    curve.addPoint( new Vector3f( 100, -800, 600) );
    curve.addPoint( new Vector3f( 200, 800, -500) );
    curve.addPoint( new Vector3f( 500, -30, 50) );

    curve.calculateCurve();
}

Scene::~Scene()
{
    curve.clear();
}

void Scene::draw()
{

    glLoadIdentity();

    glTranslatef(0,0,-1000);
    glRotatef(rotx,1,0,0);
    glRotatef(roty,0,1,0);

    GLMathElements::drawAxis(300);

    curve.glControlPoints();
    curve.glCurve();
}








