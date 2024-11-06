#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "src/headers/person.h"
#include "src/headers/humanity.h"
#include "src/headers/graveyard.h"
#include "src/headers/world.h"
#include "src/headers/heaven.h"
#include "./ui_mainwindow.h"


int main(int argc, char *argv[])
{

    Humanity humanity = Humanity();
    Person* person1 = new Person(1, "persona 1", "Bolanos", "23/03/06", "a", "a", "a");
    Person* person2 = new Person(2, "persona 2", "Delgado", "23/03/06", "a", "a", "a");
    Person* person3 = new Person(3, "persona 3", "Delgado", "23/03/06", "a", "a", "a");
    Person* person4 = new Person(4, "persona 4", "Delgado", "23/03/06", "a", "a", "a");
    //Person* person5 = new Person(5, "persona 5", "Bolanos", "23/03/06", "a", "a", "a");
    //Person* person6 = new Person(6, "persona 6", "Delgado", "23/03/06", "a", "a", "a");
    //Person* person7 = new Person(7, "persona 7", "Delgado", "23/03/06", "a", "a", "a");
    //Person* person8 = new Person(8, "persona 8", "Delgado", "23/03/06", "a", "a", "a");
    //Person* person9 = new Person(9, "persona 9", "Bolanos", "23/03/06", "a", "a", "a");
    //Person* person10 = new Person(10, "persona 10", "Delgado", "23/03/06", "a", "a", "a");

    humanity.add(person1, nullptr, 1);
    humanity.add(person2, person1, 0);
    humanity.add(person3, person2, 1);
    humanity.add(person4, person3, 1);
    //humanity.add(person5, person4, 1);
    //humanity.add(person6, person5, 1);
    //humanity.add(person7, person6, 1);
    //humanity.add(person8, person7, 1);
    //humanity.add(person9, person8, 1);
    //humanity.add(person10, person9, 1);

    qDebug() << humanity.firstPerson->firstName;
    qDebug() << humanity.lastPerson->firstName;
    qDebug() << humanity.lastPerson->leftPerson->firstName;
    qDebug() << humanity.firstPerson->rightPerson->firstName;

    //humanity.remove(person3, person4, 0);
    //humanity.showHeap(LUST);

    qDebug() << humanity.firstPerson->firstName;
    qDebug() << humanity.lastPerson->firstName;
    qDebug() << humanity.lastPerson->leftPerson->firstName;
    qDebug() << humanity.firstPerson->rightPerson->firstName;

    qDebug() << humanity.find(3,person2,1)->firstName;
    //qDebug() << humanity.find(2,person2,1)->firstName; se cae pq lo quite entonces hopefully funciona

    person1->sins[0] = 7;
    person2->sins[0] = 5;
    person3->sins[0] = 6;
    person4->sins[0] = 8;

    person1->sins[1] = 1;
    person2->sins[1] = 5;
    person3->sins[1] = 3;
    person4->sins[1] = 3;

    person1->sins[2] = 5;
    person2->sins[2] = 0;
    person3->sins[2] = 4;
    person4->sins[2] = 2;
    humanity.showHeap(LUST);


    Graveyard graveyard = Graveyard(&humanity);

    for (int i = 1; i<100; i++){
        Person * p =humanity.createPerson(100,100,100,20,20);
        humanity.add(p,humanity.firstPerson,1);
    }
    World world = World(&humanity, &graveyard);

    humanity.humansSin();
    humanity.restoreLog_();

    QVector <Person*> people = humanity.killByHeap(5,ALL);
    ;

    for (Person * p: people){
        humanity.remove(p->id, humanity.firstPerson, 1);
        graveyard.add(p);
    }

    graveyard.restoreLog();
    qDebug()<<"************";

    humanity.showHeap(ALL);
    qDebug()<<"************";
    qDebug()<<"#####";
    qDebug()<< QString::number(graveyard.length);
    Heaven heaven = Heaven(&graveyard,&world,&humanity);

    //heaven.generateLevel();


    //graveyard.restoreLog();




    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
