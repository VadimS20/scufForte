#include <iostream>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <argparse/argparse.hpp>

#include "./src/app/server.h"
#include "./src/app/graph.h"
#include "./src/app/parser.h"
#include "./src/typeLib/IFB.h"
#include "./src/typeLib/modules/FBSumOfTwo.h"
#include "./src/typeLib/modules/FBConsoleOut.h"


void runApp(std::string xmlFile){
    auto pair=Parser::parse(xmlFile);
    auto all=pair.first;
    auto agregtor=pair.second;

    std::vector<IFB*> start;
    start.push_back(all[0]);
    auto graph=new Graph();
    graph->BFS(start,all,agregtor);
}

int main(int argc, char *argv[]) {
    std::string pathToFile;
    int port;

    argparse::ArgumentParser program("scufford");
    
    program.add_argument("-f", "--file")
        .default_value("")
        .help("input .xml filename");

    program.add_argument("-p", "--port")
        .default_value(61499)
        .help("specify port to connect")
        .scan<'i', int>();

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    pathToFile = program.get("-f");
    port = program.get<int>("-p");
    Server server(port);
    if (pathToFile == ""){
        server.runServer();
        runApp("received_file.xml");
    } else {
        runApp(pathToFile);
    }

    return 0;
}