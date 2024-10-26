#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "src/headers/person.h"
#include "src/headers/humanity.h"

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
    qDebug() << humanity.firstPerson->rightPerson->rightPerson->firstName;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
