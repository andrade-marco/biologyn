#include "Chaos.h"

int Chaos::random_integer(int min, int max) {
    std::random_device seeder;
    std::mt19937 engine(seeder());

    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
};