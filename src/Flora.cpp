#include "Flora.h"
#include <algorithm>

Flora::Flora(std::string id, Environment &env, float decay_rate): Living(id, env, decay_rate) {};

unsigned int Flora::transferHealth(int value) {
    unsigned int health = std::min(value, this->getHealth());
    this->setHealth(this->getHealth() - health);

    return health;
};
