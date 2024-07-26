#include "../includes/server.h"
#include <iostream>

int main() {
    std::string address = "127.0.0.1";
    int port;
    std::string basePath;

    std::cout << "Enter the port number: ";
    std::cin >> port;

    std::cout << "Enter the base path to serve files from: ";
    std::cin >> basePath;

    Server server(address, port, basePath);
    server.start();

    return 0;
}
