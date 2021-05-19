//
// Created by Marco Andrade on 2021-04-12.
//

#ifndef BIOLOGYN_FLORA_H
#define BIOLOGYN_FLORA_H

#include <string>
#include "Living.h"

class Environment;

class Flora: public Living {
public:
    Flora(std::string id, Environment &env, float decay_rate);
    unsigned int transferHealth(int value);
};


#endif //BIOLOGYN_FLORA_H
