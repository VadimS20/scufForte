#include "parser.h"


void Parser::parse(std::string pathToFile){
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file(pathToFile.c_str());

    if (!result) {
        std::cerr << "XML parsed with errors, error description: "
            << result.description()
            << "\n";
    }

    auto root=doc.child("FB_Blocks");

    for (pugi::xml_node fbNode = root.child("FunctionBlock"); fbNode; fbNode = fbNode.next_sibling("FunctionBlock")) {
        std::string name = fbNode.child("Name").text().as_string();
        std::string type = fbNode.child("Type").text().as_string();
        std::string description = fbNode.child("Description").text().as_string();

        std::cout << "Function Block:" << std::endl;
        std::cout << "  Name: " << name << std::endl;
        std::cout << "  Type: " << type << std::endl;

        auto var = fbNode.child("Interface");

        std::cout << "  Input Variables:" << std::endl;
        for (pugi::xml_node inputNode = var.child("InputVariables").child("Variable"); inputNode; inputNode = inputNode.next_sibling("Variable")) {
            std::cout << "    - " << inputNode.child("Name").text().as_string() <<" value: " << inputNode.child("Value").text().as_int() <<std::endl;
        
        }

        std::cout << "  Output Variables:" << std::endl;
        for (pugi::xml_node outputNode = var.child("OutputVariables").child("Variable"); outputNode; outputNode = outputNode.next_sibling("Variable")) {
            std::cout << "    - " << outputNode.child("Name").text().as_string() << std::endl;
        }

        std::cout << "  Connections:" << std::endl;

        for (pugi::xml_node connNode = var.child("Connections").child("Connection"); connNode; connNode = connNode.next_sibling("Connection")) {
            std::cout << "    - " << connNode.child("Source").text().as_string() <<" ---> " << connNode.child("Target").text().as_string() << std::endl;
        }

        std::cout << std::endl;
    }
}