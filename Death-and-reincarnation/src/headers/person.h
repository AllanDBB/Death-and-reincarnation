#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QVector>

enum SinType {
    LUST = 0,
    GLUTTONY = 1,
    GREED = 2,
    SLOTH = 3,
    WRATH = 4,
    ENVY = 5,
    PRIDE = 6,
    ALL = 7,
    };

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
    QString timeOfDeath;
    QString typeOfDeath;
    QVector<Person*> myFriends;
    QVector<Person> otherFriend;
    QVector<Person*> reincarnations;

    bool condition;

    Person(int, QString, QString, QString, QString, QString, QString);
    QString toString();
    int getSinSum ();

};



#endif // PERSON_H
