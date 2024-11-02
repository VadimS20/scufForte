#include "FBSumOfTwo.h"

void FBSumOfTwo::execute(){
    int sum=0;
    for(const auto p:inputs){
        sum+=p.second;
    }
    outputs[{"out_1",}]=sum;
}