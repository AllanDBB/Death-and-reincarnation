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
    if (!root) return;

    // Cola para procesar solo las hojas
    std::queue<Angel*> nodeQueue;
    nodeQueue.push(root);

    // Crear el siguiente nivel de nodos
    while (!nodeQueue.empty()) {
        Angel* node = nodeQueue.front();
        nodeQueue.pop();

        if (node == nullptr) continue;  // Asegúrate de no procesar nodos nulos

        // Si el nodo no tiene hijos, lo procesamos
        if (node->firstChild == nullptr && node->secondChild == nullptr && node->thirdChild == nullptr) {
            // Crear los 3 hijos para este nodo
            QString randomLine = readRandomLine_("C:/Users/natal/Desktop/sage/Death-and-reincarnation/Death-and-reincarnation/src/angelNames", 10);
            int vers = getVersion(randomLine);
            node->firstChild = new Angel(randomLine, vers, generation, graveyard->firstPerson);
            reincarnatePerson();

            qDebug()<<"pipipipi";
            randomLine = readRandomLine_("C:/Users/natal/Desktop/sage/Death-and-reincarnation/Death-and-reincarnation/src/angelNames", 10);
            vers = getVersion(randomLine);
            qDebug()<<"adios";
            node->secondChild = new Angel(randomLine, vers, generation, graveyard->firstPerson);
            qDebug()<<"gsdghbek";
            reincarnatePerson();
            qDebug()<<"casi fin";

            randomLine = readRandomLine_("C:/Users/natal/Desktop/sage/Death-and-reincarnation/Death-and-reincarnation/src/angelNames", 10);
            vers = getVersion(randomLine);
            qDebug()<<"pre angel";
            node->thirdChild = new Angel(randomLine, vers, generation, graveyard->firstPerson);
            reincarnatePerson();
            qDebug()<<"paso";

        } else {
            // Solo añadimos los hijos a la cola si existen
            if (node->firstChild) nodeQueue.push(node->firstChild);
            if (node->secondChild) nodeQueue.push(node->secondChild);
            if (node->thirdChild) nodeQueue.push(node->thirdChild);
        }
    }

    // Incrementar la generación para la próxima llamada
    generation++;
}




void Heaven::reincarnatePerson() {
    graveyard->firstPerson->reincarnations.append(graveyard->firstPerson);
    Person* newPerson = humanity->resurrect(graveyard->firstPerson);

    for (int i = 0; i < 7; ++i) {
        newPerson->sins[i] = graveyard->firstPerson->sins[i] / 2;
    }
    qDebug()<<"ayuda";
    world->add(newPerson);
    Person * p = graveyard->remove(graveyard->firstPerson->id);
    if (p==nullptr){
        qDebug()<<"{{{{{";}
}
