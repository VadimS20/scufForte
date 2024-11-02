#pragma once
#include "../IFB.h"

class FBSumOfTwo:public IFB<int>{
private:
    void execute() override;
public:
    FBSumOfTwo();
};