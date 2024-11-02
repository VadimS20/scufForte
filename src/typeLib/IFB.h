#pragma once
#include <vector>
#include <string>
#include <map>


template <typename T>
class IFB{
protected:
    std::map<std::string, T> inputs;
    std::map<std::pair<std::string, std::string>, T>  outputs;
    virtual void execute() = 0;
    void sentOutputs();
    std::vector<IFB*> next;

public:
    IFB(std::map<std::string, T> inputs,
        std::map<std::pair<std::string, std::string>, T>  outputs, 
        std::vector<IFB*> next);
    void call();
};


// output format = {
//      {"out1", "in1"}: "value1",
//      {"out2", "in2"}: "value2",
//      ....
// }

// to constuct send value as null


// input format = {
//      "in1": "value1",
//      "in2": "value2",
//       ....
// }