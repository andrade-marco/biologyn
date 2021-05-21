#ifndef BIOLOGYN_FAUNA_H
#define BIOLOGYN_FAUNA_H

#include "Living.h"
#include "Flora.h"

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
    Fauna(std::string id, Environment &env, NutritionType type, Gender gender);
    NutritionType getType();
    Gender getGender();

    void move();
    void scan();
    void graze(Flora& flora);
    void battle(Fauna& opponent);
    void mate(Fauna& partner);
private:
    NutritionType _type;
    Gender _gender;
    unsigned int _min_attack_rate;
    unsigned int _min_defend_rate;

    void setLocation(unsigned int x, unsigned int y);
    void searchFlora();
    void searchFauna();
    unsigned int attack();
    unsigned int defend();
};


#endif //BIOLOGYN_FAUNA_H
