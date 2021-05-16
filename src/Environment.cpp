#include <algorithm>
#include <nlohmann/json.hpp>
#include <iostream>
#include "Environment.h"

Environment::Environment() {};

Environment::Environment(nlohmann::json parsedJson): _configuration{parsedJson} {};

std::vector<unsigned int> Environment::getDimensions() {
    return this->_configuration["axesLimits"].get<std::vector<unsigned int>>();
}

nlohmann::json Environment::getFaunaConfigByTypes(NutritionType type, Gender gender) const {
    std::string genderType = gender == Gender::male ? "male" : "female";
    std::string nutritionType = type == NutritionType::herbivore ? "herbivores" : "carnivores";

    return this->_configuration["faunaPopulation"][genderType][nutritionType];
}

unsigned int Environment::getFloraTotal() {
    return this->_configuration["floraPopulation"]["total"].get<unsigned int>();
};

float Environment::getFloraDecayRate() {
    return this->_configuration["floraPopulation"]["decayRate"].get<unsigned int>() / 100;
};

unsigned int Environment::getFaunaTotal(NutritionType type, Gender gender) {
    return this->getFaunaConfigByTypes(type, gender)["total"].get<unsigned int>();
};

float Environment::getFaunaDecayRate(NutritionType type, Gender gender) {
    return this->getFaunaConfigByTypes(type, gender)["decayRate"].get<unsigned int>() / 100;
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
    int encounters {0};
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
                    }
            );

            if (*foundIndividual) {
//                this->_fauna.erase(this->_fauna.begin(), it);
                std::cout << currIndividual->getType() << " " << (*foundIndividual)->getType() << std::endl;
                encounters++;
            }
        }

        count++;
    }
}