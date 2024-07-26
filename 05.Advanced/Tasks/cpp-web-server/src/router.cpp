#include "router.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <filesystem>

Router::Router(const std::string& basePath) : m_basePath(basePath) {}

Response Router::route(const Request& request) const {
    std::string filePath = std::filesystem::path(m_basePath) / request.uri.substr(1);
    if (request.method == "GET") {
        std::string body = readFile(filePath);
        if (!body.empty()) {
            return Response::create(200, "OK", body);
        } else {
            return Response::create(404, "Not Found", "Page not found");
        }
    }
    return Response::create(405, "Method Not Allowed", "Only GET method is allowed");
}
