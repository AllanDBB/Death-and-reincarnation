#include "../../src/headers/heaven.h"
#include "../../src/headers/graveyard.h"
#include "../../src/headers/humanity.h"
#include <queue>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRandomGenerator>
#include <QDebug>
#include <QDateTime>

void generateResurrectionFile(const QString& content) {
    // Generar nombre de archivo con la fecha y hora actuales
    QString fileName = "resurrection_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".txt";

    QFile file("C:/Users/natal/Desktop/u" + fileName);

    // Intentar abrir el archivo en modo escritura
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "si entre";
        QTextStream out(&file);
        out << content;  // Escribe el contenido en el archivo
        file.close();
    } else {
        qDebug() << "Error al crear el archivo:" << fileName;
    }
}

QString readRandomLine_(const QString& filename, int quantity) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error al abrir el archivo:" << filename;
        return QString();
    }

    QTextStream in(&file);
    int randomIndex = QRandomGenerator::global()->bounded(quantity);
    for (int i = 0; i < randomIndex && !in.atEnd(); ++i) {
        in.readLine();  // Salta hasta la línea deseada
    }

    return in.readLine();  // Devuelve la línea aleatoria
}

void Heaven::backTozero() {
    miguelVersion = nurielVersion = anielVersion = 0;
    rafaelVersion = gabrielVersion = shamsielVersion = 0;
    raguelVersion = urielVersion = azraelVersion = sarielVersion = 0;
}

int Heaven::getVersion(const QString& name) {
    if (name == "Miguel") return ++miguelVersion;
    if (name == "Nuriel") return ++nurielVersion;
    if (name == "Aniel") return ++anielVersion;
    if (name == "Rafael") return ++rafaelVersion;
    if (name == "Gabriel") return ++gabrielVersion;
    if (name == "Shamsiel") return ++shamsielVersion;
    if (name == "Raguel") return ++raguelVersion;
    if (name == "Uriel") return ++urielVersion;
    if (name == "Azrael") return ++azraelVersion;
    if (name == "Sariel") return ++sarielVersion;
    return 0;
}

void getLeaves(Angel* root, QVector<Angel*>& leaves) {
    if (!root) return;

    // Si el nodo actual no tiene hijos, es una hoja
    if (!root->firstChild && !root->secondChild && !root->thirdChild) {
        leaves.append(root);
    } else {
        // Si tiene hijos, recursivamente buscamos las hojas en cada subárbol
        if (root->firstChild) getLeaves(root->firstChild, leaves);
        if (root->secondChild) getLeaves(root->secondChild, leaves);
        if (root->thirdChild) getLeaves(root->thirdChild, leaves);
    }
}


Heaven::Heaven(Graveyard* _graveyard, World* _world, Humanity* _humanity) {
    root = new Angel("GOD", 1, 0, nullptr);
    root->firstChild = new Angel("Serafines", 1, 1, nullptr);
    root->secondChild = new Angel("Querubines", 1, 1, nullptr);
    root->thirdChild = new Angel("Tronos", 1, 1, nullptr);

    root->firstChild->firstChild = new Angel("Angel", 1, 2, nullptr);
    root->firstChild->secondChild = new Angel("Angel", 2, 2, nullptr);
    root->firstChild->thirdChild = new Angel("Angel", 3, 2, nullptr);

    root->secondChild->firstChild = new Angel("Angel", 4, 2, nullptr);
    root->secondChild->secondChild = new Angel("Angel", 5, 2, nullptr);
    root->secondChild->thirdChild = new Angel("Angel", 6, 2, nullptr);

    root->thirdChild->firstChild = new Angel("Angel", 7, 2, nullptr);
    root->thirdChild->secondChild = new Angel("Angel", 8, 2, nullptr);
    root->thirdChild->thirdChild = new Angel("Angel", 9, 2, nullptr);

    generation = 3;
    graveyard = _graveyard;
    world = _world;
    humanity = _humanity;

    backTozero();
}

void Heaven::generateLevel() {
    QString forFile;
    QVector<Angel*> leaves;
    getLeaves(root, leaves);
    for (Angel * a: leaves){
        QString randomLine = readRandomLine_("C:/Users/natal/Desktop/sage/Death-and-reincarnation/Death-and-reincarnation/src/angelNames", 10);
        int vers = getVersion(randomLine);
        a->firstChild = new Angel(randomLine, vers, generation, graveyard->firstPerson);
        forFile.append(graveyard->firstPerson->toString()+" resucitó como: ");
        QString temp = reincarnatePerson();
        forFile.append(temp);
        forFile.append("\n");


        randomLine = readRandomLine_("C:/Users/natal/Desktop/sage/Death-and-reincarnation/Death-and-reincarnation/src/angelNames", 10);
        vers = getVersion(randomLine);
        a->secondChild = new Angel(randomLine, vers, generation, graveyard->firstPerson);
        forFile.append(graveyard->firstPerson->toString()+" resucitó como: ");
        temp = reincarnatePerson();
        forFile.append(temp);
        forFile.append("\n");

        randomLine = readRandomLine_("C:/Users/natal/Desktop/sage/Death-and-reincarnation/Death-and-reincarnation/src/angelNames", 10);
        vers = getVersion(randomLine);
        a->thirdChild = new Angel(randomLine, vers, generation, graveyard->firstPerson);
        forFile.append(graveyard->firstPerson->toString()+" resucitó como: ");
        temp = reincarnatePerson();
        forFile.append(temp);
        forFile.append("\n");
    }
    generateResurrectionFile(forFile);
    generation++;
}




QString Heaven::reincarnatePerson() {
    Person* newPerson = humanity->resurrect(graveyard->firstPerson);

    for (int i = 0; i < 7; ++i) {
        newPerson->sins[i] = graveyard->firstPerson->sins[i] / 2;
    }

    world->add(newPerson);
    newPerson->reincarnations.append(graveyard->firstPerson);
    graveyard->remove(graveyard->firstPerson->id);

    return newPerson->toString();
}
