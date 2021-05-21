#include <iostream>
#include <algorithm>
#include <memory>
#include "Flora.h"
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

template <class S, class T>
void sendMessage(S& self, T& target, std::string message) {
    std::cout << self.getId() << message << target.getId() << std::endl;
}

void Fauna::move() {
     auto envLimits {this->_env.getDimensions()};
     auto currentLocation {this->getCurrentLocation()};

     unsigned int newX = getNewPosition(currentLocation[0], envLimits[0]);
     unsigned int newY = getNewPosition(currentLocation[1], envLimits[1]);

     this->setLocation(newX, newY);
}

void Fauna::scan() {
    if (this->getType() == NutritionType::herbivore) {
        this->searchFlora();
    }

    this->searchFauna();
};

void Fauna::graze(Flora& flora) {
    if (this->getType() == NutritionType::herbivore) {
        flora.transferHealth(*this);
        std::cout << this->getId() << " grazed on " << flora.getId() << std::endl;
    }
};

void Fauna::searchFlora() {
    const auto currentPos = this->getCurrentLocation();
    auto& flora = this->_env.getFlora();
    if (this->getType() == NutritionType::herbivore && !flora.empty()) {
        auto foundFlora = std::find_if(flora.begin(), flora.end(), [&currentPos](auto& entry) {
                    auto entryPos = entry->getCurrentLocation();
                    return std::equal(currentPos.begin(), currentPos.end(), entryPos.begin());
                }
        );

        if (foundFlora != flora.end()) {
            this->graze(**foundFlora);
        }
    }
};

void Fauna::searchFauna() {
    const auto currentPos = this->getCurrentLocation();
    const auto id = this->getId();
    auto& fauna = this->_env.getFauna();
    auto foundIndividual = std::find_if(fauna.begin(), fauna.end(), [&id, &currentPos](auto& entry) {
                auto entryPos = entry->getCurrentLocation();
                bool samePos = std::equal(currentPos.begin(), currentPos.end(), entryPos.begin());
                return id != entry->getId() && samePos;
            });

    if (foundIndividual != fauna.end()) {
        auto type = this->getType();
        auto gender = this->getGender();
        if (type == (*foundIndividual)->getType()) {
            if (gender == (*foundIndividual)->getGender()) {
                this->battle(**foundIndividual);
            } else {
                this->mate(**foundIndividual);
            }
        } else {
            if (type == NutritionType::carnivore) {
                this->battle(**foundIndividual);
            } else {
                this->move(); // run away
                sendMessage(*this, **foundIndividual, " ran from ");
            }
        }
    }
};

unsigned int Fauna::attack() {
    return Chaos::random_integer(this->_min_attack_rate, MAX_RATE);
};

unsigned int Fauna::defend() {
    return Chaos::random_integer(this->_min_defend_rate, MAX_RATE);
};

void Fauna::battle(Fauna& opponent) {
    if (this->attack() > opponent.defend()) {
        std::string action {" killed [territorial] "};

        // No cannibalism rule
        if (this->getType() != opponent.getType()) {
            opponent.transferHealth(*this);
            action = " killed [eating] ";
        }

        opponent.setHealth(0);
        sendMessage(*this, opponent, action);
    }
}

void Fauna::mate(Fauna& partner) {
    sendMessage(*this, partner, " mated with ");
};