#include "parser.h"


std::pair<std::vector<IFB*>, GlobalOutputs*> Parser::parse(std::string pathToFile){
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file(pathToFile.c_str());

    if (!result) {
        std::cerr << "XML parsed with errors, error description: "
            << result.description()
            << "\n";
    }

    auto root=doc.child("FB_Blocks");
    std::vector<IFB*> FBs;

    std::map<std::string, std::string> outputs;
    
    for (pugi::xml_node fbNode = root.child("FunctionBlock"); fbNode; fbNode = fbNode.next_sibling("FunctionBlock")) {
        std::string name = fbNode.child("Name").text().as_string();
        std::string type = fbNode.child("Type").text().as_string();
        std::string description = fbNode.child("Description").text().as_string();

        // std::cout << "Function Block:" << std::endl;
        // std::cout << "  Name: " << name << std::endl;
        // std::cout << "  Type: " << type << std::endl;

        auto var = fbNode.child("Interface");

        std::map<std::string, std::string> inputs;
        //std::cout << "  Input Variables:" << std::endl;
        for (pugi::xml_node inputNode = var.child("InputVariables").child("Variable"); inputNode; inputNode = inputNode.next_sibling("Variable")) {
            //std::cout << "    - " << inputNode.child("Name").text().as_string() <<" value: " << inputNode.child("Value").text().as_string() <<std::endl;

            inputs[inputNode.child("Name").text().as_string()] = inputNode.child("Value").text().as_string();
        }
        
        //std::cout << "  Output Variables:" << std::endl;
        for (pugi::xml_node outputNode = var.child("OutputVariables").child("Variable"); outputNode; outputNode = outputNode.next_sibling("Variable")) {
            //std::cout << "    - " << outputNode.child("Name").text().as_string() << std::endl;

            outputs[outputNode.child("Name").text().as_string()] = "";
        }

        std::map<std::string, std::string> connections;
        std::vector<std::string> next;
        //std::cout << "  Connections:" << std::endl;
        for (pugi::xml_node connNode = var.child("Connections").child("Connection"); connNode; connNode = connNode.next_sibling("Connection")) {
            //std::cout << "    - " << connNode.child("Source").text().as_string() <<" ---> " << connNode.child("Target").text().as_string() << std::endl;

            std::string connTo = connNode.child("Target").text().as_string();
            
            if (connTo.find("REQ")!=std::string::npos) {
                next.push_back(connTo);
            } else { 
                connections[connTo] = connNode.child("Source").text().as_string();
            }
        }

        if (type == "FBSumOfTwo") {
            FBs.push_back(new FBSumOfTwo(inputs, connections, next, name));
        } else if (type == "FBConsoleOut") {
            FBs.push_back(new FBConsoleOut(inputs, connections, next, name));
        } else {
            //std::cout << "Unknown function block type" << std::endl;
        }
        
        //std::cout << std::endl;
    }
    

    auto Output=new GlobalOutputs(outputs);

    return std::make_pair(FBs, Output);
}