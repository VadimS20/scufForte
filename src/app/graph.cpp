#include "graph.h"

void Graph::BFS(std::vector<IFB*> start){
    std::queue<IFB*> queue;
    for(const auto& block:start){
        queue.push(block);
    }
    while(!queue.empty()){
        auto* block=queue.front();
        queue.pop();
        block->call();
        auto blocks=block->getNext();
        for(const auto& b:blocks){
            queue.push(b);
        }
    }
}