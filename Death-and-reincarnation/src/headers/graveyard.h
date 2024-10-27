#include "person.h"

#ifndef GRAVEYARD_H
#define GRAVEYARD_H

enum SinType { //MAYBE HAY QUE PASARLO A UN HEADER APARTE
    LUST = 0,
    GLUTTONY = 1,
    GREED = 2,
    SLOTH = 3,
    WRATH = 4,
    ENVY = 5,
    PRIDE = 6,
    ALL = 7,
};

struct Graveyard{

    Person* firstPerson;
    Person* lastPerson;
    int length;

    Graveyard();
    void add(Person*);
    QVector<Person*> sort(SinType);
    Person* remove(int);
    Person* find(int);
    void showHeap(QVector<Person*>, SinType);
    Person* killByHeap(int);
    Person* killRandom();
    Person* killSpecific(int);
};
#endif // GRAVEYARD_H
