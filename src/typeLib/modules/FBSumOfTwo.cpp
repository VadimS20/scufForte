#include "FBSumOfTwo.h"

void FBSumOfTwo::execute(GlobalOutputs* outputs){
    int sum=0;
    for(const auto p : this->inputs){
        sum += std::stoi(p.second);
    }
    outputs->setOutput(this->FBname+".out1",std::to_string(sum));
}