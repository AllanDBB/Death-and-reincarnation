#include "../../src/headers/humanity.h"
#include <QDebug>

Humanity::Humanity(){
    length = 0;
    firstPerson = nullptr;
    lastPerson = nullptr;
}

void Humanity::add(Person* person, Person* origin, bool direction){

    if (length == 0){
        firstPerson = person;
        lastPerson = person;
    } else if(direction){

        Person * temp = origin;
        while (temp->rightPerson != nullptr && temp->rightPerson->id < person->id){
            temp = temp->rightPerson;
        }

        person->rightPerson = temp->rightPerson;
        person->leftPerson = temp;
        if (length != 1)
            temp->rightPerson->leftPerson = person;
        temp->rightPerson = person;

        if (person->rightPerson == nullptr)
            lastPerson = person;

    } else {
        Person * temp = origin;
        while (temp->leftPerson != nullptr && temp->leftPerson->id > person->id ){
            qDebug() <<  "ME MOVI IZQUIERDA";
            temp = temp->leftPerson;
        }

        person->leftPerson = temp->leftPerson;
        person->rightPerson = temp;
        if (length != 1)
            temp->leftPerson->rightPerson = person;
        temp->leftPerson = person;

        if(person->leftPerson == nullptr)
            firstPerson = person;
    }

    length++;
}
