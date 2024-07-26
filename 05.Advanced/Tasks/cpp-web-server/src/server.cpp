#include "../includes/server.h"
#include "../includes/request.h"
#include "../includes/response.h"
#include "../includes/router.h"
#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

Server::Server(const std::string &address, int port)
    : address(address), port(port) {}

void Server::start() {
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0) {
    std::cerr << "Failed to create socket" << std::endl;
    return;
  }

  sockaddr_in serverAddr{};
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = inet_addr(address.c_str());
  serverAddr.sin_port = htons(port);

  if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    std::cerr << "Failed to bind socket" << std::endl;
    return;
  }

  if (listen(serverSocket, 10) < 0) {
    std::cerr << "Failed to listen on socket" << std::endl;
    return;
  }

  std::cout << "Server listening on " << address << ":" << port << std::endl;

  while (true) {
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket < 0) {
      std::cerr << "Failed to accept client connection" << std::endl;
      continue;
    }
    handleClient(clientSocket);
  }
}

void Server::handleClient(int clientSocket) {
  char buffer[1024];
  read(clientSocket, buffer, sizeof(buffer));
  Request request = Request::parse(buffer);
  Router router;
  Response response = router.route(request);
  std::string responseStr = response.toString();
  write(clientSocket, responseStr.c_str(), responseStr.size());
  close(clientSocket);
}
