#include "particle.h"

#include <QtOpenGL>

#include "Utils/scenecontainer.h"
#include "Widgets/viewer.h"

Particle::Particle(int lifetime, QVector3D position, QVector3D speed)
{
    this->position_ = position;
    this->speed_ = speed;
    this->lifetime_ = lifetime;
}


void Particle::draw()
{
    SceneContainer::viewer_reference_->bindShader();

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
    //    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor4d(1.0,1.0,1.0,1);

    glTranslatef(position_.x(),position_.y(),position_.z());

    float matrix4f[16];

    glGetFloatv(GL_MODELVIEW_MATRIX , matrix4f);
    for(int i=0; i<3; i++ ){
        for(int j=0; j<3; j++ ) {
            if ( i==j )
                matrix4f[i*4+j] = 1.0;
            else
                matrix4f[i*4+j] = 0.0;
        }
    }
    glLoadMatrixf(matrix4f);

    glBegin(GL_QUADS);

    glTexCoord2f(0,0);
    glVertex3f(0,0,0);
    glTexCoord2f(0,1);
    glVertex3f(2,0,0);
    glTexCoord2f(1,1);
    glVertex3f(2,2,0);
    glTexCoord2f(1,0);
    glVertex3f(0,2,0);

    glEnd();
    glPopMatrix();
    glPopAttrib();

    SceneContainer::viewer_reference_->releaseShader();
}

void Particle::handle()
{
    position_+=speed_;
}


//-------------------
//! PARTICLE SPAWNER
//-------------------

QList<ParticleSpawner*> ParticleSpawner::particle_spawners_;

ParticleSpawner::ParticleSpawner(int cooldown)
{
    this->count = 0;
    this->cooldown = cooldown;
    particle_spawners_.push_back(this);
}

ParticleSpawner::~ParticleSpawner(){
    while(!particles.empty()){
        delete particles.first();
        particles.pop_front();
    }

    particle_spawners_.removeOne(this);
}

void ParticleSpawner::handleParticleSpawners()
{
    for(int i=0;i<particle_spawners_.size();i++){
        ParticleSpawner *ps = particle_spawners_.at(i);
        ps->count ++;
        if(ps->count > ps->cooldown){
            ps->count = 0;
            Particle *particle = new Particle(100,QVector3D(0,0,0),QVector3D(0,0.1,0));
            ps->particles.push_back(particle);
        }

        ps->handleParticles();
        ps->drawParticles();
    }
}

void ParticleSpawner::drawParticles()
{
    glBindTexture( GL_TEXTURE_2D, texID );
    for(int i=0;i<particles.size();i++){
        particles.at(i)->draw();
    }
}


void ParticleSpawner::handleParticles()
{
    for(int i=0;i<particles.size();i++){
        particles.at(i)->handle();
        particles.at(i)->lifetime_--;

        if(particles.at(i)->lifetime_ < 0){
            delete particles.at(i);
            particles.removeAt(i);
        }
    }
}

void ParticleSpawner::loadTex(QString filename)
{
    QImage tex = QGLWidget::convertToGLFormat( QImage(filename) );
    //    GLuint texId;
    glGenTextures( 1, (GLuint*)&texID );
    glBindTexture( GL_TEXTURE_2D, texID );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, tex.width(), tex.height(), 0, GL_RGBA,GL_UNSIGNED_BYTE, tex.bits());
}


void ParticleSpawner::clearParticleSpawners()
{
    while(!particle_spawners_.empty()){
        delete particle_spawners_.first();
    }
}
