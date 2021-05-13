//
// Created by Marco Andrade on 2021-04-12.
//

#include <nlohmann/json.hpp>
#include <iostream>
#include "Environment.h"

using json = nlohmann::json;

Environment::Environment(unsigned int x, unsigned int y): _xBound{x}, _yBound{y} {};

std::vector<unsigned int> Environment::getDimensions() {
    return std::vector<unsigned int> {this->_xBound, this->_yBound};
}

bool Environment::validateJsonEnvironment(json &parsed) {
    try {
        auto xMax = (unsigned int)parsed["xMax"];
        auto yMax = (unsigned int)parsed["yMax"];

        if (xMax > MAX_DIMENSION || yMax > MAX_DIMENSION) {
            std::cout << "\nInvalid dimensions: xMax and yMax must not exceed " << MAX_DIMENSION << std::endl;
            return false;
        }

        if ((int)parsed["faunaCount"] > (xMax * yMax)) {
            std::cout << "\nInvalid faunaCount: it must not exceed xMax multiplied by yMax" << std::endl;
            return false;
        }

        if ((int)parsed["floraCount"] > (xMax * yMax)) {
            std::cout << "\nInvalid floraCount: it must not exceed xMax multiplied by yMax" << std::endl;
            return false;
        }

        return true;

    } catch (json::type_error &error) {
        std::cout << "\nEnvironment file missing required keys. Please review README file.";
        return false;
    } catch (std::exception &error) {
        std::cout << "\nSomething went wrong. Please review your environment file.";
        return false;
    }
}

std::map<std::string, int> Environment::transformJsonEnvironment(json &parsed) {
    std::map<std::string, int> transformed {};
    for (auto& el : parsed.items()) {
        transformed[el.key()] = (int) el.value();
    }

    return transformed;
}

void Environment::addFlora(std::unique_ptr<Flora> flora) {
    this->_flora.emplace_back(std::move(flora));
}

void Environment::addFauna(std::unique_ptr<Fauna> fauna) {
    this->_fauna.emplace_back(std::move(fauna));
}