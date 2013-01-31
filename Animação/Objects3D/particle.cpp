#include "particle.h"

#include <QtOpenGL>

#include "Utils/scenecontainer.h"
#include "Widgets/viewer.h"

#include <cstdlib>
#include <ctime>

Particle::Particle()
{
    //    this->color1_ = color1;
    //    this->color2_ = color2;
    //    this->position_ = position;
    //    this->speed_ = speed;
    //    this->lifetime_ = lifetime;
    //    this->life_ = lifetime_;
}

float Particle::interpolate()
{
    return ((float)lifetime_/(float)life_);
}

void Particle::draw()
{
    SceneContainer::viewer_reference_->bindShader();

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
    //    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    //glDisable(GL_LIGHTING);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(3);
    glColor4f( color().redF(), color().greenF(), color().blueF(), color().alphaF());
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

    glBegin(GL_POINTS);

    //    glTexCoord2f(0,0);
    glVertex3f(0,0,0);

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
//! SPARK PARTICLES
//-------------------

SparkParticle::SparkParticle(int lifetime, QVector3D position)
{
    float theta = ( ((float)(rand()%360000))*M_PI/180000 );
    float phi = ( ((float)(rand()%360000))*M_PI/180000 );
    float radius =  ( ((float)(rand()%100))/1000 );
    speed_ = QVector3D(radius*sin(phi)*cos(theta),radius*cos(phi),radius*sin(phi)*sin(theta));
    lifetime_ = lifetime;
    life_ = lifetime_;
    position_ = position;
    color_ = QColor(rand()%256,rand()%256,rand()%256);
}

void SparkParticle::handle()
{
//    speed_+= QVector3D(0,0.1,0);
    position_+=speed_;
}

QColor SparkParticle::color(){
    return QColor(color_.red(),color_.green(),color_.blue(),interpolate()*255);
}

//-------------------
//! SMOKE PARTICLES
//-------------------

SmokeParticle::SmokeParticle(int lifetime, QVector3D position)
{
    float theta = ( ((float)(rand()%360000))*M_PI/180000 );
    float phi = ( ((float)(rand()%360000))*M_PI/180000 );
    float radius =  ( ((float)(rand()%100))/1000 );
    speed_ = QVector3D(radius*sin(phi)*cos(theta),radius*cos(phi),radius*sin(phi)*sin(theta));
    lifetime_ = lifetime;
    life_ = lifetime_;
    position_ = position;
    int x = rand()%256;
    color_ = QColor(x,x,x);
}

void SmokeParticle::handle()
{
    //speed_+= QVector3D(0,0.1,0);
    position_+=speed_;
}

QColor SmokeParticle::color(){
    return QColor(color_.red(),color_.green(),color_.blue(),interpolate()*255);
}


//-------------------
//! FIRE PARTICLES
//-------------------

FireParticle::FireParticle(int lifetime, QVector3D position)
{
    float theta = ( ((float)(rand()%360000))*M_PI/180000 );
    float phi = ( ((float)(rand()%360000))*M_PI/180000 );
    float radius =  ( ((float)(rand()%100))/1000 );
    speed_ = QVector3D(3*radius*sin(phi)*cos(theta),radius*cos(phi)-0.2,3*radius*sin(phi)*sin(theta));
    lifetime_ = lifetime;
    life_ = lifetime_;
    position_ = position;
    center_ = position_;
}

void FireParticle::handle()
{
    float xdif = 0;
    if(position_.x() > center_.x()){
        xdif = -0.1;
    }else if(position_.x() < center_.x()){
        xdif = 0.1;
    }
    float zdif = 0;
    if(position_.z() > center_.z()){
        zdif = -0.1;
    }else if(position_.z() < center_.z()){
        zdif = 0.1;
    }
    speed_+= QVector3D(xdif,0.1,zdif);
    position_+=speed_;
}

QColor FireParticle::color(){
    return QColor( 255, interpolate()*255, 0 , 255*sqrt(interpolate()));
}

//-------------------
//! PARTICLE SPAWNER
//-------------------

QList<ParticleSpawner*> ParticleSpawner::particle_spawners_;

ParticleSpawner::ParticleSpawner(int cooldown, QVector3D offset, QColor color, Joint *parent, int type)
{
    this->offset = offset;
    this->type = type;
    this->joint = parent;
    this->color = color;
    this->count = 0;
    this->cooldown = cooldown;
    particle_spawners_.push_back(this);

    srand(time(0));
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
            ps->position = QVector3D(ps->joint->globalPosition().x,ps->joint->globalPosition().y,ps->joint->globalPosition().z);
            ps->count = 0;

            ps->generateParticle(20,ps->type);

        }

        ps->handleParticles();
        ps->drawParticles();
    }
}

void ParticleSpawner::drawParticles()
{
    //    glColor4f(color.red(),color.green(),color.blue(),color.alpha());
    //glBindTexture( GL_TEXTURE_2D, texID );
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

//void ParticleSpawner::loadTex(QString /*filename*/)
//{
//    QImage tex = QGLWidget::convertToGLFormat( QImage(filename) );
//    glGenTextures( 1, (GLuint*)&texID );
//    glBindTexture( GL_TEXTURE_2D, texID );
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    glTexImage2D(GL_TEXTURE_2D, 0, 4, tex.width(), tex.height(), 0, GL_RGBA,GL_UNSIGNED_BYTE, tex.bits());
//}


void ParticleSpawner::clearParticleSpawners()
{
    while(!particle_spawners_.empty()){
        delete particle_spawners_.first();
    }
}


void ParticleSpawner::generateParticle(int number, int type)
{
    Particle *particle;

    for(int i=0;i<number;i++){
        switch(type){
        case 0:
            //Sparkles
            particle = new SparkParticle(10+rand()%5,position+offset);
            particles.push_back(particle);
            break;
        case 1:
            //Fire
            particle = new FireParticle(10+rand()%5,position+offset);
            particles.push_back(particle);
            break;
        case 2:
            //Smoke
            particle = new SmokeParticle(10+rand()%5,position+offset);
            particles.push_back(particle);
            break;
        }
    }
}


