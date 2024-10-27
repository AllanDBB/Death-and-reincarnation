#include "../../src/headers/graveyard.h"
#include <iostream>
#include <cmath>
#include <QVector>
#include <QDebug>


Graveyard::Graveyard(){
    firstPerson = nullptr;
    lastPerson = nullptr;
    length = 0;
}

void Graveyard::add(Person* person) {
    if (firstPerson == nullptr) {  // Lista vacía
        firstPerson = person;
        lastPerson = person;
    } else if (person->id < firstPerson->id) {  // Insertar al inicio
        person->rightPerson = firstPerson;
        firstPerson->leftPerson = person;
        firstPerson = person;
    } else if (person->id > lastPerson->id) {  // Insertar al final
        person->leftPerson = lastPerson;
        lastPerson->rightPerson = person;
        lastPerson = person;
    } else {  // Insertar en el medio
        Person* temp = firstPerson;
        while (temp->rightPerson != nullptr && temp->rightPerson->id < person->id) {
            temp = temp->rightPerson;
        }
        person->rightPerson = temp->rightPerson;
        person->leftPerson = temp;

        if (temp->rightPerson != nullptr) {
            temp->rightPerson->leftPerson = person;
        }
        temp->rightPerson = person;
    }
    length++;
}

QVector<Person*> Graveyard::sort(SinType sinType) {
    QVector<Person*> sortedPersons;
    Person* current = firstPerson;

    while (current != nullptr) {
        sortedPersons.push_back(current);
        current = current->rightPerson;
    }

    auto comparator = [sinType](Person* a, Person* b) {
        switch (sinType) {
        case GREED: return a->sins[2] > b->sins[2];
        case ENVY: return a->sins[5] > b->sins[5];
        case SLOTH: return a->sins[3] > b->sins[3];
        case LUST: return a->sins[0] > b->sins[0];
        case PRIDE: return a->sins[6] > b->sins[6];
        case GLUTTONY: return a->sins[1] > b->sins[1];
        case WRATH: return a->sins[4] > b->sins[4];
        case ALL: return a->getSinSum() > b->getSinSum();
        default: return false;
        }
    };

    std::sort(sortedPersons.begin(), sortedPersons.end(), comparator);

    return sortedPersons;
}

Person* Graveyard::remove(int id) {
    if (length == 0) return nullptr;

    Person* temp = firstPerson;
    while (temp != nullptr && temp->id != id) {
        temp = temp->rightPerson;
    }

    if (temp == nullptr) return nullptr;


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

Person* Graveyard::find(int id){
    if (length == 0) return nullptr;

    Person * temp = firstPerson;
    while (temp != nullptr && temp->id != id ){
        temp = temp->rightPerson;
    }
    return temp;
};

void Graveyard::showHeap(QVector<Person*> sortedList, SinType sin) { //problema para despues
}


Person* Graveyard::killByHeap(int levels){

}

