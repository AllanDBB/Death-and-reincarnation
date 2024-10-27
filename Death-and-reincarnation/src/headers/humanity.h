#include "person.h"

#ifndef HUMANITY_H
#define HUMANITY_H


struct Humanity{

    Person* firstPerson;
    Person* lastPerson;
    int length;

    Humanity();
    void add(Person*, Person*, bool);
    Person* remove(Person*, Person*, bool);
    QVector<Person*> sort(SinType); //?
    Person* find(int, Person*, bool);
    void showHeap(SinType);
    Person* killByHeap(int);
    Person* killRandom();
    Person* killSpecific(int);

};
#endif // HUMANITY_H
