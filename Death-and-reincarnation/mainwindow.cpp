#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "src/headers/person.h"
#include "src/headers/humanity.h"
#include "src/headers/graveyard.h"
#include "src/headers/world.h"
#include "src/headers/heaven.h"
#include "src/headers/person.h"
#include "./ui_mainwindow.h"

#include <QSpinBox>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QString>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QSet>
#include <QVector>


Humanity *humanity;
Graveyard *graveyard;
World *world;
Heaven *heaven;

QSet<Angel*> visitedNodes;
Angel* angelsRoot = nullptr;

QSpinBox *spinBox;
QSpinBox *spinBox2;
QSpinBox *spinBox3;
QSpinBox *spinBox4;
QSpinBox *spinBox5;
QSpinBox *spinBox6;
QSpinBox *spinBox7;
QSpinBox *spinBox8;
QSpinBox *spinBox9;
QSpinBox *spinBox10;
QSpinBox *spinBox11;

QLCDNumber *lcdNumber;
QLCDNumber *lcdNumber2;

QLabel *Qlabel;
QLabel *Qlabel2;
QLabel *Qlabel3;
QLabel *Qlabel4;
QLabel *Qlabel5;
QLabel *Qlabel6;
QLabel *Qlabel7;
QLabel *Qlabel8;
QLabel *Qlabel9;
QLabel *Qlabel10;
QLabel *Qlabel11;

QPushButton *button;
QPushButton *button2;
QPushButton *button3;
QPushButton *button4;
QPushButton *button5;
QPushButton *button6;
QPushButton *button7;
QPushButton *button8;
QPushButton *button9;

QTextEdit *textEdit;
QTextEdit *textEdit2;


QTreeWidget* treeWidget;
QTreeWidget* treeWidget2;

int idSearch;
int amountNames;
int amountLastnames;
int amountCountries;
int amountProfessions;
int amountBelives;
int amountToCreate;
int idToRemove;
int levelOfHeap;
int sinType;
int probRandom;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , worker1(new Worker())
    , worker2(new Worker())

{
    ui->setupUi(this);

    // Initialize game
    humanity = new Humanity();
    graveyard = new Graveyard(humanity);
    world = new World(humanity, graveyard);
    heaven = new Heaven(graveyard,world,humanity);
    treeWidget = findChild<QTreeWidget *>("treeWidget");
    treeWidget2 = findChild<QTreeWidget *>("treeWidget_2");

    // Create human:
    spinBox = findChild<QSpinBox *>("spinBox"); // names
    spinBox2 = findChild<QSpinBox *>("spinBox_2"); // lastnames
    spinBox3 = findChild<QSpinBox *>("spinBox_3"); // countries
    spinBox4 = findChild<QSpinBox *>("spinBox_4"); // professions
    spinBox5 = findChild<QSpinBox *>("spinBox_5"); // believe
    spinBox6 = findChild<QSpinBox *>("spinBox_6"); // amount

    spinBox->setValue(0);
    spinBox2->setValue(0);
    spinBox3->setValue(0);
    spinBox4->setValue(0);
    spinBox5->setValue(0);
    spinBox6->setValue(0);

    spinBox->setMaximum(1000000000);
    spinBox2->setMaximum(1000000000);
    spinBox3->setMaximum(1000000000);
    spinBox4->setMaximum(1000000000);
    spinBox5->setMaximum(1000000000);
    spinBox6->setMaximum(1000000000);
    //spinBox8->setMaximum(1000000000);
    //spinBox9->setMaximum(1000000000);

    button = findChild<QPushButton *>("pushButton");

    // Display human interface:
    lcdNumber = findChild<QLCDNumber *>("lcdNumber_2");
    Qlabel = findChild<QLabel *>("label_8"); // name to display
    Qlabel2 = findChild<QLabel *>("label_9"); // lastname to display
    Qlabel3 = findChild<QLabel *>("label_11"); // belief to display
    Qlabel4 = findChild<QLabel *>("label_13"); // profession to display
    Qlabel5 = findChild<QLabel *>("label_16"); // birthday
    Qlabel6 = findChild<QLabel *>("label_17"); // sins
    Qlabel7 = findChild<QLabel *>("label_20"); // friends
    Qlabel8 = findChild<QLabel *>("label_21"); // reincarnations
    Qlabel9 = findChild<QLabel *>("label_24"); // status


    // Angels
    button2 = findChild<QPushButton *>("pushButton_6");
    textEdit = findChild<QTextEdit *>("textEdit_2");
    spinBox8 = findChild<QSpinBox *>("spinBox_8");
    spinBox8->setMaximum(1000000000);

    button3 = findChild<QPushButton *>("pushButton_7");
    button4 = findChild<QPushButton *>("pushButton_8");
    button5 = findChild<QPushButton *>("pushButton_5");

    // dead
    button6 = findChild<QPushButton *>("pushButton_2");
    spinBox7 = findChild<QSpinBox *>("spinBox_7");
    button7 = findChild<QPushButton *>("pushButton_3");
    spinBox9 = findChild<QSpinBox *>("spinBox_9");
    button8 = findChild<QPushButton *>("pushButton_4");
    spinBox9->setMaximum(10000000);
    // global counter
    lcdNumber2 = findChild<QLCDNumber *>("lcdNumber");

    // Label for rankings
    Qlabel10 = findChild<QLabel *>("label_25");

    button9 = findChild<QPushButton *>("pushButton_9");

    Qlabel11 = findChild<QLabel *>("label_28");
    spinBox10 = findChild<QSpinBox *>("spinBox_10");
    spinBox10->setMaximum(7);
    spinBox11 = findChild<QSpinBox *>("spinBox_11");


    spinBox11->setMaximum(100);
    qDebug() << humanity->length;
    startF1();
    startF2();
}

void Worker::process(int duration) {
    qDebug() << "Worker comenzando proceso en segundo plano";
    QThread::sleep(duration);
    emit finished();
}


MainWindow::~MainWindow()
{

    if (function1){
        function1->quit();
        function1->wait();
    }

    if (function2){
        function2->quit();
        function2->wait();
    }

    delete worker1;
    delete worker2;

    delete ui;
}


void displayHuman(Person *p){

    lcdNumber->display(p->id);
    Qlabel->setText(QString(p->firstName));
    Qlabel2->setText(p->lastName);
    Qlabel3->setText(p->belief);
    Qlabel4->setText(p->profession);
    Qlabel5->setText(p->birthDate);


    QString text;
    for (int i = 0; i < 7; i++) {
        text += QString::number(p->sins[i]);
        if (i < 6) {
            text += "-";
        }
    }

    Qlabel6->setText(text);
    Qlabel7->setText(QString::number(p->myFriends.size()));
    Qlabel8->setText(QString::number(p->reincarnations.size()));
    Qlabel9->setText(p->condition ? "Vivo" : "Muerto");

}



void MainWindow::startF1(){
    Worker *worker1 = new Worker();
    function1 = new QThread(this);
    worker1->moveToThread(function1);

    connect(function1, &QThread::started, [=]() {
        worker1->process(0);
    });

    connect(worker1, &Worker::finished, this, [=](){

        connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){
            amountNames = value;
        });


        connect(spinBox2, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){
            amountLastnames = value;
        });


        connect(spinBox3, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){
            amountCountries = value;
        });


        connect(spinBox4, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){
            amountProfessions = value;
        });


        connect(spinBox5, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){
            amountBelives = value;
        });

        connect(spinBox6, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){
            amountToCreate = value;
        });

        connect(button, &QPushButton::clicked, [=](){
            if (amountNames && amountLastnames && amountProfessions && amountBelives && amountCountries && amountToCreate){

                for (int i = 0; i<amountToCreate; i++){
                    Person * p = humanity->createPerson(amountNames,amountLastnames,amountCountries,amountProfessions,amountBelives);
                    world->add(p);
                    QTimer::singleShot(500, this, [=]() {});
                    lcdNumber->display(p->id);
                    displayHuman(p);
                }

                spinBox->setValue(0);
                spinBox2->setValue(0);
                spinBox3->setValue(0);
                spinBox4->setValue(0);
                spinBox5->setValue(0);
                spinBox6->setValue(0);

                amountNames = 0;
                amountLastnames = 0;
                amountProfessions = 0;
                amountBelives = 0;
                amountCountries = 0;
                amountToCreate = 0;

                humanity->humansSin();
                lcdNumber2->display(humanity->length);

                world->length = humanity->length;
            }

            qDebug() << humanity->length;
        });

    });

    function1->start();

}

void addTreeNodeToWidget(TreeNode* node, QTreeWidgetItem* parentItem, QSet<TreeNode*>& visitedNodes) {
    if (node == nullptr) return; // Evita nodos nulos
    if (visitedNodes.contains(node)) return; // Verifica si ya ha sido visitado

    // Añadir el nodo al conjunto de nodos visitados
    visitedNodes.insert(node);

    // Crear un nuevo elemento en el árbol de widgets
    QTreeWidgetItem* item = new QTreeWidgetItem(parentItem);
    item->setText(0, QString::number(node->person->id));

    // Llamada recursiva para los hijos
    if (node->left != nullptr) {
        addTreeNodeToWidget(node->left, item, visitedNodes);
    }
    if (node->right != nullptr) {
        addTreeNodeToWidget(node->right, item, visitedNodes);
    }
}


void printTree(TreeNode* node) {
    if (node == nullptr) return;
    qDebug() << "Node ID:" << node->person->id;
    printTree(node->left);
    printTree(node->right);
}

void addAngelToWidget(Angel* node, QTreeWidgetItem* parentItem) {
    if (!node) return;

    // Crea el ítem en el widget para el ángel actual
    QTreeWidgetItem* item = new QTreeWidgetItem(parentItem);
    item->setText(0, node->name);  // Asigna el nombre del ángel
    item->setData(0, Qt::UserRole, QVariant::fromValue(reinterpret_cast<quintptr>(node)));

    // Llama recursivamente a los hijos si existen
    if (node->firstChild) addAngelToWidget(node->firstChild, item);
    if (node->secondChild) addAngelToWidget(node->secondChild, item);
    if (node->thirdChild) addAngelToWidget(node->thirdChild, item);
}



void MainWindow::startF2(){
    Worker *worker2 = new Worker();
    function2 = new QThread(this);
    worker1->moveToThread(function2);

    connect(function2, &QThread::started, [=]() {
        worker2->process(0);
    });

    connect(worker2, &Worker::finished, this, [=](){

        // Angels

        connect(spinBox8, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){
            idSearch = value;
        });

        connect(button2, &QPushButton::clicked, [=](){
            Person* person = humanity->find(idSearch, humanity->firstPerson, 1);

            if (person->id == idSearch){
                qDebug() << "Founded";
                displayHuman(person);
            }

        });

        connect(button3, &QPushButton::clicked, [=](){
            QVector<QString> topCountries = humanity->getTopSinCountries(10);
            QString displayText = topCountries.join("\n");
            Qlabel10->setText(displayText);
            Qlabel10->setAlignment(Qt::AlignLeft | Qt::AlignTop);
            qDebug() << displayText;
        });

        connect(button4, &QPushButton::clicked, [=]() {
            // Llama a generateLevel() para asegurarse de que el árbol esté actualizado
            heaven->generateLevel();

            // Limpia el widget y verifica si está vacío
            treeWidget2->clear();

            // Verifica si la raíz está definida antes de continuar
            Angel* rootAngel = heaven->root;
            if (!rootAngel) {
                qWarning() << "Error: El árbol de ángeles no tiene una raíz definida.";
                return;
            }

            // Crea el nodo raíz en treeWidget2
            QTreeWidgetItem* rootItem = new QTreeWidgetItem(treeWidget2);
            rootItem->setText(0, "Root Node");
            rootItem->setData(0, Qt::UserRole, QVariant::fromValue(reinterpret_cast<quintptr>(rootAngel)));

            // Dibuja el árbol completo desde la raíz
            addAngelToWidget(rootAngel, rootItem);

            world->length = humanity->length;
            lcdNumber2->display(humanity->length);
        });


        connect(button5, &QPushButton::clicked, [=]() {
            treeWidget->clear();
            TreeNode* root = world->generate();
            printTree(root);
            if (root != nullptr) {
                QTreeWidgetItem* rootItem = new QTreeWidgetItem(treeWidget);
                rootItem->setText(0, "ID: " + QString::number(root->person->id));
                treeWidget->addTopLevelItem(rootItem);

                // Crear un conjunto para los nodos visitados
                QSet<TreeNode*> visitedNodes;
                addTreeNodeToWidget(root->left, rootItem, visitedNodes);
                addTreeNodeToWidget(root->right, rootItem, visitedNodes);
            }
            treeWidget->expandAll();
        });

        connect(spinBox11, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){
            probRandom = value;
        });

        connect(button6, &QPushButton::clicked, [=](){
            QVector <Person*> people = humanity->killRandom(probRandom);
            lcdNumber2->display(humanity->length);

            for (Person * p: people){
                qDebug()<<".";
                world->remove(p->id);
                graveyard->add(p);
            }

            // It need to be added to graveyard?
        });

        connect(spinBox7, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){
            levelOfHeap = value;
        });

        connect(spinBox9, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){
            idToRemove = value;
        });

        connect(spinBox10, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){
            sinType = value;
        });

        connect(button7, &QPushButton::clicked, [=](){
            QVector <Person*> people;

            switch(sinType) {
            case 0:
                people = humanity->killByHeap(levelOfHeap, LUST);
                break;
            case 1:
                people = humanity->killByHeap(levelOfHeap, GLUTTONY);
                break;
            case 2:
                people = humanity->killByHeap(levelOfHeap, GREED);
                break;
            case 3:
                people = humanity->killByHeap(levelOfHeap, SLOTH);
                break;
            case 4:
                people = humanity->killByHeap(levelOfHeap, WRATH);
                break;
            case 5:
                people = humanity->killByHeap(levelOfHeap, ENVY);
                break;
            case 6:
                people = humanity->killByHeap(levelOfHeap, PRIDE);
                break;
            case 7:
                people = humanity->killByHeap(levelOfHeap, ALL);
                break;
            default:

                return LUST;  // Valor por defecto si el número no es válido
            }

            for (Person * p: people){
                world->remove(p->id);
                graveyard->add(p);
            }

            spinBox7->setValue(0);
            spinBox10->setValue(0);

            lcdNumber2->display(humanity->length);
            world->length = humanity->length;
        });

        connect(button8, &QPushButton::clicked, [=](){
            Person* people = humanity->killSpecific(idToRemove);
            graveyard->add(people);
            world->remove(people->id);

            spinBox9->setValue(0);
            lcdNumber2->display(humanity->length);
            world->length = humanity->length;
        });

        connect(button9, &QPushButton::clicked, [=](){
            humanity->makeFriends();
        });

    });

    function2->start();
}


