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


QString readRandomLine(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error al abrir el archivo:" << filename;
        return QString();
    }

    QStringList lines;
    QTextStream in(&file);

    // Lee todas las líneas del archivo y las almacena en un QStringList
    while (!in.atEnd()) {
        QString line = in.readLine();
        lines.append(line);
    }
    file.close();

    if (lines.isEmpty()) {
        qWarning() << "El archivo está vacío.";
        return QString();
    }

    // Genera un índice aleatorio
    int randomIndex = QRandomGenerator::global()->bounded(lines.size());

    return lines[randomIndex]; // Devuelve la línea aleatoria
}

void Heaven:: backTozero(){

    miguelVersion = 0;
    nurielVersion = 0;
    anielVersion = 0;
    rafaelVersion = 0;
    gabrielVersion = 0;
    shamsielVersion = 0;
    raguelVersion = 0;
    urielVersion = 0;
    azraelVersion = 0;
    sarielVersion = 0;
}


Heaven :: Heaven (Graveyard* _graveyard, World* _world, Humanity * _humanity){
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

void Heaven::generateLevel(){
    backTozero();
    if (!root) return;

    std::queue<Angel*> nodeQueue;
    nodeQueue.push(root);
    int currentLevel = 0;

    while (!nodeQueue.empty() && currentLevel < (currentLevel+1)) {
        int nodesInLevel = nodeQueue.size();
        for (int i = 0; i < nodesInLevel; ++i) {
            Angel* node = nodeQueue.front();
            nodeQueue.pop();

            QString filename="angelName.txt";

            generation++;
            if (!node->firstChild) {
                QString randomLine = readRandomLine(filename);
                int vers = 0;
                if(randomLine == "Miguel"){
                    miguelVersion++;
                    vers = miguelVersion;
                } else if (randomLine == "Nuriel"){
                    nurielVersion++;
                    vers = nurielVersion;
                }else if (randomLine == "Aniel"){
                    anielVersion++;
                    vers = anielVersion;
                }else if (randomLine == "Rafael"){
                    rafaelVersion++;
                    vers = rafaelVersion;
                }else if (randomLine == "Gabriel"){
                    gabrielVersion++;
                    vers = gabrielVersion;
                }else if (randomLine == "Shamsiel"){
                    shamsielVersion++;
                    vers = shamsielVersion;
                }else if (randomLine == "Raguel"){
                    raguelVersion++;
                    vers = raguelVersion;
                }else if (randomLine == "Uriel"){
                    urielVersion++;
                    vers = urielVersion;
                }else if (randomLine == "Azrael"){
                    azraelVersion++;
                    vers = azraelVersion;
                }else if (randomLine == "Sariel"){
                    sarielVersion++;
                    vers = sarielVersion;
                }



                node->firstChild = new Angel(randomLine, vers, generation, graveyard->firstPerson);
                graveyard->firstPerson->reincarnations.append(graveyard->firstPerson);
                Person * newPerson = humanity->resurrect(graveyard->firstPerson);
                newPerson->sins[0] = graveyard->firstPerson->sins[0]/2;
                newPerson->sins[1] = graveyard->firstPerson->sins[1]/2;
                newPerson->sins[2] = graveyard->firstPerson->sins[2]/2;
                newPerson->sins[3] = graveyard->firstPerson->sins[3]/2;
                newPerson->sins[4] = graveyard->firstPerson->sins[4]/2;
                newPerson->sins[5] = graveyard->firstPerson->sins[5]/2;
                newPerson->sins[6] = graveyard->firstPerson->sins[6]/2;
                world->add(newPerson);
                graveyard->remove(graveyard->firstPerson->id);
            }
            if (!node->secondChild) {

                QString randomLine = readRandomLine(filename);
                int vers = 0;
                if(randomLine == "Miguel"){
                    miguelVersion++;
                    vers = miguelVersion;
                } else if (randomLine == "Nuriel"){
                    nurielVersion++;
                    vers = nurielVersion;
                }else if (randomLine == "Aniel"){
                    anielVersion++;
                    vers = anielVersion;
                }else if (randomLine == "Rafael"){
                    rafaelVersion++;
                    vers = rafaelVersion;
                }else if (randomLine == "Gabriel"){
                    gabrielVersion++;
                    vers = gabrielVersion;
                }else if (randomLine == "Shamsiel"){
                    shamsielVersion++;
                    vers = shamsielVersion;
                }else if (randomLine == "Raguel"){
                    raguelVersion++;
                    vers = raguelVersion;
                }else if (randomLine == "Uriel"){
                    urielVersion++;
                    vers = urielVersion;
                }else if (randomLine == "Azrael"){
                    azraelVersion++;
                    vers = azraelVersion;
                }else if (randomLine == "Sariel"){
                    sarielVersion++;
                    vers = sarielVersion;
                }



                node->secondChild = new Angel(randomLine, vers, generation, graveyard->firstPerson);
                graveyard->firstPerson->reincarnations.append(graveyard->firstPerson);
                Person * newPerson = humanity->resurrect(graveyard->firstPerson);
                newPerson->sins[0] = graveyard->firstPerson->sins[0]/2;
                newPerson->sins[1] = graveyard->firstPerson->sins[1]/2;
                newPerson->sins[2] = graveyard->firstPerson->sins[2]/2;
                newPerson->sins[3] = graveyard->firstPerson->sins[3]/2;
                newPerson->sins[4] = graveyard->firstPerson->sins[4]/2;
                newPerson->sins[5] = graveyard->firstPerson->sins[5]/2;
                newPerson->sins[6] = graveyard->firstPerson->sins[6]/2;
                world->add(newPerson);
                graveyard->remove(graveyard->firstPerson->id);
            }
            if (!node->thirdChild) {

                QString randomLine = readRandomLine(filename);
                int vers = 0;
                if(randomLine == "Miguel"){
                    miguelVersion++;
                    vers = miguelVersion;
                } else if (randomLine == "Nuriel"){
                    nurielVersion++;
                    vers = nurielVersion;
                }else if (randomLine == "Aniel"){
                    anielVersion++;
                    vers = anielVersion;
                }else if (randomLine == "Rafael"){
                    rafaelVersion++;
                    vers = rafaelVersion;
                }else if (randomLine == "Gabriel"){
                    gabrielVersion++;
                    vers = gabrielVersion;
                }else if (randomLine == "Shamsiel"){
                    shamsielVersion++;
                    vers = shamsielVersion;
                }else if (randomLine == "Raguel"){
                    raguelVersion++;
                    vers = raguelVersion;
                }else if (randomLine == "Uriel"){
                    urielVersion++;
                    vers = urielVersion;
                }else if (randomLine == "Azrael"){
                    azraelVersion++;
                    vers = azraelVersion;
                }else if (randomLine == "Sariel"){
                    sarielVersion++;
                    vers = sarielVersion;
                }



                node->thirdChild = new Angel(randomLine, vers, generation, graveyard->firstPerson);
                graveyard->firstPerson->reincarnations.append(graveyard->firstPerson);
                Person * newPerson = humanity->resurrect(graveyard->firstPerson);
                newPerson->sins[0] = graveyard->firstPerson->sins[0]/2;
                newPerson->sins[1] = graveyard->firstPerson->sins[1]/2;
                newPerson->sins[2] = graveyard->firstPerson->sins[2]/2;
                newPerson->sins[3] = graveyard->firstPerson->sins[3]/2;
                newPerson->sins[4] = graveyard->firstPerson->sins[4]/2;
                newPerson->sins[5] = graveyard->firstPerson->sins[5]/2;
               newPerson->sins[6] = graveyard->firstPerson->sins[6]/2;
                world->add(newPerson);
                graveyard->remove(graveyard->firstPerson->id);
            }


            nodeQueue.push(node->firstChild);
            nodeQueue.push(node->secondChild);
            nodeQueue.push(node->thirdChild);
        }
        currentLevel++;
    }
}




