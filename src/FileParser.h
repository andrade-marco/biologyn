#ifndef BIOLOGYN_FILEPARSER_H
#define BIOLOGYN_FILEPARSER_H

#include <string>
#include <nlohmann/json.hpp>

namespace FileParser {
    const std::string validExtension {".json"};
    const std::string filePathPrefix {"../environments/"};

    void cleanFilename(std::string &fileName);
    nlohmann::json simpleFileParse(std::string filePath);
    nlohmann::json parseEnvironmentFile();
};


#endif //BIOLOGYN_FILEPARSER_H
