#ifndef FILEOBJ_H
#define FILEOBJ_H

#include <Objects3D/object3d.h>
#include <QVector>
#include <QVector2D>
#include <QVector3D>

class FileObj : public Object3D
{
private:
    class FileObjFace{
    public:
        FileObjFace(){}

        int pointID[3];
        int textureID[3];
        int normalID[3];
    };
public:

    FileObj();

    void DrawObject(bool, bool);
    void loadFile(QString filename);

    QVector<QVector3D> vertex;
    QVector<QVector2D> texturecoord;
    QVector<QVector3D> normal;

    QVector<FileObjFace> face;
};

#endif // FILEOBJ_H
