#include "../../src/headers/world.h"

World::World(Humanity* _humanity, Graveyard* _graveyard){
    humanity = _humanity;
    graveyard = _graveyard;
    length = humanity->length;
}

void World::generate(){
    int nodes = length/100;
    //todo
}
