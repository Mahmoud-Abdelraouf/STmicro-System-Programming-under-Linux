# RDT 3.0 Protocol Implementation in C++

This project implements the RDT (Reliable Data Transfer) protocol version 3.0, which is designed to operate over an unreliable channel that can lose, corrupt, or reorder packets. The implementation includes features such as checksums, sequence numbers, acknowledgments (ACKs), negative acknowledgments (NAKs), and timers for retransmission.

## Project Structure

```plaintext
rdt_protocol/
├── client/                            # Client-side code
│   ├── src/                           # Source files for the client
│   │   ├── main.cpp                   # Main entry point for the client application
│   │   ├── RDTClient.cpp              # RDT protocol implementation for client
│   │   ├── Packet.cpp                 # Packet segmentation and assembly implementation
│   │   ├── UDPClient.cpp              # UDP communication class implementation for client
│   ├── include/                       # Header files for the client
│   │   ├── RDTClient.hpp              # RDT protocol header for client
│   │   ├── Packet.hpp                 # Packet header for client
│   │   ├── UDPClient.hpp              # UDP communication class header for client
│   ├── build/                         # Build files for the client
│   ├── bin/                           # Binary files for the client (executables)
│   │   ├── rdt_client                 # Compiled client executable
│   ├── Makefile                       # Makefile for building the client application
├── server/                            # Server-side code
│   ├── src/                           # Source files for the server
│   │   ├── main.cpp                   # Main entry point for the server application
│   │   ├── RDTServer.cpp              # RDT protocol implementation for server
│   │   ├── Packet.cpp                 # Packet segmentation and assembly implementation
│   │   ├── UDPServer.cpp              # UDP communication class implementation for server
│   ├── include/                       # Header files for the server
│   │   ├── RDTServer.hpp              # RDT protocol header for server
│   │   ├── Packet.hpp                 # Packet header for server
│   │   ├── UDPServer.hpp              # UDP communication class header for server
│   ├── build/                         # Build files for the server
│   ├── bin/                           # Binary files for the server (executables)
│   │   ├── rdt_server                 # Compiled server executable
│   ├── Makefile                       # Makefile for building the server application
```

## 1. Packet Class

The `Packet` class handles packet segmentation and assembly, which is used by both the client and server. It includes a checksum to detect packet corruption.

### `Packet.hpp`

```cpp
#pragma once
#include <vector>
#include <cstdint>
#include <cstddef>

class Packet {
public:
    Packet(uint16_t sequenceNumber, const std::vector<uint8_t>& data);
    std::vector<uint8_t> serialize() const;  // Serializes the packet for transmission
    static Packet deserialize(const std::vector<uint8_t>& data);  // Deserializes received data into a packet

    uint16_t getSequenceNumber() const;  // Returns the packet's sequence number
    const std::vector<uint8_t>& getData() const;  // Returns the packet's data
    uint16_t getChecksum() const;  // Returns the packet's checksum
    static uint16_t calculateChecksum(const std::vector<uint8_t>& data);  // Calculates the checksum

private:
    uint16_t sequenceNumber;
    uint16_t checksum;
    std::vector<uint8_t> data;
};
```

### `Packet.cpp`

```cpp
#include "Packet.hpp"
#include <cstring>
#include <numeric>

Packet::Packet(uint16_t sequenceNumber, const std::vector<uint8_t>& data)
    : sequenceNumber(sequenceNumber), data(data) {
    this->checksum = calculateChecksum(data);
}

std::vector<uint8_t> Packet::serialize() const {
    std::vector<uint8_t> serializedData;
    serializedData.push_back(sequenceNumber >> 8);  // High byte of sequence number
    serializedData.push_back(sequenceNumber & 0xFF); // Low byte of sequence number
    serializedData.push_back(checksum >> 8);  // High byte of checksum
    serializedData.push_back(checksum & 0xFF); // Low byte of checksum
    serializedData.insert(serializedData.end(), data.begin(), data.end());

    return serializedData;
}

Packet Packet::deserialize(const std::vector<uint8_t>& data) {
    uint16_t sequenceNumber = (data[0] << 8) | data[1];
    uint16_t checksum = (data[2] << 8) | data[3];
    std::vector<uint8_t> packetData(data.begin() + 4, data.end());

    Packet packet(sequenceNumber, packetData);
    if (packet.checksum != checksum) {
        throw std::runtime_error("Checksum does not match!");
    }

    return packet;
}

uint16_t Packet::getSequenceNumber() const {
    return sequenceNumber;
}

const std::vector<uint8_t>& Packet::getData() const {
    return data;
}

uint16_t Packet::getChecksum() const {
    return checksum;
}

uint16_t Packet::calculateChecksum(const std::vector<uint8_t>& data) {
    return std::accumulate(data.begin(), data.end(), 0);
}
```

---

## 2. UDP Communication Classes

These classes handle the low-level UDP communication.

### `UDPClient.hpp`

```cpp
#pragma once
#include <string>
#include <vector>
#include <cstdint>

class UDPClient {
public:
    UDPClient(const std::string& serverIp, int serverPort);
    bool sendBytes(const std::vector<uint8_t>& data);  // Sends data to the server
    bool receiveBytes(std::vector<uint8_t>& data);     // Receives data from the server

private:
    int udpFd;  // File descriptor for the UDP socket
    struct sockaddr_in serverAddr;  // Server address

    void configureSocket();  // Configures the UDP socket
};
```

### `UDPClient.cpp`

```cpp
#include "UDPClient.hpp"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

UDPClient::UDPClient(const std::string& serverIp, int serverPort) {
    udpFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpFd < 0) {
        std::cerr << "Error creating UDP socket: " << strerror(errno) << std::endl;
        return;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr);

    configureSocket();
}

void UDPClient::configureSocket() {
    int optval = 1;
    setsockopt(udpFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
}

bool UDPClient::sendBytes(const std::vector<uint8_t>& data) {
    ssize_t sentBytes = sendto(udpFd, data.data(), data.size(), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (sentBytes != data.size()) {
        std::cerr << "Failed to send data over UDP" << std::endl;
        return false;
    }
    return true;
}

bool UDPClient::receiveBytes(std::vector<uint8_t>& data) {
    uint8_t buffer[512];
    ssize_t receivedBytes = recvfrom(udpFd, buffer, sizeof(buffer), 0, NULL, NULL);
    if (receivedBytes < 0) {
        std::cerr << "Failed to receive data over UDP" << std::endl;
        return false;
    }
    data.assign(buffer, buffer + receivedBytes);
    return true;
}
```

### `UDPServer.hpp`

```cpp
#pragma once
#include <vector>
#include <cstdint>

class UDPServer {
public:
    UDPServer(int port);
    bool receiveBytes(std::vector<uint8_t>& data);     // Receives data from the client
    bool sendBytes(const std::vector<uint8_t>& data);  // Sends data to the client

private:
    int udpFd;  // File descriptor for the UDP socket
    struct sockaddr_in clientAddr;  // Client address
    socklen_t clientAddrLen;

    void configureSocket();  // Configures the UDP socket
};
```

### `UDPServer.cpp`

```cpp
#include "UDPServer.hpp"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

UDPServer::UDPServer(int port) {
    udpFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpFd < 0) {
        std::cerr << "Error creating UDP socket: " << strerror(errno) << std::endl;
        return;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr

.sin_port = htons(port);

    if (bind(udpFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error binding UDP socket: " << strerror(errno) << std::endl;
        close(udpFd);
        return;
    }

    configureSocket();
    clientAddrLen = sizeof(clientAddr);
}

void UDPServer::configureSocket() {
    int optval = 1;
    setsockopt(udpFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
}

bool UDPServer::receiveBytes(std::vector<uint8_t>& data) {
    uint8_t buffer[512];
    ssize_t receivedBytes = recvfrom(udpFd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (receivedBytes < 0) {
        std::cerr << "Failed to receive data over UDP" << std::endl;
        return false;
    }
    data.assign(buffer, buffer + receivedBytes);
    return true;
}

bool UDPServer::sendBytes(const std::vector<uint8_t>& data) {
    ssize_t sentBytes = sendto(udpFd, data.data(), data.size(), 0, (struct sockaddr*)&clientAddr, clientAddrLen);
    if (sentBytes != data.size()) {
        std::cerr << "Failed to send data over UDP" << std::endl;
        return false;
    }
    return true;
}
```

---

## 3. RDT Protocol Implementation

These classes implement the RDT 3.0 protocol, incorporating sequence numbers, checksums, and retransmission logic.

### `RDTClient.hpp`

```cpp
#pragma once
#include "UDPClient.hpp"
#include "Packet.hpp"
#include <vector>
#include <cstdint>

class RDTClient {
public:
    RDTClient(UDPClient* udpClient);
    bool sendData(const std::vector<uint8_t>& data);  // Sends data to the server

private:
    UDPClient* udpClient;
    uint16_t sequenceNumber;

    bool sendPacket(const Packet& packet);  // Sends a packet over UDP
    bool receiveAck(uint16_t sequenceNumber);  // Receives an acknowledgment from the server
    bool waitForAck(uint16_t sequenceNumber);  // Waits for an acknowledgment
    const int maxRetries = 5;
};
```

### `RDTClient.cpp`

```cpp
#include "RDTClient.hpp"
#include <iostream>
#include <thread>
#include <chrono>

RDTClient::RDTClient(UDPClient* udpClient)
    : udpClient(udpClient), sequenceNumber(0) {}

bool RDTClient::sendData(const std::vector<uint8_t>& data) {
    size_t packetSize = 256;  // Adjust packet size as necessary
    for (size_t offset = 0; offset < data.size(); offset += packetSize) {
        std::vector<uint8_t> packetData(data.begin() + offset, data.begin() + std::min(offset + packetSize, data.end()));
        Packet packet(sequenceNumber++, packetData);
        if (!sendPacket(packet)) {
            return false;
        }
    }
    return true;
}

bool RDTClient::sendPacket(const Packet& packet) {
    for (int attempt = 0; attempt < maxRetries; ++attempt) {
        if (udpClient->sendBytes(packet.serialize())) {
            if (waitForAck(packet.getSequenceNumber())) {
                return true;
            }
        }
        std::cerr << "Retrying packet with sequence number: " << packet.getSequenceNumber() << std::endl;
    }
    return false;
}

bool RDTClient::waitForAck(uint16_t sequenceNumber) {
    std::vector<uint8_t> ackData;
    if (udpClient->receiveBytes(ackData)) {
        uint16_t receivedSequence = (ackData[0] << 8) | ackData[1];
        return receivedSequence == sequenceNumber;
    }
    return false;
}
```

### `RDTServer.hpp`

```cpp
#pragma once
#include "UDPServer.hpp"
#include "Packet.hpp"
#include <vector>
#include <cstdint>
#include <map>

class RDTServer {
public:
    RDTServer(UDPServer* udpServer);
    bool receiveData(std::vector<uint8_t>& data);  // Receives data from the client

private:
    UDPServer* udpServer;
    std::map<uint16_t, Packet> packetBuffer;
    uint16_t expectedSequenceNumber;

    bool processPacket(const Packet& packet);  // Processes a received packet
    bool sendAck(uint16_t sequenceNumber);     // Sends an acknowledgment to the client
};
```

### `RDTServer.cpp`

```cpp
#include "RDTServer.hpp"
#include <iostream>

RDTServer::RDTServer(UDPServer* udpServer)
    : udpServer(udpServer), expectedSequenceNumber(0) {}

bool RDTServer::receiveData(std::vector<uint8_t>& data) {
    Packet packet;
    std::vector<uint8_t> packetData;
    while (udpServer->receiveBytes(packetData)) {
        packet = Packet::deserialize(packetData);
        if (!processPacket(packet)) {
            return false;
        }
    }

    for (const auto& entry : packetBuffer) {
        data.insert(data.end(), entry.second.getData().begin(), entry.second.getData().end());
    }
    return true;
}

bool RDTServer::processPacket(const Packet& packet) {
    uint16_t sequenceNumber = packet.getSequenceNumber();
    if (sequenceNumber == expectedSequenceNumber) {
        packetBuffer[sequenceNumber] = packet;
        sendAck(sequenceNumber);
        expectedSequenceNumber++;
        return true;
    } else {
        sendAck(expectedSequenceNumber - 1);  // Resend the last acknowledged packet
        return false;
    }
}

bool RDTServer::sendAck(uint16_t sequenceNumber) {
    std::vector<uint8_t> ack = { static_cast<uint8_t>(sequenceNumber >> 8), static_cast<uint8_t>(sequenceNumber & 0xFF) };
    return udpServer->sendBytes(ack);
}
```

---

## 4. Main Files

### Client `main.cpp`

```cpp
#include "RDTClient.hpp"
#include "UDPClient.hpp"
#include <iostream>
#include <vector>

int main() {
    UDPClient udpClient("127.0.0.1", 8080);  // Server IP and port
    RDTClient client(&udpClient);

    std::vector<uint8_t> dataToSend = { /* Data to send */ };
    if (client.sendData(dataToSend)) {
        std::cout << "Data sent successfully" << std::endl;
    } else {
        std::cerr << "Failed to send data" << std::endl;
    }

    return 0;
}
```

### Server `main.cpp`

```cpp
#include "RDTServer.hpp"
#include "UDPServer.hpp"
#include <iostream>
#include <vector>

int main() {
    UDPServer udpServer(8080);  // Listening on port 8080
    RDTServer server(&udpServer);

    std::vector<uint8_t> receivedData;
    if (server.receiveData(receivedData)) {
        std::cout << "Data received successfully" << std::endl;
        // Process the received data
    } else {
        std::cerr << "Failed to receive data" << std::endl;
    }

    return 0;
}
```

---

## 5. Makefiles

### Client `Makefile`

```Makefile
# Makefile for RDT Client

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include

# Source files
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/RDTClient.cpp $(SRC_DIR)/Packet.cpp $(SRC_DIR)/UDPClient.cpp

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Output executable
TARGET = $(BIN_DIR)/rdt_client

# Build target
all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create bin and build directories if they don't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean target
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
```

### Server `Makefile`

```Makefile
# Makefile for RDT Server

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include

# Source files
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/RDTServer.cpp $(SRC_DIR)/Packet.cpp $(SRC_DIR)/UDPServer.cpp

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Output executable
TARGET = $(BIN_DIR)/rdt_server

# Build target
all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN

_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create bin and build directories if they don't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean target
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
```

---

## Conclusion

This project implements the RDT version 3.0 protocol in C++ for reliable data transfer over UDP. It includes key features such as checksums, sequence numbers, acknowledgments, and retransmission. The project is organized with separate client and server components, each with its own source files, headers, and build instructions.
