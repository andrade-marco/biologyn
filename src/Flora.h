//
// Created by Marco Andrade on 2021-04-12.
//

#ifndef BIOLOGYN_FLORA_H
#define BIOLOGYN_FLORA_H

#include "Living.h"

class Environment;

class Flora: public Living {
public:
    Flora(Environment &env, float decay_rate);
};


#endif //BIOLOGYN_FLORA_H
