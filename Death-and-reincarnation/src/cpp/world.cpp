#include "../../src/headers/world.h"
#include <QDebug>
#include <QRandomGenerator>




World::World(Humanity* _humanity, Graveyard* _graveyard){
    humanity = _humanity;
    graveyard = _graveyard;
    length = humanity->length;
}

void insertIntoTree(TreeNode*& node, Person* person) {
    if (node == nullptr) {
        node = new TreeNode(person);
    } else if (person->id < node->person->id) {
        insertIntoTree(node->left, person);
    } else {
        insertIntoTree(node->right, person);
    }
}

TreeNode* World::generate() {
    int nodes = length / 100;
    int completeTreeNodes = 1;


    while (completeTreeNodes < nodes) {
        completeTreeNodes = (completeTreeNodes << 1) + 1;
    }

    QSet<int> selectedIndices;
    QVector<Person*> treeNodes;

    while (selectedIndices.size() < completeTreeNodes) {
        int randomIndex = QRandomGenerator::global()->bounded(length);
        if (!selectedIndices.contains(randomIndex)) {
            selectedIndices.insert(randomIndex);

            Person* temp = humanity->firstPerson;
            for (int i = 0; i < randomIndex; ++i) {
                temp = temp->rightPerson;
            }
            treeNodes.append(temp);
        }
    }


    TreeNode* root = nullptr;
    for (Person* person : treeNodes) {
        insertIntoTree(root, person);
    }

    return root;
}

Person* World::search(int id) { //idealmente el buscado pero sino el mas cercano

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

void World::add(Person * person){
    Person * p = search(person->id);
    bool dir = 0;
    if (person->id>p->id){
        dir = 1;
    }

    humanity->add(person, p, dir);
}

Person* World::remove(int id){
    Person * p = search(id);
    bool dir = 0;
    if (id>p->id){
        dir = 1;
    }

    Person * removed = humanity->remove(id,p,dir);
    return removed;
}






