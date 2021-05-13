#ifndef BIOLOGYN_FILEPARSER_H
#define BIOLOGYN_FILEPARSER_H

#include <string>
#include <nlohmann/json.hpp>

namespace FileParser {
    const std::string validExtension {".json"};
    const std::string filePathPrefix {"../environments/"};

    void cleanFilename(std::string &filename);
    nlohmann::json parseFile();
};


#endif //BIOLOGYN_FILEPARSER_H
