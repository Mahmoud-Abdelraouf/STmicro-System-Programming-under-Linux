#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "router.h"

class Server {
public:
    Server(const std::string& address, int port, const std::string& basePath);
    void start();
private:
    std::string m_address;
    int m_port;
    std::string m_basePath;
    Router m_router;
    void handleClient(int clientSocket);
};

#endif // SERVER_H
