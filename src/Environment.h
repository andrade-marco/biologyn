#ifndef BIOLOGYN_ENVIRONMENT_H
#define BIOLOGYN_ENVIRONMENT_H

#include <vector>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include "Chaos.h"
#include "Flora.h"
#include "Fauna.h"

class Fauna;
class Flora;


class Environment {
public:
    static constexpr unsigned int MAX_DIMENSION {1000};
    Environment();
    Environment(nlohmann::json parsedJson);

    std::vector<unsigned int> getDimensions();

    unsigned int getFloraTotal();
    unsigned int getFloraDecayRate();

    unsigned int getFaunaTotal(NutritionType type, Gender gender);
    unsigned int getFaunaDecayRate(NutritionType type, Gender gender);
    unsigned int getFaunaMinAttackRate(NutritionType type, Gender gender);
    unsigned int getFaunaMinDefendRate(NutritionType type, Gender gender);

    const std::vector<std::unique_ptr<Flora>>& getFlora();
    const std::vector<std::unique_ptr<Fauna>>& getFauna();

    void addFlora(std::unique_ptr<Flora> flora);
    void addFauna(std::unique_ptr<Fauna> fauna);

    void simulate();
    void report();
private:
    nlohmann::json _configuration {};
    unsigned int _age {0};
    std::unique_ptr<Fauna> _lastFauna {};
    std::unique_ptr<Flora> _lastFlora {};
    std::vector<std::unique_ptr<Flora>> _flora;
    std::vector<std::unique_ptr<Fauna>> _fauna;

    unsigned int getFaunaIntegerConfig(NutritionType type, Gender gender, std::string key) const;
    unsigned int getFloraIntegerConfig(std::string key) const;

    void incrementAge();
    void faunaCleanup();
    void floraCleanup();

    template<typename T>
    void cleanUp(std::vector<std::unique_ptr<T>>& individuals, std::unique_ptr<T>& target, std::string message) {
        if (!individuals.empty()) {
            for (auto& i : individuals) {
                i->decay();
            }

            bool allDead = std::all_of(individuals.begin(), individuals.end(), [](auto& i) {
                return i->getHealth() == 0;
            });

            if (allDead) {
                auto index = Chaos::random_integer(0, individuals.size() - 1);
                target = std::move(individuals[index]);
                individuals.clear();
                std::cout << message << std::endl;
            } else {
                individuals.erase(std::remove_if(individuals.begin(), individuals.end(), [](auto& i) {
                    return (*i).getHealth() == 0;
                }), individuals.end());
            }
        }
    }
};


#endif //BIOLOGYN_ENVIRONMENT_H
