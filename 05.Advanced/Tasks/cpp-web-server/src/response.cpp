#include "../includes/response.h"
#include <sstream>

Response Response::create(int statusCode, const std::string &statusMessage,
                          const std::string &body) {
  Response response;
  response.httpVersion = "HTTP/1.1";
  response.statusCode = statusCode;
  response.statusMessage = statusMessage;
  response.body = body;
  return response;
}

std::string Response::toString() {
  std::ostringstream stream;
  stream << httpVersion << " " << statusCode << " " << statusMessage << "\r\n";
  stream << "Content-Length: " << body.size() << "\r\n";
  stream << "Content-Type: text/html\r\n";
  stream << "\r\n";
  stream << body;
  return stream.str();
}
