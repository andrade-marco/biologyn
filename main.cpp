#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include "src/FileParser.h"
#include "src/Environment.h"
#include "src/Flora.h"
#include "src/Fauna.h"

int main() {

    std::cout << "*******************" << std::endl;
    std::cout << "Welcome to Biologyn" << std::endl;
    std::cout << "*******************\n" << std::endl;

    // Try to load environment and exit if validation or unexpected error occurs
    Environment env;
    try {
        auto parsed = FileParser::parseEnvironmentFile();
        env = Environment(parsed);
    } catch (nlohmann::json::type_error &error) {
        std::cout << "\nEnvironment file missing required keys and/or contains unexpected keys. Please review README "
                     "file.";
        return 0;
    } catch (std::exception &error) {
        std::cout << "\nError occurred. Please review your environment file.";
        return 0;
    }

    // Load individuals to environment if initialization is successful
    for (int i = 0; i < env.getFloraTotal(); ++i) {
        env.addFlora(std::make_unique<Flora>(
                Flora("flora_" + std::to_string(i + 1), env, env.getFloraDecayRate()
        )));
    }

    int faunaCount {1};
    for (int i = Gender::male; i <= Gender::female; ++i) {
        for (int j = NutritionType::herbivore; j <= NutritionType::carnivore; ++j) {
            auto type = static_cast<NutritionType>(j);
            auto gender = static_cast<Gender>(i);

            for (int k = 0; k < env.getFaunaTotal(type, gender); ++k) {
                std::string id = "fauna_" + std::to_string(faunaCount);
                env.addFauna(std::make_unique<Fauna>(Fauna(id, env, type, gender)));
                faunaCount++;
            }
        }
    }

    env.simulate();
    env.report();

    return 0;
}
