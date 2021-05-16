#ifndef BIOLOGYN_FAUNA_H
#define BIOLOGYN_FAUNA_H

#include "Living.h"

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
    Fauna(std::string id, Environment &env, NutritionType type, Gender gender, float decay_rate, float fertility);
    NutritionType getType();
    Gender getGender();
    void move();
private:
    NutritionType _type;
    Gender _gender;
    float _fertility;
    float _attack_accuracy;

    void setLocation(unsigned int x, unsigned int y);
};


#endif //BIOLOGYN_FAUNA_H
