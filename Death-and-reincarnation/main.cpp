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
    Graveyard graveyard = Graveyard(&humanity);
    World world = World(&humanity, &graveyard);


    for (int i = 0; i<100; i++){
        Person * p =humanity.createPerson(1000,1000,20,100,100);
        world.add(p);
    }


    humanity.humansSin();
    humanity.restoreLog_();


    QVector <Person*> people = humanity.killByHeap(5,ALL);

    for (Person * p: people){
        qDebug()<<".";
        world.remove(p->id);
        graveyard.add(p);
    }

    graveyard.restoreLog();
    humanity.restoreLog_();
    qDebug()<< QString::number(graveyard.length);
    qDebug()<<"************";

    humanity.showHeap(ALL);
    qDebug()<<"************";
    qDebug()<<"#####";
    qDebug()<< QString::number(graveyard.length);
    Heaven heaven = Heaven(&graveyard,&world,&humanity);

    heaven.generateLevel();

    graveyard.restoreLog();
    humanity.restoreLog_();



    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
