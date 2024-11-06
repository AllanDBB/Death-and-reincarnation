#include "../../src/headers/graveyard.h"
#include <algorithm>
#include <cmath>
#include <QVector>
#include <QDebug>
#include <iomanip>
#include <QFile>
#include <QTextStream>


Graveyard::Graveyard(Humanity* _humanity){
    firstPerson = nullptr;
    lastPerson = nullptr;
    length = 0;
    humanity = _humanity;
}

void writeToFile(const QString& filename, const QString& text) {
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        QTextStream out(&file);
        out << text << "\n";
        file.close();
        qDebug() << "Texto escrito correctamente en" << filename;
    } else {
        qWarning() << "No se pudo abrir el archivo para escribir:" << filename;
    }
}

void clearFile(const QString& filename) {
    QFile file(filename);

    // Abre el archivo en modo de escritura con la opción Truncate para vaciarlo
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file.close();
        qDebug() << "Archivo limpiado correctamente:" << filename;
    } else {
        qWarning() << "No se pudo abrir el archivo para limpiar:" << filename;
    }
}

void Graveyard::restoreLog(){
    clearFile("C:/Users/natal/Desktop/sage/Death-and-reincarnation/Death-and-reincarnation/src/deathLog");

    Person * person = firstPerson;

    while (person!=nullptr){
        writeToFile("C:/Users/natal/Desktop/sage/Death-and-reincarnation/Death-and-reincarnation/src/deathLog", (QString::number(humanity->deaths) +"\t"+ person->timeOfDeath +"\t"+ person->typeOfDeath +"\t"+ person->toString()));
        person=person->rightPerson;
    }
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
    restoreLog();
    length++;
}



Person* Graveyard::remove(int id) {
    if (length == 0) return nullptr;

    Person* temp = firstPerson;
    while (temp != nullptr && temp->id != id) {
        temp = temp->rightPerson;
    }

    if (temp == nullptr) return nullptr;  // No se encuentra la persona con el ID especificado

    // Caso cuando la persona es la primera en la lista
    if (temp == firstPerson) {
        firstPerson = temp->rightPerson;
        if (firstPerson != nullptr) {
            firstPerson->leftPerson = nullptr;
        }
    } else {  // Caso cuando no es la primera persona
        if (temp->leftPerson != nullptr) {
            temp->leftPerson->rightPerson = temp->rightPerson;
        }
    }

    // Caso cuando la persona es la última en la lista
    if (temp == lastPerson) {
        lastPerson = temp->leftPerson;
        if (lastPerson != nullptr) {
            lastPerson->rightPerson = nullptr;
        }
    } else {  // Caso cuando no es la última persona
        if (temp->rightPerson != nullptr) {
            temp->rightPerson->leftPerson = temp->leftPerson;
        }
    }

    // Limpiamos los punteros del nodo eliminado
    temp->leftPerson = nullptr;
    temp->rightPerson = nullptr;

    // Actualizamos el contador de elementos en la lista
    length--;

    // Llamamos a la función que registra el log
    restoreLog();

    return temp;
}


Person* Graveyard::find(int id){
    if (length == 0) return nullptr;

    Person * temp = firstPerson;
    while (temp != nullptr && temp->id != id ){
        temp = temp->rightPerson;
    }
    return temp;
}



