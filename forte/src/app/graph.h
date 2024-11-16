#include <queue>
#include "iostream"
#include "../typeLib/IFB.h"
#include "../typeLib/globalOutputsList.h"

class Graph{
public:
    IFB search(std::string nameFB);
    void BFS(std::vector<IFB*> start, std::vector<IFB*> all, GlobalOutputs* outputsAgregtor);  
};