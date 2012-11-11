#ifndef MATERIAL_H
#define MATERIAL_H

enum MATERIAL_COLOR{MAT_RED, MAT_DARK_RED,    MAT_GREEN, MAT_DARK_GREEN,
          MAT_BLUE, MAT_DARK_BLUE,  MAT_YELLOW,MAT_DARK_YELLOW,
          MAT_CYAN, MAT_DARK_CYAN,  MAT_MAGENTA, MAT_DARK_MAGENTA,
          MAT_WHITE,MAT_GRAY_75,MAT_GRAY_50,MAT_GRAY_25,
          MAT_ORANGE, MAT_BLACK};

class Material
{
public:
    Material();

    void gl();
    void glHalf();

    void setDiffuse(int color);
    void setSpecular(int color);
    void setEmission(int color);
    void setShininess(int intensity);

private:
    float emission[4];
    float specular[4];
    float diffuse[4];
    float diffuse_2[4];
    float shininess[1];

    void setColor(float component[], int color);
};

#endif // MATERIAL_H
