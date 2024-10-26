#include "../../src/headers/person.h"

Person::Person(int _id, QString _firstName, QString _lastName, QString _country, QString _belief, QString _profession, QString _birthDate){
    id = _id;
    firstName = _firstName;
    lastName = _lastName;
    country = _country;
    belief = _belief;
    profession = _profession;
    birthDate = _birthDate;
    condition = 1;

    leftPerson = nullptr;
    rightPerson = nullptr;
}
