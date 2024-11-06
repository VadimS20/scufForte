#include <iostream>
#include <vector>
#include <map>

#include "./src/typeLib/IFB.h"
#include "./src/typeLib/modules/FBSumOfTwo.h"

int main() {
    std::map<std::string, std::string> inputs = {
        {"FBSumOfTwo.in1", "1"},
        {"FBSumOfTwo.in2", "2"},
    };
    std::map<std::string, std::string> connections = {
        {"FBSumOfTwo.out1", "FBSumOfTwo.in1"}
    };
    std::map<std::string, std::string> outputs = {
        {"FBSumOfTwo.out1", ""}
    };
    GlobalOutputs* outputsAgregtor = GlobalOutputs::getInstance(outputs);

    for (auto x : outputsAgregtor->getOutputs()) {
        std::cout << x.first << " " << x.second << std::endl;
    }

    std::vector<IFB*> next;
    next.push_back(new FBSumOfTwo(inputs, outputsAgregtor, connections, next, "FBSumOfTwo"));
    next[0]->call();

    for (auto x : outputsAgregtor->getOutputs()) {
        std::cout << x.first << " " << x.second << std::endl;
    }

    return 0;
}