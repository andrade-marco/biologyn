#include <algorithm>
#include "Fauna.h"
#include "Chaos.h"
#include "Environment.h"

constexpr int AXIS_ORIGIN = 0;
constexpr int MAX_RATE = 100;

Fauna::Fauna(std::string id, Environment &env, NutritionType type, Gender gender) :
    Living(id, env, env.getFaunaDecayRate(type, gender)),
    _type{type},
    _gender{gender},
    _min_attack_rate{env.getFaunaMinAttackRate(type, gender)},
    _min_defend_rate{env.getFaunaMinDefendRate(type, gender)} {};

void Fauna::setLocation(unsigned int x, unsigned int y) {
    this->_x = x;
    this->_y = y;
}

NutritionType Fauna::getType() {
    return this->_type;
}

Gender Fauna::getGender() {
    return this->_gender;
}

int getNewPosition(int current, int limit) {
    int newPos {current + Chaos::random_integer(-1, 1)};
    if (current == limit) {
        return std::min(current, newPos);
    }

    if (current == AXIS_ORIGIN) {
        return std::max(current, newPos);
    }

    return newPos;
}

void Fauna::move() {
     auto envLimits {this->_env.getDimensions()};
     auto currentLocation {this->getCurrentLocation()};

     unsigned int newX = getNewPosition(currentLocation[0], envLimits[0]);
     unsigned int newY = getNewPosition(currentLocation[1], envLimits[1]);

     this->setLocation(newX, newY);
}

void Fauna::graze(Flora& flora) {
    if (this->getType() == NutritionType::herbivore) {
        auto healthGap = Living::MAX_HEALTH - this->getHealth();
        this->setHealth(flora.transferHealth(healthGap));
    }
};

unsigned int Fauna::attack() {
    return Chaos::random_integer(this->_min_attack_rate, MAX_RATE);
};

unsigned int Fauna::defend() {
    return Chaos::random_integer(this->_min_defend_rate, MAX_RATE);
};

bool Fauna::attack_success(Fauna& opponent) {
    return this->attack() > opponent.defend();
}