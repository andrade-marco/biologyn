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

    auto parsed = FileParser::parseFile();
    if(Environment::validateJsonEnvironment(parsed)) {
        parsed = Environment::transformJsonEnvironment(parsed);
        Environment env {parsed["xMax"], parsed["yMax"]};

        for (int i = 0; i < parsed["floraCount"]; ++i) {
            env.addFlora(std::make_unique<Flora>(
                    Flora(env, parsed["floraDecayRate"])
            ));
        }
    }

    return 0;
}
