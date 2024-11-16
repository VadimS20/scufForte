#include <iostream>
#include <fstream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <argparse/argparse.hpp>


#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    std::string pathToFile;

    argparse::ArgumentParser program("CLIENT");
    
    program.add_argument("-f", "--file")
        .required()
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
    int port = program.get<int>("-p");

    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Ошибка создания сокета." << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Неверный адрес/адрес не поддерживается." << std::endl;
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Ошибка подключения." << std::endl;
        return -1;
    }

    std::ifstream infile(pathToFile, std::ios::binary);
    if (!infile) {
        std::cerr << "Ошибка открытия файла для чтения." << std::endl;
        return 1;
    }

    while (infile.read(buffer, BUFFER_SIZE) || infile.gcount() > 0) {
        send(sock, buffer, infile.gcount(), 0);
    }

    std::cout << "Файл отправлен." << std::endl;

    infile.close();
    close(sock);
    return 0;
}
