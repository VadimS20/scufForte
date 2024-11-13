#pragma once
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include "../../lib/pugixml.hpp"
#include "../typeLib/IFB.h"
#include "../typeLib/globalOutputsList.h"
#include "../typeLib/modules/FBConsoleOut.h"
#include "../typeLib/modules/FBSumOfTwo.h"


class Parser{
public:
    static std::pair<std::vector<IFB*>, GlobalOutputs*> parse(std::string pathToFile);
};
