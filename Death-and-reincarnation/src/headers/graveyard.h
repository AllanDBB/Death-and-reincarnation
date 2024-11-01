#include "person.h"

#ifndef GRAVEYARD_H
#define GRAVEYARD_H



struct Graveyard{

    Person* firstPerson;
    Person* lastPerson;
    int length;

    Graveyard();
    void add(Person*);
    QVector<Person*> sort(SinType);
    Person* remove(int);
    Person* find(int);

};
#endif // GRAVEYARD_H
