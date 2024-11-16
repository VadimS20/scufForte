#include <iostream>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include "./src/app/graph.h"
#include "./src/app/parser.h"
#include "./src/typeLib/IFB.h"
#include "./src/typeLib/modules/FBSumOfTwo.h"
#include "./src/typeLib/modules/FBConsoleOut.h"


#define PORT 61499
#define BUFFER_SIZE 1024


void parse(){
    Parser::parse("test.xml");
}

void block(){
    std::map<std::string, std::string> inputs = {
        {"FBSumOfTwo.in1", "1"},
        {"FBSumOfTwo.in2", "2"},
    };
    std::map<std::string, std::string> connections = {
        {"FBSumOfTwo.out1", "FBConsoleOut.in1"}
    };
    std::map<std::string, std::string> outputs = {
        {"FBSumOfTwo.out1", ""}
    };
    GlobalOutputs* outputsAgregtor = GlobalOutputs::getInstance(outputs);

    std::vector<IFB*> next;
    next.push_back(new FBSumOfTwo(inputs, connections, {"FBConsoleOut"}, "FBSumOfTwo"));
    next.push_back(new FBConsoleOut({{"FBConsoleOut.in1", outputsAgregtor->getOutputs()["FBSumOfTwo.out1"]}},
                                     connections, {"FBSumOfTwo"}, "FBConsoleOut"));

    next[1]->call(outputsAgregtor);
    next[0]->call(outputsAgregtor);
    next[1]->setInputs({{"FBConsoleOut.in1", outputsAgregtor->getOutputs()["FBSumOfTwo.out1"]}});
    next[1]->call(outputsAgregtor);
}

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
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Сервер запущен. Ожидание подключения..." << std::endl;

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    std::cout << "Клиент подключен." << std::endl;

    std::ofstream outfile("received_file.xml", std::ios::binary);
    if (!outfile) {
        std::cerr << "Ошибка открытия файла для записи." << std::endl;
        return 1;
    }

    int bytes_read;
    while ((bytes_read = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
        outfile.write(buffer, bytes_read);
    }
    outfile.close();
    close(new_socket);
    close(server_fd);

    runApp("received_file.xml");

    return 0;
}