#include <iostream>
#include <fstream>
#include "FileParser.h"

void FileParser::cleanFilename(std::string &fileName) {
    // Code from: https://stackoverflow.com/a/10532518/8190058
    if (
            fileName != validExtension &&
            fileName.size() > validExtension.size() &&
            fileName.substr(fileName.size() - validExtension.size()) == validExtension
            ) {
        fileName = fileName.substr(0, fileName.size() - validExtension.size());
    }
}

nlohmann::json FileParser::simpleFileParse(std::string filePath) {
    std::ifstream ifs(filePath);
    return nlohmann::json::parse(ifs);
}

nlohmann::json FileParser::parseEnvironmentFile() {
    nlohmann::json parsed {};

    bool success = false;
    while (!success) {
        try {
            std::string filename {};
            std::cout << "Enter the environment file name: ";
            std::cin >> filename;

            cleanFilename(filename);
            std::string path {filePathPrefix + filename + validExtension};
            parsed = simpleFileParse(path);
            success = true;
        } catch (nlohmann::json::parse_error &error) {
            std::cout << "\nInvalid file name... Please try again" << std::endl;
        }
    }

    return parsed;
}