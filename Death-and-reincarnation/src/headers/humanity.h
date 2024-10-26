#include "person.h"

#ifndef HUMANITY_H
#define HUMANITY_H


struct Humanity{

    Person* firstPerson;
    Person* lastPerson;
    int length;

    Humanity();
    void add(Person*);
    Person* remove();
    void sort();
    Person* find(int, Person*, bool);

};
#endif // HUMANITY_H
