#include "FBConsoleOut.h"

void FBConsoleOut::execute(){
    for(const auto p:inputs){
        std::cout << p.first << " LOG INFO: " << p.second << std::endl;
    }
}