#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
public:
    std::string method;
    std::string uri;
    std::string httpVersion;
    static Request parse(const std::string& requestStr);
};

#endif // REQUEST_H
