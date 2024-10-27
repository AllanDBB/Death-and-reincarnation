#include "../../src/headers/humanity.h"
#include <QDebug>

Humanity::Humanity() {
    length = 0;
    firstPerson = nullptr;
    lastPerson = nullptr;
}

void Humanity::add(Person* person, Person* origin, bool direction) {
    if (length == 0) {
        firstPerson = person;
        lastPerson = person;
    } else if (direction) {
        Person *temp = origin;
        while (temp->rightPerson != nullptr && temp->rightPerson->id < person->id) {
            temp = temp->rightPerson;
        }

        person->rightPerson = temp->rightPerson;
        person->leftPerson = temp;

        if (temp->rightPerson != nullptr) {
            temp->rightPerson->leftPerson = person;
        }
        temp->rightPerson = person;

        if (person->rightPerson == nullptr) {
            lastPerson = person;
        }

    } else {
        Person *temp = origin;
        while (temp->leftPerson != nullptr && temp->leftPerson->id > person->id) {
            qDebug() << "ME MOVI IZQUIERDA";
            temp = temp->leftPerson;
        }

        person->leftPerson = temp->leftPerson;
        person->rightPerson = temp;

        if (temp->leftPerson != nullptr) {
            temp->leftPerson->rightPerson = person;
        }
        temp->leftPerson = person;

        if (person->leftPerson == nullptr) {
            firstPerson = person;
        }
    }

    length++;
}

Person* Humanity::remove(Person* person, Person* origin, bool direction) {
    if (length == 0) return nullptr;

    Person *temp = origin;

    if (direction) {
        while (temp != nullptr && person->id != temp->id) {
            temp = temp->rightPerson;
        }
    } else {
        while (temp != nullptr && person->id != temp->id) {
            temp = temp->leftPerson;
        }
    }

    if (temp == nullptr || temp->id != person->id) return nullptr;

    if (temp->leftPerson != nullptr) {
        temp->leftPerson->rightPerson = temp->rightPerson;
    } else {
        firstPerson = temp->rightPerson;
    }

    if (temp->rightPerson != nullptr) {
        temp->rightPerson->leftPerson = temp->leftPerson;
    } else {
        lastPerson = temp->leftPerson;
    }

    temp->leftPerson = nullptr;
    temp->rightPerson = nullptr;

    length--;

    return temp;
}

Person* Humanity::find(int id, Person* origin, bool direction){
    if (length == 0) return nullptr;

    Person * temp = origin;
    if (direction){
        while (id != temp->id && temp!=nullptr){
            temp = temp->rightPerson;
        }
    }
    else{
        while (id != temp->id && temp!=nullptr){
            temp = temp->leftPerson;
        }
    }
    return temp;
};
