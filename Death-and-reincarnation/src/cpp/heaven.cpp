#include "../../src/headers/heaven.h"
void Heaven:: backTozero(){

    miguelVersion = 0;
    nurielVersion = 0;
    anielVersion = 0;
    rafaelVersion = 0;
    gabrielVersion = 0;
    shamsielVersion = 0;
    raguelVersion = 0;
    urielVersion = 0;
    azraelVersion = 0;
    sarielVersion = 0;
}


Heaven :: Heaven (){
    root = new Angel("GOD", 1, 0, nullptr);
    root->firstChild = new Angel("Serafines", 1, 1, nullptr);
    root->secondChild = new Angel("Querubines", 1, 1, nullptr);
    root->thirdChild = new Angel("Tronos", 1, 1, nullptr);

    root->firstChild->firstChild = new Angel("Angel", 1, 2, nullptr);
    root->firstChild->secondChild = new Angel("Angel", 2, 2, nullptr);
    root->firstChild->thirdChild = new Angel("Angel", 3, 2, nullptr);

    root->secondChild->firstChild = new Angel("Angel", 4, 2, nullptr);
    root->secondChild->secondChild = new Angel("Angel", 5, 2, nullptr);
    root->secondChild->thirdChild = new Angel("Angel", 6, 2, nullptr);

    root->thirdChild->firstChild = new Angel("Angel", 7, 2, nullptr);
    root->thirdChild->secondChild = new Angel("Angel", 8, 2, nullptr);
    root->thirdChild->thirdChild = new Angel("Angel", 9, 2, nullptr);

    generation = 3;
    backTozero();
}

void Heaven::generateLevel(){
    Angel * temp = root;
    //todo



}
