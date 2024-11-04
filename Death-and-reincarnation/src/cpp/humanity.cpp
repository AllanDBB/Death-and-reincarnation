#include "../../src/headers/humanity.h"
#include <QDebug>
#include <QRandomGenerator>
#include "../../src/headers/graveyard.h"
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRandomGenerator>
#include <QDebug>
#include <QDateTime>

Humanity::Humanity() {
    length = 0;
    firstPerson = nullptr;
    lastPerson = nullptr;
}

QString readRandomLine(const QString& filename, int quantity) {
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
    int randomIndex = QRandomGenerator::global()->bounded(quantity);

    return lines[randomIndex]; // Devuelve la línea aleatoria
}

int Humanity::getRandomId(){
    int random = QRandomGenerator::global()->bounded(1000000);
    while (find(random, firstPerson,1)!=nullptr){
        random = QRandomGenerator::global()->bounded(1000000);
    }
    return random;
}

Person * Humanity::createPerson(int name, int lastName, int religion, int major, int country){
    QString filename_names="names.txt";
    QString randomLine_names = readRandomLine(filename_names, name);

    QString filename_lastNames="lastNames.txt";
    QString randomLine_lastNames = readRandomLine(filename_lastNames, lastName);

    QString filename_religion="religion.txt";
    QString randomLine_religion = readRandomLine(filename_religion, religion);

    QString filename_major="major.txt";
    QString randomLine_major = readRandomLine(filename_major, major);

    QString filename_country="country.txt";
    QString randomLine_country = readRandomLine(filename_country, country);

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");

    Person * person = new Person(getRandomId(), randomLine_names, randomLine_lastNames, randomLine_country, randomLine_religion, randomLine_major, formattedDateTime);

    return person;
}

Person * Humanity::resurrect(Person * person){
    QString filename_names="names.txt";
    QString randomLine_names = readRandomLine(filename_names, 1000);

    QString filename_lastNames="lastNames.txt";
    QString randomLine_lastNames = readRandomLine(filename_lastNames, 1000);

    QString filename_religion="religion.txt";
    QString randomLine_religion = readRandomLine(filename_religion, 20);

    QString filename_major="major.txt";
    QString randomLine_major = readRandomLine(filename_major, 100);

    QString filename_country="country.txt";
    QString randomLine_country = readRandomLine(filename_country, 100);

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");

    person->firstName = randomLine_names;
    person->lastName = randomLine_lastNames;
    person->belief = randomLine_religion;
    person->profession = randomLine_major;
    person->country = randomLine_country;
    person->birthDate = formattedDateTime;

    return person;
}

void Humanity::add(Person* person, Person* origin, bool direction) {
    if (length == 0) {
        firstPerson = person;
        lastPerson = person;
    } else if (direction) {
        Person *temp = origin;
        while (temp->rightPerson != nullptr && temp->rightPerson->id < person->id) {
            temp = temp->rightPerson;
        }

        person->rightPerson = temp->rightPerson;
        person->leftPerson = temp;

        if (temp->rightPerson != nullptr) {
            temp->rightPerson->leftPerson = person;
        }
        temp->rightPerson = person;

        if (person->rightPerson == nullptr) {
            lastPerson = person;
        }

    } else {
        Person *temp = origin;
        while (temp->leftPerson != nullptr && temp->leftPerson->id > person->id) {
            qDebug() << "ME MOVI IZQUIERDA";
            temp = temp->leftPerson;
        }

        person->leftPerson = temp->leftPerson;
        person->rightPerson = temp;

        if (temp->leftPerson != nullptr) {
            temp->leftPerson->rightPerson = person;
        }
        temp->leftPerson = person;

        if (person->leftPerson == nullptr) {
            firstPerson = person;
        }
    }

    length++;
}

Person* Humanity::remove(int id, Person* origin, bool direction) {
    if (length == 0) return nullptr;

    Person *temp = origin;

    if (direction) {
        while (temp != nullptr && id != temp->id) {
            temp = temp->rightPerson;
        }
    } else {
        while (temp != nullptr && id != temp->id) {
            temp = temp->leftPerson;
        }
    }

    if (temp == nullptr || temp->id != id) return nullptr;

    if (temp->leftPerson != nullptr) {
        temp->leftPerson->rightPerson = temp->rightPerson;
    } else {
        firstPerson = temp->rightPerson;
    }

    if (temp->rightPerson != nullptr) {
        temp->rightPerson->leftPerson = temp->leftPerson;
    } else {
        lastPerson = temp->leftPerson;
    }

    temp->leftPerson = nullptr;
    temp->rightPerson = nullptr;

    length--;

    return temp;
}

Person* Humanity::find(int id, Person* origin, bool direction) {
    qDebug() << "entrar apenas";
    if (length == 0) return nullptr;

    Person *temp = origin;

    if (direction) {
        qDebug() << "si direccion";
        while (temp != nullptr && id != temp->id) {
            temp = temp->rightPerson;
        }
    } else {
        qDebug() << "no direccion ";
        while (temp != nullptr && id != temp->id) {
            temp = temp->leftPerson;
        }
    }

    if (temp->id != id){
        return nullptr;
    }

    return temp;
}


QVector<Person*> Humanity::sort(SinType sinType) {
    QVector<Person*> sortedPersons;
    Person* current = firstPerson;

    while (current != nullptr) {
        sortedPersons.push_back(current);
        current = current->rightPerson;
    }

    auto comparator = [sinType](Person* a, Person* b) {
        switch (sinType) {
        case GREED: return a->sins[2] > b->sins[2];
        case ENVY: return a->sins[5] > b->sins[5];
        case SLOTH: return a->sins[3] > b->sins[3];
        case LUST: return a->sins[0] > b->sins[0];
        case PRIDE: return a->sins[6] > b->sins[6];
        case GLUTTONY: return a->sins[1] > b->sins[1];
        case WRATH: return a->sins[4] > b->sins[4];
        case ALL: return a->getSinSum() > b->getSinSum();
        default: return false;
        }
    };

    std::sort(sortedPersons.begin(), sortedPersons.end(), comparator);

    return sortedPersons;
}


void heapify(QVector<Person*> arr, int n, int i, SinType sintype) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (sintype == 7){
        if (left < n && arr[left]->getSinSum() > arr[largest]->getSinSum()) {
            largest = left;
        }


        if (right < n && arr[right]->getSinSum() > arr[largest]->getSinSum()) {
            largest = right;
        }
    } else{

        if (left < n && arr[left]->sins[sintype] > arr[largest]->sins[sintype]) {
            largest = left;
        }


        if (right < n && arr[right]->sins[sintype] > arr[largest]->sins[sintype]) {
            largest = right;
        }}


    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest, sintype);
    }
}


void buildMaxHeap(QVector<Person*> arr, SinType sintype) {
    int n = arr.size();


    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, sintype);
    }
}

void printHeapAsTree(QVector<Person*>& arr, SinType sintype ) {
    int n = arr.size();
    int levels = std::log2(n) + 1;

    int maxWidth = std::pow(2, levels) * 2;

    int index = 0;
    for (int i = 0; i < levels; i++) {
        int levelNodes = std::pow(2, i);
        int spaceBetween = maxWidth / (levelNodes + 1);

        QString levelStr;
        levelStr = QString(" ").repeated(spaceBetween / 2);


        for (int j = 0; j < levelNodes && index < n; j++, index++) {
            if (sintype == 7){
                levelStr += QString("%1").arg(QString :: number(arr[index]->getSinSum()), spaceBetween);
            } else{
                levelStr += QString("%1").arg(QString :: number(arr[index]->sins[sintype]), spaceBetween);}
        }
        qDebug().noquote() << levelStr;
    }
}

void Humanity::showHeap(SinType sin) {
    QVector<Person*> sortedList = sort(sin);
    buildMaxHeap(sortedList, sin);
    printHeapAsTree(sortedList,sin);}

QVector <Person*> Humanity::killByHeap(int levels, SinType sinType){ //conectar con el graveyard
    QVector<Person*> sortedList = sort(sinType);
    buildMaxHeap(sortedList, sinType);

    int toDelete = pow(2,levels)-1;
    QVector <Person*> killed;

    if (toDelete>length){
        return killed;
    }


    while (toDelete>0){
        Person * temp = (Person*) sortedList.front();
        sortedList.pop_front();
        remove(temp->id,firstPerson,1); //idk para muchos
        killed.append(temp);
        toDelete--;
    };

    return killed;

}

QVector<Person*> Humanity::killRandom(int probability) {

    QVector<Person*> dead;

    Person* temp = firstPerson;

    while (temp!=nullptr){
        if (QRandomGenerator::global()->bounded(length) <= probability){
            dead.append(temp);
            remove(temp->id, temp->leftPerson, 1);
        }
        temp = temp->rightPerson;
    }

    return dead;
}


Person* Humanity::killSpecific(int id){ //acoplarlo al arbol

    Person *toKill = find(id, firstPerson, 1);



    if (toKill == nullptr) {

        return nullptr;
    }


    Person *removedPerson = remove(toKill->id, toKill->leftPerson, 1);



    if (removedPerson != nullptr) {

        return removedPerson;
    }


    return nullptr;
}

