#include <iostream>
#include <vector>
#include <map>

#include "./src/app/graph.h"
#include "./src/app/parser.h"
#include "./src/typeLib/IFB.h"
#include "./src/typeLib/modules/FBSumOfTwo.h"
#include "./src/typeLib/modules/FBConsoleOut.h"


void parse(){
    Parser::parse("test.xml");
}

void block(){
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
}

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

    std::vector<IFB*> next;
    std::vector<IFB*> next_2;

    next.push_back(new FBSumOfTwo(inputs, outputsAgregtor, connections, next_2, "FBSumOfTwo"));
    next_2.push_back(new FBConsoleOut({{"FBConsoleOut.in1", outputsAgregtor->getOutputs()["FBSumOfTwo.out1"]}},
                                     outputsAgregtor, connections, next, "FBConsoleOut"));
    
    next[0]->setNext(next_2);

    Graph graph;
    graph.BFS(next);

    

    return 0;
}