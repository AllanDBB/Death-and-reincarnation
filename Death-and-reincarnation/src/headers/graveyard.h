#include "person.h"

#ifndef GRAVEYARD_H
#define GRAVEYARD_H

struct Graveyard{

    Person* firstPerson;
    Person* lastPerson;
    int length;

    Graveyard();
    void add(Person*);
    Person* remove();
    Person* find(int);

};
#endif // GRAVEYARD_H
