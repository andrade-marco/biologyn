#include "Flora.h"
#include <iostream>

Flora::Flora(std::string id, Environment &env, float decay_rate): Living(id, env, decay_rate) {};