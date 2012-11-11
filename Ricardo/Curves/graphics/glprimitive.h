#ifndef GLPRIMITIVE_H
#define GLPRIMITIVE_H

class Material;
class Matrix4f;

//Draws the primitives using opengl commands.
namespace GLPrimitive
{
    void sphere(float r);
    void box(float lx, float ly, float lz);
    void cylinder(float r, float l, Material *mat, Matrix4f *t);
    void capsule(float r, float l, Material *mat, Matrix4f *t);

    //future implementation
    //void triMesh();
    //void convexHull();

    //not tied to any object
    //part of the static world
    //void plane(float a, float b, float c, float d);
    void plane(float s, Material *mat, Matrix4f *t);

    //don't represent a solid object
    //start at the object center and go to z direction
    void ray(float length);
}

#endif // GLPRIMITIVE_H
