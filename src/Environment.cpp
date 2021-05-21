#include <algorithm>
#include <thread>
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