#ifndef HEAVEN_H
#define HEAVEN_H
#include "../../src/headers/angel.h"
#include "../../src/headers/graveyard.h"
#include "../../src/headers/world.h"

struct Heaven{
    Angel* root;
    int generation; //level
    Graveyard* graveyard;
    World* world;
    Humanity * humanity;

    int miguelVersion;
    int nurielVersion;
    int anielVersion;
    int rafaelVersion;
    int gabrielVersion;
    int shamsielVersion;
    int raguelVersion;
    int urielVersion;
    int azraelVersion;
    int sarielVersion;

    Heaven(Graveyard *, World *, Humanity *);
    QString reincarnatePerson();
    void backTozero();
    void generateLevel();
    int getVersion(const QString&);
};



#endif // HEAVEN_H
