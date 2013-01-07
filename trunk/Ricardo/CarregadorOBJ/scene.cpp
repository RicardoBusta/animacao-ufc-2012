#include "scene.h"

#include <QtOpenGL>

Scene::Scene()
{
    rotx = 0;
    roty = 0;

    obj.loadFile("D:\\UFC\\Ricardo\\CarregadorOBJ\\nave.obj");
}

Scene::~Scene()
{
}

void Scene::draw()
{
    glLoadIdentity();

    glTranslatef(0,0,-5);
    glRotatef(rotx,1,0,0);
    glRotatef(roty,0,1,0);

    obj.DrawObject(true,true);
    /*
    glBegin(GL_TRIANGLES);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);
    glVertex3f(100,100,0);
    glEnd();*/
}








