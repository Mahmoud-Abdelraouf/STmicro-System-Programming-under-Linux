#ifndef ROUTER_H
#define ROUTER_H

#include "request.h"
#include "response.h"

class Router {
public:
    Response route(const Request &request);
};

#endif // ROUTER_H

