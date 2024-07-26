#ifndef ROUTER_H
#define ROUTER_H

#include "request.h"
#include "response.h"
#include <string>

class Router {
public:
    Router(const std::string& basePath);
    Response route(const Request& request) const;
private:
    std::string m_basePath;
};

#endif // ROUTER_H
