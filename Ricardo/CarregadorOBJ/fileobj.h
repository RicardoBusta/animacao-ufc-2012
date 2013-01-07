#ifndef FILEOBJ_H
#define FILEOBJ_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>

class FileObj
{
private:
    class FileObjFace{
    public:
        FileObjFace(){}

        int vertexID[3];
        int textureID[3];
        int normalID[3];

        FileObjFace operator=(FileObjFace o){
            for(int i=0;i<3;i++){
                this->vertexID[i] = o.vertexID[i];
                this->textureID[i] = o.vertexID[i];
                this->normalID[i] = o.normalID[i];
            }
            return *this;
        }
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
