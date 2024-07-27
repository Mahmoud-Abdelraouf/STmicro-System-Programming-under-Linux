### 1. Creating a Socket

#### Code

```cpp
// create_socket.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }
    std::cout << "Socket created successfully" << std::endl;
    return 0;
}
```

#### Expected Output

```
Socket created successfully
```

#### How to Run

```sh
g++ create_socket.cpp -o create_socket
./create_socket
```

### 2. Binding the Socket

#### Code

```cpp
// bind_socket.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    // Configure server address structure
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    // Bind the socket to the address and port
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        return -1;
    }
    std::cout << "Socket bound successfully" << std::endl;

    // Close the socket
    close(serverSocket);
    return 0;
}
```

#### Expected Output

```
Socket bound successfully
```

#### How to Run

```sh
g++ bind_socket.cpp -o bind_socket
./bind_socket
```

### 3. Listening for Connections

#### Code

```cpp
// listen_socket.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    // Configure server address structure
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    // Bind the socket to the address and port
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return -1;
    }
    std::cout << "Listening on 127.0.0.1:8080" << std::endl;

    // Close the socket
    close(serverSocket);
    return 0;
}
```

#### Expected Output

```
Listening on 127.0.0.1:8080
```

#### How to Run

```sh
g++ listen_socket.cpp -o listen_socket
./listen_socket
```

### 4. Accepting Connections

#### Code

```cpp
// accept_connection.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    // Configure server address structure
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    // Bind the socket to the address and port
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return -1;
    }
    std::cout << "Listening on 127.0.0.1:8080" << std::endl;

    // Accept a client connection
    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        return -1;
    }
    std::cout << "Connection accepted" << std::endl;

    // Close the client and server sockets
    close(clientSocket);
    close(serverSocket);
    return 0;
}
```

#### Expected Output

```
Listening on 127.0.0.1:8080
Connection accepted
```

#### How to Run

```sh
g++ accept_connection.cpp -o accept_connection
./accept_connection
```

### 5. Receiving Data

#### Code

```cpp
// receive_data.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    // Configure server address structure
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    // Bind the socket to the address and port
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return -1;
    }
    std::cout << "Listening on 127.0.0.1:8080" << std::endl;

    // Accept a client connection
    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        return -1;
    }

    // Receive data from the client
    char buffer[4096];
    int bytesReceived = recv(clientSocket, buffer, 4096, 0);
    if (bytesReceived < 0) {
        std::cerr << "Failed to receive data" << std::endl;
        return -1;
    }
    std::cout << "Received: " << std::string(buffer, 0, bytesReceived) << std::endl;

    // Close the client and server sockets
    close(clientSocket);
    close(serverSocket);
    return 0;
}
```

#### Expected Output

```
Listening on 127.0.0.1:8080
Received: [data from client]
```

#### How to Run

```sh
g++ receive_data.cpp -o receive_data
./receive_data
```

### 6. Sending Data

#### Code

```cpp
// send_data.cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }

    // Configure server address structure
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    // Bind the socket to the address and port
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return -1;
    }
    std::cout << "Listening on 

127.0.0.1:8080" << std::endl;

    // Accept a client connection
    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        return -1;
    }

    // Send data to the client
    std::string message = "Hello from server";
    int bytesSent = send(clientSocket, message.c_str(), message.size(), 0);
    if (bytesSent < 0) {
        std::cerr << "Failed to send data" << std::endl;
        return -1;
    }
    std::cout << "Data sent to client" << std::endl;

    // Close the client and server sockets
    close(clientSocket);
    close(serverSocket);
    return 0;
}
```

#### Expected Output

```
Listening on 127.0.0.1:8080
Data sent to client
```

#### How to Run

```sh
g++ send_data.cpp -o send_data
./send_data
```

### 7. Reading a File

This example shows how to read a file's content into a string using `std::ifstream`.

#### Code

```cpp
// read_file.cpp
#include <iostream>
#include <fstream>
#include <sstream>

std::string readFile(const std::string& filePath) {
    // Open the file
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return "";
    }

    // Read the file's content into a stringstream
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

int main() {
    // Read the content of the file "public/index.html"
    std::string content = readFile("public/index.html");
    // Print the content
    std::cout << content << std::endl;
    return 0;
}
```

#### Expected Output

```
[Content of public/index.html]
```

#### How to Run

```sh
g++ read_file.cpp -o read_file
./read_file
```

### 8. Parsing an HTTP Request

This example shows how to parse an HTTP request.

#### Code

```cpp
// parse_http_request.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <map>

struct HttpRequest {
    std::string method;
    std::string path;
    std::string version;
    std::map<std::string, std::string> headers;
};

HttpRequest parseRequest(const std::string& request) {
    std::istringstream stream(request);
    HttpRequest req;
    std::string line;

    // Parse the request line
    std::getline(stream, line);
    std::istringstream lineStream(line);
    lineStream >> req.method >> req.path >> req.version;

    // Parse the headers
    while (std::getline(stream, line) && line != "\r") {
        std::istringstream headerStream(line);
        std::string key;
        std::string value;
        std::getline(headerStream, key, ':');
        std::getline(headerStream, value);
        if (!key.empty() && !value.empty()) {
            req.headers[key] = value;
        }
    }

    return req;
}

int main() {
    // Sample raw HTTP request
    std::string rawRequest = "GET / HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\n\r\n";
    // Parse the HTTP request
    HttpRequest request = parseRequest(rawRequest);

    // Print the parsed request
    std::cout << "Method: " << request.method << std::endl;
    std::cout << "Path: " << request.path << std::endl;
    std::cout << "Version: " << request.version << std::endl;
    for (const auto& header : request.headers) {
        std::cout << "Header: " << header.first << " = " << header.second << std::endl;
    }

    return 0;
}
```

#### Expected Output

```
Method: GET
Path: /
Version: HTTP/1.1
Header: Host = 127.0.0.1
Header: Connection = close
```

#### How to Run

```sh
g++ parse_http_request.cpp -o parse_http_request
./parse_http_request
```

By running these individual programs, you will gain a deeper understanding of how each component works in the context of a C++ web server.
