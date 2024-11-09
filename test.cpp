#include <iostream>
#include <vector>
#include <map>

#include "./src/xmlLib/parser.h"
#include "./src/typeLib/IFB.h"
#include "./src/typeLib/modules/FBSumOfTwo.h"
#include "./src/typeLib/modules/FBConsoleOut.h"

int main() {
    Parser::parse("test.xml");


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

    std::vector<IFB*> next;
    next.push_back(new FBSumOfTwo(inputs, outputsAgregtor, connections, next, "FBSumOfTwo"));
    next.push_back(new FBConsoleOut({{"FBConsoleOut.in1", outputsAgregtor->getOutputs()["FBSumOfTwo.out1"]}},
                                     outputsAgregtor, connections, next, "FBConsoleOut"));

    next[1]->call();
    next[0]->call();
    next[1]->setInputs({{"FBConsoleOut.in1", outputsAgregtor->getOutputs()["FBSumOfTwo.out1"]}});
    next[1]->call();

    return 0;
}