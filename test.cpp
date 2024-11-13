#include <iostream>
#include <vector>
#include <map>

#include "./src/app/graph.h"
#include "./src/app/parser.h"
#include "./src/typeLib/IFB.h"
#include "./src/typeLib/modules/FBSumOfTwo.h"
#include "./src/typeLib/modules/FBConsoleOut.h"


// void parse(){
//     Parser::parse("test.xml");
// }

// void block(){
//     std::map<std::string, std::string> inputs = {
//         {"FBSumOfTwo.in1", "1"},
//         {"FBSumOfTwo.in2", "2"},
//     };
//     std::map<std::string, std::string> connections = {
//         {"FBSumOfTwo.out1", "FBConsoleOut.in1"}
//     };
//     std::map<std::string, std::string> outputs = {
//         {"FBSumOfTwo.out1", ""}
//     };
//     GlobalOutputs* outputsAgregtor = GlobalOutputs::getInstance(outputs);

//     std::vector<IFB*> next;
//     next.push_back(new FBSumOfTwo(inputs, connections, {"FBConsoleOut"}, "FBSumOfTwo"));
//     next.push_back(new FBConsoleOut({{"FBConsoleOut.in1", outputsAgregtor->getOutputs()["FBSumOfTwo.out1"]}},
//                                      connections, {"FBSumOfTwo"}, "FBConsoleOut"));

//     next[1]->call(outputsAgregtor);
//     next[0]->call(outputsAgregtor);
//     next[1]->setInputs({{"FBConsoleOut.in1", outputsAgregtor->getOutputs()["FBSumOfTwo.out1"]}});
//     next[1]->call(outputsAgregtor);
// }

int main() {
    
    auto pair=Parser::parse("test.xml");

    std::vector<IFB*> blocks=pair.first;
    GlobalOutputs* outputsAgregtor=pair.second;
    // block();

    // std::map<std::string, std::string> inputs = {
    //     {"FBSumOfTwo.in1", "1"},
    //     {"FBSumOfTwo.in2", "2"},
    // };
    // std::map<std::string, std::string> connections = {
    //     {"FBConsoleOut.in1", "FBSumOfTwo.out1"}
    // };
    // std::map<std::string, std::string> outputs = {
    //     {"FBSumOfTwo.out1", ""}
    // };
    // // GlobalOutputs* outputsAgregtor = GlobalOutputs::getInstance(outputs);

    // std::vector<IFB*> next;
    // std::vector<IFB*> next_2;
    // std::vector<IFB*> next_3;

    // next.push_back(new FBSumOfTwo(inputs, connections, {"FBConsoleOut"}, "FBSumOfTwo"));
    // next_2.push_back(new FBConsoleOut({{"FBConsoleOut.in1", outputsAgregtor->getOutputs()["FBSumOfTwo.out1"]}},
    //                                  connections, {"FBSumOfTwo"}, "FBConsoleOut"));
    

    auto graph=new Graph();
    graph->BFS(blocks,outputsAgregtor);

    

    return 0;
}