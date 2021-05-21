#include <algorithm>
#include "Living.h"
#include "Chaos.h"
#include "Environment.h"

constexpr int AXIS_ORIGIN = 0;

Living::Living(std::string id, Environment& env, unsigned int max_decay_rate) : _id{id}, _env{env} {
    this->_decay_rate = Chaos::random_integer(1, max_decay_rate);
    this->setInitialPosition();
};

std::string Living::getId() {
    return this->_id;
}

unsigned int Living::getAge() {
    return this->_age;
}

std::vector<unsigned int> Living::getCurrentLocation() {
    return std::vector<unsigned int> {this->_x, this->_y};
}

unsigned int Living::getHealth() {
    return this->_health;
}

void Living::decay() {
    if (this->_health <= this->_decay_rate) {
        this->setHealth(0);
    } else {
        this->setHealth(this->_health - this->_decay_rate);
    }

    this->_age++;
}

void Living::transferHealth(Living& predator) {
    unsigned int health = std::min(Living::MAX_HEALTH - predator.getHealth(), this->getHealth());
    this->setHealth(this->getHealth() - health);
    predator.setHealth(predator.getHealth() + health);
};

void Living::incrementAge() {
    this->_age++;
}

void Living::setHealth(int health) {
    this->_health = health;
}

void Living::setInitialPosition() {
    auto dimension = this->_env.getDimensions();
    this->_x = Chaos::random_integer(AXIS_ORIGIN, dimension[0]);
    this->_y = Chaos::random_integer(AXIS_ORIGIN, dimension[1]);
}
