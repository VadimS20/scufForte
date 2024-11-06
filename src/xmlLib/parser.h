#pragma once
#include <string>
#include "../../lib/pugixml.hpp"

class Parser{
public:
    Parser(std::string pathToFile);
    void parse();
private:
    std::string path;
};
