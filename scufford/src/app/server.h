#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>


#define BUFFER_SIZE 1024

class Server{
private:
    int port;
    void serverLogic();
public:
    Server(int port) : port(port) {};
    int runServer();
};