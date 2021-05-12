#include <random>
#include "Living.h"

constexpr int AXIS_ORIGIN = 0;

Living::Living(Environment& env, float decay_rate) : _env{env}, _decay_rate{decay_rate} {
    this->setInitialPosition();
};

void Living::setInitialPosition() {
    auto dimension = this->_env.getDimensions();

    // Adapted from https://stackoverflow.com/a/12658061/8190058
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<int> xDist(AXIS_ORIGIN, dimension[0]);
    std::uniform_int_distribution<int> yDist(AXIS_ORIGIN, dimension[1]);

    this->_x = xDist(engine);
    this->_y = yDist(engine);
}
