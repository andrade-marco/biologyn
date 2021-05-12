#ifndef BIOLOGYN_FAUNA_H
#define BIOLOGYN_FAUNA_H

#include "Living.h"
#include "Environment.h"

class Environment;

enum NutritionType {
    herbivore,
    carnivore
};

enum Gender {
    male,
    female
};

class Fauna: public Living {
public:
    Fauna(float decay_rate, Environment &env, NutritionType type, Gender gender, float reproduction_prob);
private:
    Environment &_env;
    NutritionType _type;
    Gender _gender;
    float _reproduction_prob;
    float _attack_success_rate;

    void move();
};


#endif //BIOLOGYN_FAUNA_H
