#ifndef PARTICLE_H
#define PARTICLE_H

#include <QVector3D>
#include <QList>
#include <QColor>
#include <Objects3D/joint.h>

class Particle
{
public:
    Particle(int lifetime_, QVector3D position, QVector3D speed, QColor color);

    int lifetime_;

    QColor color;
    QVector3D position_;
    QVector3D speed_;

    virtual void draw();
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

    QColor color;

    Joint *joint;

//    int texID;

    ParticleSpawner(int cooldown, QColor color, Joint *parent);
    ~ParticleSpawner();

//     void loadTex(QString filename);
};

#endif // PARTICLE_H
