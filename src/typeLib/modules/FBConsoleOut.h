#pragma once
#include "../IFB.h"
#include <iostream>

class FBConsoleOut : public IFB{
private:
    void execute() override;

public:
    FBConsoleOut(std::map<std::string, std::string> inputs,
        GlobalOutputs* outputs, 
        std::map<std::string, std::string> connections, 
        std::vector<IFB*> next,
        std::string FBname) : IFB(inputs, outputs, connections, next, FBname) {};
};