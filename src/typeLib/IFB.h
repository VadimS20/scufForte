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
    std::vector<IFB*> getNext();
    void setNext(std::vector<IFB*> newNext);
    void setInputs(std::map<std::string, std::string> inputs);
};


// output format = {
//      "FBname.in1": "value1",
//      "FBname.in2": "value2",
//      ....
// }

// when init class object send value as ""


// input format = {
//      "FBname.in1": "value1",
//      "FBname.in2": "value2",
//       ....
// }