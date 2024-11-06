#include "humanity.h"
#include "graveyard.h"

#ifndef WORLD_H
#define WORLD_H

struct TreeNode {
    Person* person;
    TreeNode* left;
    TreeNode* right;


    TreeNode(Person* p) : person(p), left(nullptr), right(nullptr) {}
};

struct World{

    Humanity* humanity;
    Graveyard* graveyard;
    int length;

    World(Humanity*, Graveyard*);
    TreeNode * generate();
    Person* search(int id);
    int getFreeId(); //todo
    void add(Person*);
    Person* remove(int id);
    TreeNode* buildBalancedTree(const QVector<Person*>&, int, int);

};
#endif // WORLD_H
