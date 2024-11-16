#include <iostream>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

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

int main() {
    Server::server(61499);

    runApp("received_file.xml");

    return 0;
}