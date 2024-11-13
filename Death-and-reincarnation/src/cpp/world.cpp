#include "../../src/headers/world.h"
#include <QDebug>
#include <QRandomGenerator>




World::World(Humanity* _humanity, Graveyard* _graveyard){
    humanity = _humanity;
    graveyard = _graveyard;
    length = humanity->length;
}

TreeNode* World::buildBalancedTree(const QVector<Person*>& selectedPersons, int start, int end) {
    if (start > end) {
        return nullptr;
    }

    int mid = start + (end - start) / 2;
    TreeNode* node = new TreeNode(selectedPersons[mid]);

    node->left = buildBalancedTree(selectedPersons, start, mid - 1);
    node->right = buildBalancedTree(selectedPersons, mid + 1, end);

    return node;
}

TreeNode* World::generate() {
    int totalPersons = length;
    int nodesToSelect = std::max(1, totalPersons / 100);

    QVector<Person*> selectedPersons;
    Person* current = humanity->firstPerson;
    int step = totalPersons / nodesToSelect;

    for (int i = 0; i < nodesToSelect && current != nullptr; ++i) {
        selectedPersons.append(current);

        for (int j = 0; j < step && current != nullptr; ++j) {
            current = current->rightPerson;
        }
    }

    return buildBalancedTree(selectedPersons, 0, selectedPersons.size() - 1);
}


Person* World::search(int id) {

    TreeNode* root = generate();
    TreeNode* currentNode = root;
    Person* closestPerson = nullptr;
    int closestDiff = std::numeric_limits<int>::max();

    while (currentNode != nullptr) {
        int currentDiff = std::abs(currentNode->person->id - id);


        if (currentDiff < closestDiff) {
            closestDiff = currentDiff;
            closestPerson = currentNode->person;
        }


        if (currentNode->person->id == id) {
            return currentNode->person;
        } else if (id < currentNode->person->id) {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }
    }

    return closestPerson;
}

void World::add(Person* person) {
    Person* p = search(person->id);

    if (p == nullptr) {
        qDebug()<< "null";
        humanity->add(person, nullptr, 0);

        return;
    }
    qDebug()<< p->firstName;
    bool dir = (person->id > p->id) ? 1 : 0;

    humanity->add(person, p, dir);
}


Person* World::remove(int id){
    Person * p = search(id);
    Person * removed = nullptr;

    if (p==nullptr){return nullptr;}

    bool dir = (id > p->id) ? 1 : 0;
    if(p->id == id){
        removed = humanity->remove(id,p,dir);
    }


    return removed;
}






