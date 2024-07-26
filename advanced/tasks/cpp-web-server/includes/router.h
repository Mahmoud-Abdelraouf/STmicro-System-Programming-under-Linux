#ifndef ROUTER_H
#define ROUTER_H

#include "request.h"
#include "response.h"
#include <string>
#include <filesystem>

class Router {
public:
    Router(const std::string& basePath);
    Response route(const Request& request) const;
private:
    std::filesystem::path m_basePath;
    bool m_isDirectory;
};

#endif // ROUTER_H
