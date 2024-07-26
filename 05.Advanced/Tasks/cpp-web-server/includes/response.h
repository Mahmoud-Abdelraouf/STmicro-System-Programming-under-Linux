#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

class Response {
public:
    std::string httpVersion;
    int statusCode;
    std::string statusMessage;
    std::string body;
    std::string toString();
    static Response create(int statusCode, const std::string &statusMessage, const std::string &body);
};

#endif // RESPONSE_H

