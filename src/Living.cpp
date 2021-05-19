#include "Living.h"
#include "Chaos.h"
#include "Environment.h"

constexpr int AXIS_ORIGIN = 0;

Living::Living(std::string id, Environment& env, unsigned int decay_rate) :
    _id{id}, _env{env}, _decay_rate{decay_rate} {
        this->setInitialPosition();
};

const std::string Living::getId() {
    return this->_id;
}

std::vector<unsigned int> Living::getCurrentLocation() {
    return std::vector<unsigned int> {this->_x, this->_y};
}

const int Living::getHealth() {
    return this->_health;
}

void Living::decay() {
    this->setHealth(this->getHealth() - this->_decay_rate);
}

void Living::setHealth(int health) {
    this->_health = health;
}

void Living::setInitialPosition() {
    auto dimension = this->_env.getDimensions();
    this->_x = Chaos::random_integer(AXIS_ORIGIN, dimension[0]);
    this->_y = Chaos::random_integer(AXIS_ORIGIN, dimension[1]);
}
