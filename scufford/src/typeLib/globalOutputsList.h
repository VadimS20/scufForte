#pragma once

#include <map>
#include <string>


class GlobalOutputs {
private:
    // GlobalOutputs* instance;
    std::map<std::string, std::string> outputs;
    

public:
    GlobalOutputs(std::map<std::string, std::string> outputs);
    // GlobalOutputs* getInstance(std::map<std::string, std::string> outputs);
    std::map<std::string, std::string> getOutputs();
    void setOutputs(std::map<std::string, std::string> outputs);
    void setOutput(std::string name, std::string value);
};
