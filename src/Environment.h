#ifndef BIOLOGYN_ENVIRONMENT_H
#define BIOLOGYN_ENVIRONMENT_H

#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include "Flora.h"
#include "Fauna.h"

class Fauna;
class Flora;

class Environment {
public:
    static constexpr unsigned int MAX_DIMENSION {1000};

    Environment(unsigned int xBound, unsigned int yBound);
    std::vector<unsigned int> getDimensions();

    static bool validateJsonEnvironment(nlohmann::json& parsed);
    static std::map<std::string, int> transformJsonEnvironment(nlohmann::json& parsed);

    void addFlora(std::unique_ptr<Flora> flora);
    void addFauna(std::unique_ptr<Fauna> fauna);
private:
    unsigned int _xBound;
    unsigned int _yBound;
    unsigned int _age {0};
    std::vector<std::unique_ptr<Flora>> _flora;
    std::vector<std::unique_ptr<Fauna>> _fauna;
};


#endif //BIOLOGYN_ENVIRONMENT_H
