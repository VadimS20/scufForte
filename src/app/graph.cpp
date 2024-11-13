#include "graph.h"

void Graph::BFS(std::vector<IFB*> start, GlobalOutputs* outputsAgregtor){
    std::queue<IFB*> queue;
    // queue.push(start[0]);
    while(!queue.empty()){
        auto* block=queue.front();
        queue.pop();

        auto outputs = outputsAgregtor->getOutputs();

        auto inputs = block->getInputs();

        auto newInputs = inputs;

        auto connections=block->getConnections();

        for(const auto& input:inputs){
            for(const auto& conn:connections[input.first]){
                if(outputs[conn]!=""){
                    newInputs[input.first]=outputs[conn];
                }
            }
        }

        block->setInputs(newInputs);
        block->call(outputsAgregtor);

        auto next=block->getNext();



        for(const std::string nextConn:next){
            for(const auto& block:start){
                if(block->getName()==nextConn.substr(0,nextConn.length()-4)){
                    queue.push(block);
                }
            }
        }

    }
}

//next[1]->setInputs({{"FBConsoleOut.in1", outputsAgregtor->getOutputs()["FBSumOfTwo.out1"]}});