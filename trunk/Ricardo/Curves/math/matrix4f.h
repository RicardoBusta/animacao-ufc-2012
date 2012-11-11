#ifndef MATRIX4_H
#define MATRIX4_H

class Vector3f;

class Matrix4f
{
public:
    Matrix4f();

    void set(int position, float value);

    void setIdentity();

    void get(float output[]) const;
    float get(int index) const;

    void translate(float x, float y, float z);

    void gl();

    void setPosition(Vector3f pos);

    #ifdef DEBUG_MODE
    void stdPrint() const;
    #endif
private:
    float matrix[16];
};

#endif // MATRIX4_H
