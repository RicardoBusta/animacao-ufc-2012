#ifndef PARTICLE_H
#define PARTICLE_H

#include <QVector3D>
#include <QList>
#include <QColor>
#include <Objects3D/joint.h>

class Particle
{
public:
    Particle(/*int lifetime_, QVector3D position, QVector3D speed, QColor color1, QColor color2*/);

    int life_;
    int lifetime_;

    //QColor color1_;
    //QColor color2_;
    QVector3D position_;
    QVector3D speed_;

    virtual float interpolate();
    virtual void draw();
    virtual QColor color()=0;
    virtual void handle()=0;
};

class SparkParticle :public Particle{
public:
    SparkParticle(int lifetime_, QVector3D position);

    QColor color_;

    virtual QColor color();
    virtual void handle();
};

class SmokeParticle :public Particle{
public:
    SmokeParticle(int lifetime_, QVector3D position);

    QColor color_;

    virtual QColor color();
    virtual void handle();
};

class FireParticle :public Particle{
public:
    FireParticle(int lifetime_, QVector3D position);

    QColor color1_;
    QColor color2_;
    QVector3D center_;

    virtual QColor color();
    virtual void handle();
};

class ParticleSpawner{
public:
    static QList<ParticleSpawner*> particle_spawners_;
    static void handleParticleSpawners();
    static void clearParticleSpawners();

    QList<Particle*> particles;
    void drawParticles();
    void handleParticles();

    void generateParticle(int number, int type);

    int count;

    int cooldown;

    QVector3D position;
    QVector3D offset;

    QColor color;

    Joint *joint;

    int type;

//    int texID;

    ParticleSpawner(int cooldown, QVector3D offset, QColor color, Joint *parent, int type);
    ~ParticleSpawner();

//     void loadTex(QString filename);
};

#endif // PARTICLE_H
