#include "FBConsoleOut.h"

void FBConsoleOut::execute(GlobalOutputs* outputs){
    for(const auto p:inputs){
        std::cout << p.first << " LOG INFO: " << p.second << std::endl;
    }
}