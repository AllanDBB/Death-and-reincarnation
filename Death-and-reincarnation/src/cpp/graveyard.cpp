#include "../../src/headers/graveyard.h"
#include <algorithm>
#include <cmath>
#include <QVector>
#include <QDebug>
#include <iomanip>


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



