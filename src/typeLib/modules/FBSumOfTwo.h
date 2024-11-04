#pragma once
#include "../IFB.h"

class FBSumOfTwo : public IFB{
private:
    void execute() override;
public:
    FBSumOfTwo(std::map<std::string, std::string> inputs,
        GlobalOutputs* outputs, 
        std::map<std::string, std::string> connections, 
        std::vector<IFB*> next,
        std::string FBname) : IFB(inputs, outputs, connections, next, FBname) {};
};