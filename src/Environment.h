#ifndef BIOLOGYN_ENVIRONMENT_H
#define BIOLOGYN_ENVIRONMENT_H

#include <vector>
#include <memory>
#include "Flora.h"
#include "Fauna.h"

class Fauna;
class Flora;

class Environment {
public:
    Environment(unsigned int xBound, unsigned int yBound);
    std::vector<unsigned int> getDimensions();
private:
    unsigned int _xBound;
    unsigned int _yBound;
    unsigned int _age {0};
    std::vector<std::unique_ptr<Flora>> _flora;
    std::vector<std::unique_ptr<Fauna>> _fauna;
};


#endif //BIOLOGYN_ENVIRONMENT_H
