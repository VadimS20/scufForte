#include "graph.h"



void Graph::BFS(std::vector<IFB*> start, std::vector<IFB*> all, GlobalOutputs* outputsAgregtor){
    std::queue<IFB*> queue;
    for(const auto& block:start){
        queue.push(block);
    }

    while(!queue.empty()){
        auto* block=queue.front();
        queue.pop();

        auto outputs = outputsAgregtor->getOutputs();

        auto inputs = block->getInputs();

        auto newInputs = inputs;

        std::map<std::string, std::string> connections=block->getConnections();
        
        
        for(const auto& input:inputs){
            if(outputs[connections[input.first]]!=""){
                newInputs[input.first]=outputs[connections[input.first]];
            }
        }

        block->setInputs(newInputs);
        block->call(outputsAgregtor);
        auto next=block->getNext();
        for(const std::string& name:next){
            for(const auto& block:all){
                auto s = name.substr(0, name.size()-4);
                if(s==block->getName()){
                    queue.push(block);
                }
            }
        }
    }
}

//next[1]->setInputs({{"FBConsoleOut.in1", outputsAgregtor->getOutputs()["FBSumOfTwo.out1"]}});