#ifndef MODEL_H_
#define MODEL_H_

#include "HashTable.h"
#include "Scene.h"

class Model
{
public:

private:
    HashTable<int, Scene> scenes;
};

#endif // MODEL_H_

