#include <iostream>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <filesystem>
#include <thread>
#include <stop_token>

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

    std::vector<IFB*> start = {};
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
    

    if (pathToFile == ""){
        std::thread appThread; 
        while (1)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Симуляция ожидания запроса
            
            if (std::filesystem::exists("./received_file.xml")) {
                
                if (appThread.joinable()) {
                    appThread.detach(); // Дождаться завершения потока
                }
                
                // Запустить новый поток для обработки нового файла
                appThread = std::thread(runApp, "received_file.xml");
            }
        }
    } else {
        runApp(pathToFile);
    }

    return 0;
}