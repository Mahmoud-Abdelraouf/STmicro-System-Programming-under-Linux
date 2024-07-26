#ifndef SERVER_H
#define SERVER_H

#include <string>

class Server {
public:
    Server(const std::string &address, int port);
    void start();
private:
    std::string address;
    int port;
    void handleClient(int clientSocket);
};

#endif // SERVER_H

