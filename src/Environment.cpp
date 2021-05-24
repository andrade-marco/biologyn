#include <algorithm>
#include <thread>
#include <nlohmann/json.hpp>
#include <iostream>
#include "Chaos.h"
#include "FileParser.h"
#include "Environment.h"

void validateJson(
        nlohmann::json& schema,
        nlohmann::json& parsed,
        std::vector<std::string> keys = {},
        std::string key = ""
    ) {

    // Record path to variable being validated
    if (key != "") keys.push_back(key);

    for (auto& el : parsed.items()) {
        if (!el.value().is_array() && el.value().is_structured()) {
            validateJson(schema, el.value(), keys, el.key());
        } else {
            if (el.value().is_array()) {
                auto convertedVec = el.value().get<std::vector<unsigned int>>();
                auto convertedSchema = schema[el.key()].get<std::vector<unsigned int>>();
                for (size_t i = 0; i < convertedVec.size(); ++i) {
                    if (convertedVec[i] < 1 || convertedVec[i] > convertedSchema[i]) {
                        throw std::exception();
                    }
                }
            } else {
                // Retrieve value path from schema up to the current element
                nlohmann::json valuePath {schema};
                for(auto it = keys.begin(); it != keys.end(); ++it) {
                    if(it != keys.end()) valuePath = valuePath[*it];
                }
                auto convertedValue = el.value().get<unsigned int>();
                if (convertedValue < 1 || convertedValue > valuePath[el.key()].get<unsigned int>()) {
                    std::string errorPath {};
                    for (auto& key:keys) errorPath += key + " > ";
                    errorPath += el.key();

                    std::cout << "Invalid parameter: "
                              << errorPath
                              << " - min value: 1 | max value: "
                              << valuePath[el.key()].get<unsigned int>()
                              << std::endl;

                    throw std::exception();
                }
            }
        }
    }
}

Environment::Environment() {};

Environment::Environment(nlohmann::json parsedJson): _configuration{parsedJson} {
    auto schema = FileParser::simpleFileParse("../resources/schema.json");
    validateJson(schema, parsedJson);
};

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
    return this->getFloraIntegerConfig("maxDecayRate");
};

unsigned int Environment::getFaunaTotal(NutritionType type, Gender gender) {
    return this->getFaunaIntegerConfig(type, gender, "total");
};

unsigned int Environment::getFaunaDecayRate(NutritionType type, Gender gender) {
    return this->getFaunaIntegerConfig(type, gender, "maxDecayRate");
};

unsigned int Environment::getFaunaMinAttackRate(NutritionType type, Gender gender) {
    return this->getFaunaIntegerConfig(type, gender, "minAttackRate");
};

unsigned int Environment::getFaunaMinDefendRate(NutritionType type, Gender gender) {
    return this->getFaunaIntegerConfig(type, gender, "minDefendRate");
};

const std::vector<std::unique_ptr<Flora>>& Environment::getFlora() {
    return this->_flora;
};

const std::vector<std::unique_ptr<Fauna>>& Environment::getFauna() {
    return this->_fauna;
};

void Environment::addFlora(std::unique_ptr<Flora> flora) {
    this->_flora.emplace_back(std::move(flora));
}

void Environment::addFauna(std::unique_ptr<Fauna> fauna) {
    this->_fauna.emplace_back(std::move(fauna));
}

void Environment::incrementAge() {
    this->_age++;
};

void Environment::simulate() {
    while (!this->_fauna.empty() || !this->_flora.empty()) {
        for (auto& currIndividual:this->_fauna) {
            if (currIndividual->getHealth() == 0) break;

            currIndividual->move();
            currIndividual->scan();
        }

        this->cleanUp(this->_fauna, this->_lastFauna, "\nWARNING: All fauna extinct...");
        this->cleanUp(this->_flora, this->_lastFlora, "\nWARNING: All flora extinct...");
        this->incrementAge();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Environment::report() {
    std::cout << "\n\n*** SUMMARY ***\n" << std::endl;

    std::cout << "Environment existed for " << this->_age << " days\n" << std::endl;

    auto lastFauna = this->_lastFauna.get();
    auto lastFlora = this->_lastFlora.get();

    auto type = lastFauna->getType() == NutritionType::carnivore ? "Carnivore" : "Herbivore";
    auto gender = lastFauna->getGender() == Gender::female ? "Female" : "Male";
    std::cout
        << "Last fauna: " << lastFauna->getId() << "\n"
        << "Age: " << lastFauna->getAge() << "\n"
        << "Type: " << type << "\n"
        << "Gender: " << gender << "\n\n";

    std::cout
        << "Last flora: " << lastFlora->getId() << "\n"
        << "Age: " << lastFlora->getAge() << "\n\n";

    std::cout << "*** THE END OF TIME ***" << std::endl;

}