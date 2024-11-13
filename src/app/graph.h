#pragma once

#include <queue>
#include "iostream"
#include "../typeLib/IFB.h"
#include "../typeLib/globalOutputsList.h"

class Graph{
public:
    void BFS(std::vector<IFB*> start,GlobalOutputs* outputsAgregtor);  
};