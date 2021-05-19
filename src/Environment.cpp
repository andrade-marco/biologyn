#include <algorithm>
#include <nlohmann/json.hpp>
#include <iostream>
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

void Environment::simulate() {
    int count {0};
    while (count < 1000) {
        for (auto& currIndividual:this->_fauna) {
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

            if (*foundIndividual) {
                // this->_fauna.erase(std::remove(this->_fauna.begin(), this->_fauna.end(), *foundIndividual));
                if (currIndividual->getType() == (*foundIndividual)->getType()) {

                }

                // If same type, then check gender
                //      If same gender, attack for territory
                //      else try to mate
                // else carnivore attacks herbivore
            }
        }

        count++;
    }
}