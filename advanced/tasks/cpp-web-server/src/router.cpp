#include "router.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <filesystem>

Router::Router(const std::string& basePath) : m_basePath(std::filesystem::canonical(basePath)) {
    m_isDirectory = std::filesystem::is_directory(m_basePath);
}

Response Router::route(const Request& request) const {
    std::filesystem::path filePath;
    if (m_isDirectory) {
        filePath = m_basePath / request.uri.substr(1);
    } else {
        filePath = m_basePath;
    }

    if (request.method == "GET") {
        std::string body = readFile(filePath.string());
        if (!body.empty()) {
            return Response::create(200, "OK", body);
        } else {
            return Response::create(404, "Not Found", "Page not found");
        }
    }
    return Response::create(405, "Method Not Allowed", "Only GET method is allowed");
}
