#include "person.h"

#ifndef HUMANITY_H
#define HUMANITY_H


struct Humanity{

    Person* firstPerson;
    Person* lastPerson;
    int length;
    int deaths;

    Humanity();
    void add(Person*, Person*, bool);
    Person* remove(int, Person*, bool);
    QVector<Person*> sort(SinType); //?
    Person* find(int, Person*, bool);
    void showHeap(SinType);
    QVector <Person*> killByHeap(int, SinType);
    QVector<Person*> killRandom(int);
    Person* killSpecific(int);
    Person * createPerson(int, int, int, int, int);
    int getRandomId();
    Person * resurrect(Person * person);
    void makeFriends();
    void restoreLog_();
};
#endif // HUMANITY_H
