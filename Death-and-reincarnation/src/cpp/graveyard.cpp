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


void heapify(QVector<Person*> arr, int n, int i, SinType sintype) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (sintype == 7){
        if (left < n && arr[left]->getSinSum() > arr[largest]->getSinSum()) {
            largest = left;
        }


        if (right < n && arr[right]->getSinSum() > arr[largest]->getSinSum()) {
            largest = right;
        }
    } else{

    if (left < n && arr[left]->sins[sintype] > arr[largest]->sins[sintype]) {
        largest = left;
    }


    if (right < n && arr[right]->sins[sintype] > arr[largest]->sins[sintype]) {
        largest = right;
    }}


    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest, sintype);
    }
}


void buildMaxHeap(QVector<Person*> arr, SinType sintype) {
    int n = arr.size();


    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, sintype);
    }
}

void printHeapAsTree(QVector<Person*>& arr, SinType sintype ) {
    int n = arr.size();
    int levels = std::log2(n) + 1;

    int maxWidth = std::pow(2, levels) * 2;

    int index = 0;
    for (int i = 0; i < levels; i++) {
        int levelNodes = std::pow(2, i);
        int spaceBetween = maxWidth / (levelNodes + 1);

        QString levelStr;
        levelStr = QString(" ").repeated(spaceBetween / 2);


        for (int j = 0; j < levelNodes && index < n; j++, index++) {
            if (sintype == 7){
                levelStr += QString("%1").arg(QString :: number(arr[index]->getSinSum()), spaceBetween);
            } else{
                levelStr += QString("%1").arg(QString :: number(arr[index]->sins[sintype]), spaceBetween);}
        }
        qDebug().noquote() << levelStr;
    }
}

void Graveyard::showHeap(SinType sin) {
    QVector<Person*> sortedList = sort(sin);
    buildMaxHeap(sortedList, sin);
    printHeapAsTree(sortedList,sin);}



