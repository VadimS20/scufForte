#include "FBSumOfTwo.h"

void FBSumOfTwo::execute(){
    int sum=0;
    for(const auto p:inputs){
        sum += std::stoi(p.second);
    }
    this->outputs->setOutput("sum",std::to_string(sum));
}