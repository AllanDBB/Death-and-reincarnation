#include "../../src/headers/angel.h"

Angel::Angel(QString _name, int _version, int _generation, Person * _saved ){
    name = _name;
    version = _version;
    generation = _generation;
    saved = _saved;
    firstChild = nullptr;
    secondChild = nullptr;
    thirdChild = nullptr;
}

