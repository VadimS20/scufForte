#include <iostream>
#include <vector>
#include <map>

#include "./src/typeLib/IFB.h"
#include "./src/typeLib/modules/FBSumOfTwo.h"

int main() {
    std::map<std::string, std::string> inputs = {
        {"in1", "1"},
        {"in2", "2"},
    };
    std::map<std::string, std::string> connections = {
        {"out1", "in1"}
    };
    std::map<std::string, std::string> outputs = {
        {"out1", ""}
    };
    GlobalOutputs* outputsAgregtor = GlobalOutputs::getInstance(outputs);
    std::vector<IFB*> next;
    next.push_back(new FBSumOfTwo(inputs, outputsAgregtor, connections, next, "FBSumOfTwo"));
    next[0]->call();
    return 0;
}