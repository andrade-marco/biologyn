#include <algorithm>
#include "Fauna.h"
#include "Chaos.h"
#include "Environment.h"

constexpr int AXIS_ORIGIN = 0;

Fauna::Fauna(std::string id, Environment &env, NutritionType type, Gender gender, float decay_rate, float fertility)
    : Living(id, env, decay_rate), _type{type}, _gender{gender}, _fertility{fertility} {};

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