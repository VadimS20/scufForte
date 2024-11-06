#pragma once

#include <vector>
#include <string>
#include <map>
#include "globalOutputsList.h"


class IFB{
protected:
    std::map<std::string, std::string> inputs;
    GlobalOutputs* outputs;
    std::map<std::string, std::string> connections;
    std::vector<IFB*> next;

    std::string FBname;

    virtual void execute() = 0;
    void sentOutputs();
    
public:
    IFB(std::map<std::string, std::string> inputs,
        GlobalOutputs* outputs, 
        std::map<std::string, std::string> connections, 
        std::vector<IFB*> next,
        std::string FBname);
    void call();
};


// output format = {
//      "in1": "value1",
//      "in2": "value2",
//      ....
// }

// to constuct send value as null


// input format = {
//      "in1": "value1",
//      "in2": "value2",
//       ....
// }