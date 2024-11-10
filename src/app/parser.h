#pragma once
#include <string>
#include "iostream"
#include "../../lib/pugixml.hpp"

class Parser{
public:
    static void parse(std::string pathToFile);
};
