#include "../includes/router.h"
#include "../includes/utils.h"
#include <fstream>

Response Router::route(const Request &request) {
    std::string filePath = "public" + request.uri;
    if (request.method == "GET") {
        // Handle the root URI
        if (request.uri == "/") {
            filePath = "public/index.html";
        }

        std::string body = readFile(filePath);
        if (!body.empty()) {
            return Response::create(200, "OK", body);
        } else {
            return Response::create(404, "Not Found", "Page not found");
        }
    }
    return Response::create(405, "Method Not Allowed", "Only GET method is allowed");
}
