#include <iostream>
#include <fstream>
#include "FileParser.h"

void FileParser::cleanFilename(std::string &filename) {
    // Code from: https://stackoverflow.com/a/10532518/8190058
    if (
            filename != validExtension &&
            filename.size() > validExtension.size() &&
            filename.substr(filename.size() - validExtension.size()) == validExtension
            ) {
        filename = filename.substr(0, filename.size() - validExtension.size());
    }
}

nlohmann::json FileParser::parseFile() {
    nlohmann::json parsed {};

    bool success = false;
    while (!success) {
        try {
            std::string filename {};
            std::cout << "Enter the environment file name: ";
            std::cin >> filename;

            cleanFilename(filename);
            std::string path {filePathPrefix + filename + validExtension};
            std::ifstream ifs(path);
            parsed = nlohmann::json::parse(ifs);
            success = true;
        } catch (nlohmann::json::parse_error &error) {
            std::cout << "\nInvalid file name... Please try again" << std::endl;
        }
    }

    return parsed;
}