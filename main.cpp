#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include "src/Environment.h"
#include "src/Flora.h"

using json = nlohmann::json;

constexpr unsigned int MAX_DIMENSION = 1000;

void cleanFilename(std::string &filename) {
    // Code from: https://stackoverflow.com/a/10532518/8190058
    const std::string extension(".json");
    if (
            filename != extension &&
            filename.size() > extension.size() &&
            filename.substr(filename.size() - extension.size()) == ".json"
        ) {
        filename = filename.substr(0, filename.size() - extension.size());
    }
}

json parseFile() {
    json parsed {};

    bool success = false;
    while (!success) {
        try {
            std::string filename {};
            std::cout << "Enter the environment file name: ";
            std::cin >> filename;

            cleanFilename(filename);
            std::string path = "../environments/" + filename + ".json";
            std::ifstream ifs(path);
            parsed = json::parse(ifs);
            success = true;
        } catch (json::parse_error &error) {
            std::cout << "\nInvalid file name... Please try again" << std::endl;
        }
    }

    return parsed;
}

bool validateEnvironment(json environment) {
    try {
        unsigned int xMax = (unsigned int)environment["xMax"];
        unsigned int yMax = (unsigned int)environment["yMax"];

        if (xMax > MAX_DIMENSION || yMax > MAX_DIMENSION) {
            std::cout << "\nInvalid dimensions: xMax and yMax must not exceed " << MAX_DIMENSION << std::endl;
            return false;
        }

        if ((int)environment["faunaCount"] > (xMax * yMax)) {
            std::cout << "\nInvalid faunaCount: it must not exceed xMax multiplied by yMax" << std::endl;
            return false;
        }

        if ((int)environment["floraCount"] > (xMax * yMax)) {
            std::cout << "\nInvalid floraCount: it must not exceed xMax multiplied by yMax" << std::endl;
            return false;
        }

        return true;

    } catch (json::type_error &error) {
        std::cout << "\nEnvironment file missing required keys. Please review README file.";
    } catch (std::exception &error) {
        std::cout << "\nSomething went wrong. Please review your environment file.";
    }
}

int main() {

    std::cout << "*******************" << std::endl;
    std::cout << "Welcome to Biologyn" << std::endl;
    std::cout << "*******************\n" << std::endl;

    const json parsed = parseFile();
    if(validateEnvironment(parsed)) {
        Environment env {parsed["xMax"], parsed["yMax"]};

    }

    return 0;
}
