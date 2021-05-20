#include <algorithm>
#include <nlohmann/json.hpp>
#include <iostream>
#include "Chaos.h"
#include "Environment.h"

Environment::Environment() {};

Environment::Environment(nlohmann::json parsedJson): _configuration{parsedJson} {};

std::vector<unsigned int> Environment::getDimensions() {
    return this->_configuration["axesLimits"].get<std::vector<unsigned int>>();
}

unsigned int Environment::getFaunaIntegerConfig(NutritionType type, Gender gender, std::string key) const {
    std::string genderType = gender == Gender::male ? "male" : "female";
    std::string nutritionType = type == NutritionType::herbivore ? "herbivores" : "carnivores";

    return this->_configuration["faunaPopulation"][genderType][nutritionType][key].get<unsigned int>();
}

unsigned int Environment::getFloraIntegerConfig(std::string key) const {
    return this->_configuration["floraPopulation"][key].get<unsigned int>();
};

unsigned int Environment::getFloraTotal() {
    return this->getFloraIntegerConfig("total");
};

unsigned int Environment::getFloraDecayRate() {
    return this->getFloraIntegerConfig("decayRate");
};

unsigned int Environment::getFaunaTotal(NutritionType type, Gender gender) {
    return this->getFaunaIntegerConfig(type, gender, "total");
};

unsigned int Environment::getFaunaDecayRate(NutritionType type, Gender gender) {
    return this->getFaunaIntegerConfig(type, gender, "decayRate");
};

unsigned int Environment::getFaunaMinAttackRate(NutritionType type, Gender gender) {
    return this->getFaunaIntegerConfig(type, gender, "minAttackRate");
};

unsigned int Environment::getFaunaMinDefendRate(NutritionType type, Gender gender) {
    return this->getFaunaIntegerConfig(type, gender, "minDefendRate");
};

//std::map<std::string, unsigned int> Environment::transformJsonEnvironment(nlohmann::json &parsed) {
//    std::map<std::string, unsigned int> transformed {};
//    for (auto& el : parsed.items()) {
//        transformed[el.key()] = static_cast<unsigned int>(el.value());
//    }
//
//    return transformed;
//}

void Environment::addFlora(std::unique_ptr<Flora> flora) {
    this->_flora.emplace_back(std::move(flora));
}

void Environment::addFauna(std::unique_ptr<Fauna> fauna) {
    this->_fauna.emplace_back(std::move(fauna));
}

void Environment::incrementAge() {
    this->_age++;
};

void Environment::faunaCleanup() {
    bool allDead = std::all_of(this->_fauna.begin(),this->_fauna.end(), [](std::unique_ptr<Fauna>& element) {
        return element->getHealth() == 0;
    });

    if (allDead) {
        auto index = Chaos::random_integer(0, this->_fauna.size() - 1);
        this->_lastFauna = std::move(this->_fauna[index]);
        this->_fauna.clear();
        std::cout << "\nWARNING: All fauna extinct..." << std::endl;
    } else {
        this->_fauna.erase(
                std::remove_if(
                        this->_fauna.begin(),
                        this->_fauna.end(),
                        [this](std::unique_ptr<Fauna>& element) {
                            return (*element).getHealth() == 0;
                        }),
                this->_fauna.end()
        );
    }
}

void Environment::simulate() {
    while (!this->_fauna.empty()) {
        for (auto& currIndividual:this->_fauna) {
            if (currIndividual->getHealth() == 0) break;

            currIndividual->move();
            const auto id = currIndividual->getId();
            const auto currentPos = currIndividual->getCurrentLocation();
            auto foundIndividual = std::find_if(
                    this->_fauna.begin(),
                    this->_fauna.end(),
                    [&id, &currentPos](std::unique_ptr<Fauna>& entry) {
                        auto entryPos = entry->getCurrentLocation();
                        bool samePos = std::equal(currentPos.begin(), currentPos.end(), entryPos.begin());
                        return id != entry->getId() && samePos;
                    });

            if (foundIndividual != this->_fauna.end()) {
                if (currIndividual->getType() == (*foundIndividual)->getType()) {
                    if (currIndividual->getGender() == (*foundIndividual)->getGender()) {
                        currIndividual->battle(**foundIndividual);
                    } else {
                        currIndividual->mate(**foundIndividual);
                    }
                } else {
                    if (currIndividual->getType() == NutritionType::carnivore) {
                        currIndividual->battle(**foundIndividual);
                    } else {
                        currIndividual->move(); // run away
                        std::cout << currIndividual->getId()
                                  << " ran from "
                                  << (*foundIndividual)->getId()
                                  << std::endl;
                    }
                }
            }

            currIndividual->decay();
        }

        this->faunaCleanup();
        this->incrementAge();
    }
}

void Environment::report() {
    std::cout << "\n\n*** SUMMARY ***\n" << std::endl;

    std::cout << "Environment existed for " << this->_age + 1 << " days\n" << std::endl;

    auto lastFauna = this->_lastFauna.get();
    std::cout
        << "Last fauna: " << lastFauna->getId() << "\n"
        << "Age: " << lastFauna->getAge() << "\n"
        << "Type: " << lastFauna->getType() << "\n"
        << "Gender: " << lastFauna->getGender() << "\n\n";

    std::cout << "*** THE END OF TIME ***" << std::endl;

}