#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "src/headers/person.h"
#include "src/headers/humanity.h"
#include "src/headers/graveyard.h"

int main(int argc, char *argv[])
{

    Humanity humanity = Humanity();
    Person* person1 = new Person(3, "Allan", "Bolanos", "23/03/06", "a", "a", "a");
    Person* person2 = new Person(1, "Natalia", "Delgado", "23/03/06", "a", "a", "a");
    Person* person3 = new Person(2, "Pepe", "Delgado", "23/03/06", "a", "a", "a");
    Person* person4 = new Person(4, "Pep", "Delgado", "23/03/06", "a", "a", "a");
    humanity.add(person1, nullptr, 1);
    humanity.add(person2, person1, 0);
    humanity.add(person3, person2, 1);
    humanity.add(person4, person3, 1);

    qDebug() << humanity.firstPerson->firstName;
    qDebug() << humanity.lastPerson->firstName;
    qDebug() << humanity.lastPerson->leftPerson->firstName;
    qDebug() << humanity.firstPerson->rightPerson->firstName;

    humanity.remove(person3, person4, 0);

    qDebug() << humanity.firstPerson->firstName;
    qDebug() << humanity.lastPerson->firstName;
    qDebug() << humanity.lastPerson->leftPerson->firstName;
    qDebug() << humanity.firstPerson->rightPerson->firstName;

    qDebug() << humanity.find(3,person2,1)->firstName;
    //qDebug() << humanity.find(2,person2,1)->firstName; se cae pq lo quite entonces hopefully funciona

    person1->sins[0] = 7;
    person2->sins[0] = 5;
    person3->sins[0] = 6;
    person4->sins[0] = 9;

    person1->sins[1] = 1;
    person2->sins[1] = 5;
    person3->sins[1] = 9;
    person4->sins[1] = 3;

    person1->sins[2] = 90;
    person2->sins[2] = 10;
    person3->sins[2] = 4;
    person4->sins[2] = 2;

    Graveyard graveyard = Graveyard();
    graveyard.add(person3);
    graveyard.add(person1);
    graveyard.add(person2);
    graveyard.add(person4);

    qDebug() << "---------";
    qDebug() << graveyard.firstPerson->firstName;
    qDebug() << graveyard.firstPerson->rightPerson->firstName;
    qDebug() << graveyard.lastPerson->leftPerson->firstName;
    qDebug() << graveyard.lastPerson->firstName;

    qDebug() << "---------";
    QVector<Person*> sortedList = graveyard.sort(ALL);
    qDebug() << "First Person:" << (sortedList.first()->firstName);
    qDebug() << "Last Person:" << (sortedList.last()->firstName);

    graveyard.remove(1);
    qDebug() << graveyard.firstPerson->firstName;
    qDebug() << graveyard.firstPerson->rightPerson->firstName;
    qDebug() << graveyard.lastPerson->firstName;

    qDebug() << graveyard.find(2)->firstName;

    graveyard.showHeap(sortedList, ALL);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
