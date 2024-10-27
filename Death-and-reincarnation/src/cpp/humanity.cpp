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

void Humanity::showHeap(SinType sin) {
    QVector<Person*> sortedList = sort(sin);
    buildMaxHeap(sortedList, sin);
    printHeapAsTree(sortedList,sin);}

