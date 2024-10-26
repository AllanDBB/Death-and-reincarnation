#include "humanity.h"
#include "graveyard.h"

#ifndef WORLD_H
#define WORLD_H

struct World{

    Humanity* humanity;
    Graveyard* graveyard;
    int length;

    World(Humanity*, Graveyard*);
    void generate();
    Person search(int id);
    int getFreeId();
    void add(Person);
    void remove(int id);



};
#endif // WORLD_H
