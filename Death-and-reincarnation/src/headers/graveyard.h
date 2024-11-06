#include "person.h"
#include "humanity.h"

#ifndef GRAVEYARD_H
#define GRAVEYARD_H



struct Graveyard{

    Person* firstPerson;
    Person* lastPerson;
    int length;
    Humanity * humanity;

    Graveyard(Humanity *);
    void add(Person*);
    QVector<Person*> sort(SinType);
    Person* remove(int);
    Person* find(int);
    void restoreLog();

};
#endif // GRAVEYARD_H
