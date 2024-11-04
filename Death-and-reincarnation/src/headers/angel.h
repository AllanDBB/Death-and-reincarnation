#ifndef ANGEL_H
#define ANGEL_H

#include "../../src/headers/person.h"


struct Angel{
    QString name;
    int version;
    int generation;
    Person * saved;

    Angel * firstChild;
    Angel * secondChild;
    Angel * thirdChild;


    Angel(QString, int, int, Person*);
};


#endif // ANGEL_H
