#pragma once
#include <string>
#include "iostream"
#include "../../lib/pugixml.hpp"
#include "../typeLib/IFB.h"

class Parser{
public:
    static void parse(std::string pathToFile);
};
