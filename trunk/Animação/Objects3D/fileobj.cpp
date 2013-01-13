#include "fileobj.h"

#include <QtOpenGL>

FileObj::FileObj()
{
    label_ = "Untitled";
}

void FileObj::DrawObject(bool renderbox)
{
    if(!renderbox){
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture( GL_TEXTURE_2D, texID );
        glBegin(GL_TRIANGLES);
        for(int i=0;i<face.size();i++){
            FileObjFace thisface = face[i];

            for(int j=0;j<3;j++){
                glTexCoord2f(texturecoord[thisface.textureID[j]].x(),texturecoord[thisface.textureID[j]].y());
                glNormal3f(normal[thisface.normalID[j]].x(),normal[thisface.normalID[j]].y(),normal[thisface.normalID[j]].z());
                glVertex3f(vertex[thisface.vertexID[j]].x(),vertex[thisface.vertexID[j]].y(),vertex[thisface.vertexID[j]].z());
            }
        }
        glEnd();
        glPopAttrib();
    }else{
        DrawBoxObject();
    }
}

void FileObj::loadFile(QString filename)
{
    vertex.clear();
    texturecoord.clear();
    normal.clear();
    face.clear();

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    QVector3D vecv(0,0,0);
    vertex.push_back(vecv);
    QVector2D vect(0,0);
    texturecoord.push_back(vect);
    QVector3D vecn(0,0,0);
    normal.push_back(vecn);
    bounding_box_max_ = qglviewer::Vec(0,0,0);
    bounding_box_min_ = qglviewer::Vec(0,0,0);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList token = line.split(' ');

        if(token.at(0) == "v" and token.size() == 4){
            float x = token.at(1).toFloat();
            float y = token.at(2).toFloat();
            float z = token.at(3).toFloat();

            if(x > bounding_box_max_.x){
                bounding_box_max_.x = x;
            }
            if(x < bounding_box_min_.x){
                bounding_box_min_.x = x;
            }
            if(y > bounding_box_max_.y){
                bounding_box_max_.y = y;
            }
            if(y < bounding_box_min_.y){
                bounding_box_min_.y = y;
            }
            if(z > bounding_box_max_.z){
                bounding_box_max_.z = z;
            }
            if(z < bounding_box_min_.z){
                bounding_box_min_.z = z;
            }

            QVector3D vec(x,y,z);
            vertex.push_back(vec);
        }else if(token.at(0) == "vt" and token.size() == 3){
            QVector2D vec(token.at(1).toFloat(),token.at(2).toFloat());
            texturecoord.push_back(vec);
        }else if(token.at(0) == "vn" and token.size() == 4){
            QVector3D vec(token.at(1).toFloat(),token.at(2).toFloat(),token.at(3).toFloat());
            normal.push_back(vec);
        }else if(token.at(0) == "f" and token.size() == 4){
            FileObjFace f;

            QStringList v0 = token.at(1).split('/');
            QStringList v1 = token.at(2).split('/');
            QStringList v2 = token.at(3).split('/');

            if(v1.size() == 3 and v2.size() == 3 and v0.size() == 3){
                f.vertexID[0] = v0.at(0).toInt();
                f.textureID[0] = v0.at(1).toInt();
                f.normalID[0] = v0.at(2).toInt();

                f.vertexID[1] = v1.at(0).toInt();
                f.textureID[1] = v1.at(1).toInt();
                f.normalID[1] = v1.at(2).toInt();

                f.vertexID[2] = v2.at(0).toInt();
                f.textureID[2] = v2.at(1).toInt();
                f.normalID[2] = v2.at(2).toInt();
            }else{
                f.vertexID[0] = 0;
                f.textureID[0] = 0;
                f.normalID[0] = 0;

                f.vertexID[1] = 0;
                f.textureID[1] = 0;
                f.normalID[1] = 0;

                f.vertexID[2] = 0;
                f.textureID[2] = 0;
                f.normalID[2] = 0;
            }
            face.push_back(f);
        }else{

        }
    }

    //    cout << vertex.size() << " " << texturecoord.size() << " " << normal.size() << " " << face.size() << endl;
    file.close();

}


void FileObj::loadTex(QString filename)
{
    QImage tex = QGLWidget::convertToGLFormat( QImage(filename) );
    //    GLuint texId;
    glGenTextures( 1, &texID );
    glBindTexture( GL_TEXTURE_2D, texID );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, tex.width(), tex.height(), 0, GL_RGBA,GL_UNSIGNED_BYTE, tex.bits());
}
