//
// Created by Marco Andrade on 2021-04-12.
//

#include "Environment.h"

Environment::Environment(unsigned int x, unsigned int y): _xBound{x}, _yBound{y} {};

std::vector<unsigned int> Environment::getDimensions() {
    return std::vector<unsigned int> {this->_xBound, this->_yBound};
}