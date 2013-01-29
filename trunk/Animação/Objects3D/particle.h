#ifndef PARTICLE_H
#define PARTICLE_H

#include <QVector3D>
#include <QList>

class Particle
{
public:
    Particle(int lifetime_, QVector3D position, QVector3D speed);

    int lifetime_;

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

    int count;

    int cooldown;

    int texID;

    ParticleSpawner(int cooldown);
    ~ParticleSpawner();

     void loadTex(QString filename);
};

#endif // PARTICLE_H
