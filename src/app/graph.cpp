#include "graph.h"

void Graph::BFS(std::vector<IFB*> start, GlobalOutputs* outputsAgregtor, std::map<std::string, std::string> connections){
    std::queue<IFB*> queue;
    for(const auto& block : start){
        queue.push(block);
    }
    while(!queue.empty()){
        auto* block=queue.front();
        queue.pop();

        auto outputs = outputsAgregtor->getOutputs();

        auto inputs = block->getInputs();

        auto newInputs = inputs;

        for(const auto& input:inputs){
            if(connections.find(input.first)!=connections.end() && outputs[connections[input.first]]!=""){
                newInputs[input.first]=outputs[connections[input.first]];
            }
        }

        block->setInputs(newInputs);

        block->call();
        auto blocks=block->getNext();
        for(const auto& b:blocks){
            queue.push(b);
        }
    }
}

//next[1]->setInputs({{"FBConsoleOut.in1", outputsAgregtor->getOutputs()["FBSumOfTwo.out1"]}});