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
    Environment();
    Environment(nlohmann::json parsedJson);
    unsigned int operator[] (std::string);

    std::vector<unsigned int> getDimensions();

    unsigned int getFloraTotal();
    unsigned int getFloraDecayRate();

    unsigned int getFaunaTotal(NutritionType type, Gender gender);
    unsigned int getFaunaDecayRate(NutritionType type, Gender gender);
    unsigned int getFaunaMinAttackRate(NutritionType type, Gender gender);
    unsigned int getFaunaMinDefendRate(NutritionType type, Gender gender);

    void addFlora(std::unique_ptr<Flora> flora);
    void addFauna(std::unique_ptr<Fauna> fauna);

    void simulate();
    void report();
private:
    nlohmann::json _configuration {};
    unsigned int _age {0};
    std::unique_ptr<Fauna> _lastFauna {};
    std::vector<std::unique_ptr<Flora>> _flora;
    std::vector<std::unique_ptr<Fauna>> _fauna;

    unsigned int getFaunaIntegerConfig(NutritionType type, Gender gender, std::string key) const;
    unsigned int getFloraIntegerConfig(std::string key) const;

    void incrementAge();
    void faunaCleanup();
};


#endif //BIOLOGYN_ENVIRONMENT_H
