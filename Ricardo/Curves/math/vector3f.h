#ifndef VECTOR3F_H
#define VECTOR3F_H

class Matrix4f;

class Vector3f
{
public:
    Vector3f(float x=0.0, float y=0.0, float z=0.0);
    Vector3f(const Vector3f &vec);
    ~Vector3f();

    void set(Vector3f op);

    void setX(float x);
    void setY(float y);
    void setZ(float z);

    float getX() const;
    float getY() const;
    float getZ() const;

    void crossProductSelf(Vector3f *op);
    void realProductSelf(float op);
    void subtractSelf(Vector3f *op);
    void addSelf(Vector3f *op);
    void transformSelf(Matrix4f *m);
    void normalizeSelf();

    Vector3f crossProduct(Vector3f *op) const;
    Vector3f realProduct(float op) const;
    Vector3f subtract(Vector3f *op) const;
    Vector3f add(Vector3f *op) const;
    Vector3f transform(Matrix4f *m) const;
    float dotProduct(Vector3f *op) const;

    Vector3f operator=(Vector3f v);

#ifdef DEBUG_MODE
    void stdPrint() const;
#endif
private:
    float x;
    float y;
    float z;
};

#endif // VECTOR3F_H
