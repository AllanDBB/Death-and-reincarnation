#include "../../src/headers/world.h"
#include <QDebug>
#include <QRandomGenerator>




World::World(Humanity* _humanity, Graveyard* _graveyard){
    humanity = _humanity;
    graveyard = _graveyard;
    length = humanity->length;
}

TreeNode* World::buildBalancedTree(const QVector<Person*>& personList, int start, int end) {
    if (start > end) {
        return nullptr;
    }

    // Encuentra el elemento del medio para balancear el árbol
    int mid = start + (end - start) / 2;
    TreeNode* node = new TreeNode(personList[mid]);

    // Construye recursivamente los subárboles izquierdo y derecho
    node->left = buildBalancedTree(personList, start, mid - 1);
    node->right = buildBalancedTree(personList, mid + 1, end);

    return node;
}

TreeNode* World::generate() {
    int totalPersons = length;  // Asumiendo que 'length' representa la cantidad total en 'humanity'
    int nodesToSelect = std::max(1, totalPersons / 100);  // 1% de la humanidad o al menos 1 nodo

    // Convierte la lista ordenada `humanity` en un QVector de nodos seleccionados
    QVector<Person*> selectedPersons;
    Person* current = humanity->firstPerson;
    int step = totalPersons / nodesToSelect;  // Salto entre personas para obtener una muestra del 1%

    for (int i = 0; i < nodesToSelect && current != nullptr; ++i) {
        selectedPersons.append(current);

        // Avanza `step` personas en la lista
        for (int j = 0; j < step && current != nullptr; ++j) {
            current = current->rightPerson;
        }
    }

    // Construye el árbol balanceado a partir del vector seleccionado
    return buildBalancedTree(selectedPersons, 0, selectedPersons.size() - 1);
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

void World::add(Person* person) {
    Person* p = search(person->id);


    // Si `p` es nullptr, significa que el árbol está vacío o que el nodo no se pudo encontrar.
    // En este caso, deberíamos insertar `person` en la raíz.
    if (p == nullptr) {
        qDebug()<< "null";
        humanity->add(person, nullptr, 0);  // Aquí `nullptr` significa que es la raíz

        return;
    }
    qDebug()<< p->firstName;
    // Calcula la dirección dependiendo de la comparación entre `person->id` y `p->id`
    bool dir = (person->id > p->id) ? 1 : 0;

    humanity->add(person, p, dir);
}


Person* World::remove(int id){
    Person * p = search(id);
    Person * removed = nullptr;

    if (p==nullptr){return nullptr;}

    bool dir = (id > p->id) ? 1 : 0;
    if(p->id == id){
        removed = humanity->remove(id,p,dir);}


    return removed;
}






