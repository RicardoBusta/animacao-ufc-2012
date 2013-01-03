#include "fileobj.h"

FileObj::FileObj()
{
}

void FileObj::DrawObject(bool, bool)
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    for(int i=0;i<face.size();i++){
        FileObjFace thisface = face[i];

        for(int j=0;j<3;j++){
            glTexCoord2f(texturecoord[thisface.textureID[j]].x(),texturecoord[thisface.textureID[j]].y());
            glNormal3f(normal[thisface.textureID[j]].x(),normal[thisface.textureID[j]].y(),normal[thisface.textureID[j]].z());
            glVertex3f(vertex[thisface.textureID[j]].x(),vertex[thisface.textureID[j]].y(),vertex[thisface.textureID[j]].z());
        }
    }

    glPopAttrib();
}

void FileObj::loadFile(QString)
{
}
