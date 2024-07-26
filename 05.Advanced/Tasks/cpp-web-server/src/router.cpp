#include "../includes/router.h"
#include "../includes/utils.h"
#include <fstream>

Response Router::route(const Request &request) {
  if (request.method == "GET" && request.uri == "/") {
    std::string body = readFile("index.html");
    return Response::create(200, "OK", body);
  }
  return Response::create(404, "Not Found", "Page not found");
}
