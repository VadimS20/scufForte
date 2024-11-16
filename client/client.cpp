#include <iostream>
#include <fstream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 61499
#define BUFFER_SIZE 1024

int main() {
    std::string pathToFile;
    std::cout << "Input path to file ";
    std::cin >> pathToFile;

    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Создание сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Ошибка создания сокета." << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Преобразование IPv4 и IPv6 адресов из текстового формата в двоичный
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Неверный адрес/адрес не поддерживается." << std::endl;
        return -1;
    }

    // Подключение к серверу
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Ошибка подключения." << std::endl;
        return -1;
    }

    // Отправка файла
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
