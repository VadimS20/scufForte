#include "server.h"

void Server::serverLogic(){
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
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Scufford запущен. Ожидание подключения..." << std::endl;
    while (1) {
        
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        std::cout << "Клиент подключен." << std::endl;

        std::ofstream outfile("received_file.xml", std::ios::binary);
        if (!outfile) {
            std::cerr << "Ошибка открытия файла для записи." << std::endl;
        }

        int bytes_read;
        while ((bytes_read = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
            outfile.write(buffer, bytes_read);
        }

        std::cout << "Файл получен." << std::endl;

        outfile.close();
    }
    close(new_socket);
    close(server_fd);
}

int Server::runServer(){
    std::thread server_thread([this]() {
        this->serverLogic();
    });
    server_thread.detach();
}