#include "request.h"
#include <sstream>

Request Request::parse(const std::string& requestStr) {
  Request request;
  std::istringstream stream(requestStr);
  stream >> request.method >> request.uri >> request.httpVersion;
  return request;
}
