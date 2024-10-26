#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QVector>

struct Person {

    Person* leftPerson;
    Person* rightPerson;

    int id;
    int sins[7] = {0,0,0,0,0,0,0};

    QString firstName;
    QString lastName;
    QString country;
    QString belief;
    QString profession;
    QString birthDate;
    QVector<Person> myFriends;
    QVector<Person> otherFriend;
    QVector<Person> reincarnations;

    bool condition;

    Person(int, QString, QString, QString, QString, QString, QString);

};



#endif // PERSON_H
