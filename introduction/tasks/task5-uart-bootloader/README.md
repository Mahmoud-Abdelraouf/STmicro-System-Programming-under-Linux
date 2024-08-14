Thank you for the clarification. I'll ensure that the README reflects the use of STM32F103C8's UART and Flash driver on the receiver side. Here's the updated README:

---

# UART Bootloader for STM32F103C8 Using RDT Version 3.0 with Finite State Machine (FSM)

## Overview

This project implements a UART bootloader for the STM32F103C8 microcontroller using principles from RDT (Reliable Data Transfer) version 3.0. The bootloader facilitates reliable firmware transfer from a computer to the microcontroller over a UART connection. The implementation is written in C++ and follows Object-Oriented Programming (OOP) principles. The project is enhanced with a Finite State Machine (FSM) to better manage the states during the bootloading process on both the sender and receiver sides.

### Key Features:
- **Finite State Machine (FSM)**: Manages various states during the bootloading process, ensuring smooth transitions and improved error handling.
- **Intel HEX Parsing**: The sender parses Intel HEX files to extract binary firmware data.
- **Packet Segmentation**: The firmware is broken into smaller packets for transmission.
- **Sequencing**: Each packet is numbered so the receiver can reorder them if needed.
- **Acknowledgment (ACK)**: The receiver sends an acknowledgment back to the sender after receiving each packet.
- **Retransmission**: The sender retransmits a packet if an acknowledgment is not received within a certain timeout.
- **Flow Control**: Data is sent at a rate that the receiver can handle to prevent buffer overflows.
- **Error Handling**: Checksums are used to ensure data integrity.
- **STM32F103C8 Integration**: The receiver side uses the STM32F103C8's built-in UART and Flash memory drivers to handle the bootloading process.

## Project Structure

```plaintext
uart_bootloader/
├── sender/                             # Sender-side code for UART bootloader
│   ├── src/                            # Source files for the sender
│   │   ├── main.cpp                    # Main entry point for the sender application
│   │   ├── RDTProtocol.cpp             # RDT protocol implementation for sender
│   │   ├── Packet.cpp                  # Packet segmentation and assembly implementation
│   │   ├── UARTSender.cpp              # UART communication class implementation for sender
│   │   ├── HexParser.cpp               # HEX file parser implementation
│   ├── include/                        # Header files for the sender
│   │   ├── RDTProtocol.hpp             # RDT protocol header for sender
│   │   ├── Packet.hpp                  # Packet header for sender
│   │   ├── UARTSender.hpp              # UART communication class header for sender
│   │   ├── HexParser.hpp               # HEX file parser header
│   │   ├── FiniteStateMachine.hpp      # FSM implementation shared by both sender and receiver
│   │   ├── Utils.hpp                   # Utility functions and shared constants
│   ├── build/                          # Build files for the sender (object files, etc.)
│   ├── bin/                            # Binary files for the sender (executables)
│   │   ├── uart_bootloader_sender      # Compiled sender executable
│   ├── Makefile                        # Makefile for building the sender application
├── receiver/                           # Receiver-side code for UART bootloader
│   ├── src/                            # Source files for the receiver
│   │   ├── main.cpp                    # Main entry point for the receiver application
│   │   ├── RDTProtocol.cpp             # RDT protocol implementation for receiver
│   │   ├── Packet.cpp                  # Packet segmentation and assembly implementation
│   │   ├── UARTReceiver.cpp            # UART communication class implementation using STM32F103C8 UART
│   │   ├── FlashMemory.cpp             # Flash memory handling implementation using STM32F103C8 Flash driver
│   ├── include/                        # Header files for the receiver
│   │   ├── RDTProtocol.hpp             # RDT protocol header for receiver
│   │   ├── Packet.hpp                  # Packet header for receiver
│   │   ├── UARTReceiver.hpp            # UART communication class header for receiver
│   │   ├── FlashMemory.hpp             # Flash memory handling header
│   │   ├── FiniteStateMachine.hpp      # FSM implementation shared by both sender and receiver
│   │   ├── Utils.hpp                   # Utility functions and shared constants
│   ├── build/                          # Build files for the receiver (object files, etc.)
│   ├── bin/                            # Binary files for the receiver (executables)
```

---

## Sender Side

### `main.cpp`

The main entry point for the sender application. This file initializes the UART connection, sets up the FSM, and starts the firmware sending process.

```cpp
#include "RDTProtocol.hpp"
#include "UARTSender.hpp"
#include "HexParser.hpp"
#include "FiniteStateMachine.hpp"

int main() {
    UARTSender uart("/dev/ttyUSB0", 115200); // Adjust to your UART port and baud rate
    FiniteStateMachine<SenderState> fsm(SenderState::Idle);
    RDTProtocol protocol(&uart, fsm);

    protocol.start();

    return 0;
}
```

### `RDTProtocol.hpp`

This header file defines the `RDTProtocol` class for the sender. It manages the transmission of firmware over UART using the RDT protocol and handles transitions between FSM states.

```cpp
#pragma once
#include "UARTSender.hpp"
#include "Packet.hpp"
#include "FiniteStateMachine.hpp"
#include <vector>
#include <cstdint>
#include <chrono>

class RDTProtocol {
public:
    RDTProtocol(UARTSender* uart, FiniteStateMachine<SenderState>& fsm);
    void start();                  // Starts the bootloader process
    bool sendFirmware();           // Sends the firmware data

private:
    UARTSender* uart;
    FiniteStateMachine<SenderState>& fsm;
    std::vector<uint8_t> firmware;

    bool sendPacket(const Packet& packet);  // Sends a packet over UART
    bool receiveAck(uint16_t sequenceNumber);  // Receives acknowledgment from the receiver
    bool waitForAck(uint16_t sequenceNumber);  // Waits for an acknowledgment
    bool parseHexFile();                   // Parses the Intel HEX file
    const int maxRetries = 5;              // Maximum number of retries for sending a packet
    const std::chrono::milliseconds ackTimeout = std::chrono::milliseconds(1000); // 1-second timeout for ACK
};
```

### `RDTProtocol.cpp`

This source file implements the `RDTProtocol` class for the sender, handling the logic for sending the firmware, managing retries, and transitioning between FSM states.

```cpp
#include "RDTProtocol.hpp"
#include <iostream>
#include <thread>
#include "HexParser.hpp"

RDTProtocol::RDTProtocol(UARTSender* uart, FiniteStateMachine<SenderState>& fsm)
    : uart(uart), fsm(fsm) {}

void RDTProtocol::start() {
    fsm.transitionTo(SenderState::Parsing);
    if (!parseHexFile()) {
        fsm.transitionTo(SenderState::Error);
        return;
    }
    fsm.transitionTo(SenderState::Sending);
    sendFirmware();
}

bool RDTProtocol::parseHexFile() {
    HexParser parser("path_to_your_file.hex"); // Provide the actual path to your HEX file
    firmware = parser.parse();
    return !firmware.empty();
}

bool RDTProtocol::sendFirmware() {
    uint16_t sequenceNumber = 0;
    size_t packetSize = 256; // Adjust packet size as necessary
    for (size_t offset = 0; offset < firmware.size(); offset += packetSize) {
        fsm.transitionTo(SenderState::Sending);
        std::vector<uint8_t> packetData(firmware.begin() + offset, firmware.begin() + std::min(offset + packetSize, firmware.end()));
        Packet packet(sequenceNumber++, packetData);
        if (!sendPacket(packet)) {
            fsm.transitionTo(SenderState::Error);
            return false;
        }
        fsm.transitionTo(SenderState::WaitingForAck);
    }
    fsm.transitionTo(SenderState::Completed);
    return true;
}

bool RDTProtocol::sendPacket(const Packet& packet) {
    for (int attempt = 0; attempt < maxRetries; ++attempt) {
        if (uart->sendBytes(packet.serialize())) {
            if (waitForAck(packet.getSequenceNumber())) {
                return true;
            }
        }
        std::cerr << "Retrying packet with sequence number: " << packet.getSequenceNumber() << std::endl;
    }
    return false;
}

bool RDTProtocol::waitForAck(uint16_t sequenceNumber) {
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < ackTimeout) {
        uint16_t receivedSequence;
        if (uart->receiveAck(receivedSequence)) {
            if (receivedSequence == sequenceNumber) {
                return true;
            }
        }
    }
    return false;
}
```

### `Packet.hpp`

This header file defines the `Packet` class, which handles the segmentation of firmware data into packets for transmission.

```cpp
#pragma once
#include <vector>
#include <cstdint>

class Packet {
public:
    Packet(uint16_t sequenceNumber, const std::vector<uint8_t>& data);
    std::vector<uint8_t>

 serialize() const;  // Serializes the packet for transmission
    static Packet deserialize(const std::vector<uint8_t>& data);  // Deserializes received data into a packet

    uint16_t getSequenceNumber() const;  // Returns the packet's sequence number
    const std::vector<uint8_t>& getData() const;  // Returns the packet's data

private:
    uint16_t sequenceNumber;
    std::vector<uint8_t> data;
};
```

### `Packet.cpp`

This source file implements the `Packet` class, providing methods for packet serialization, deserialization, and accessing packet data.

```cpp
#include "Packet.hpp"
#include <cstring>

Packet::Packet(uint16_t sequenceNumber, const std::vector<uint8_t>& data)
    : sequenceNumber(sequenceNumber), data(data) {}

std::vector<uint8_t> Packet::serialize() const {
    std::vector<uint8_t> serializedData;
    serializedData.push_back(sequenceNumber >> 8);  // High byte of sequence number
    serializedData.push_back(sequenceNumber & 0xFF); // Low byte of sequence number
    serializedData.insert(serializedData.end(), data.begin(), data.end());

    return serializedData;
}

Packet Packet::deserialize(const std::vector<uint8_t>& data) {
    uint16_t sequenceNumber = (data[0] << 8) | data[1];
    std::vector<uint8_t> packetData(data.begin() + 2, data.end());

    return Packet(sequenceNumber, packetData);
}

uint16_t Packet::getSequenceNumber() const {
    return sequenceNumber;
}

const std::vector<uint8_t>& Packet::getData() const {
    return data;
}
```

### `UARTSender.hpp`

This header file defines the `UARTSender` class, which manages UART communication for the sender side.

```cpp
#pragma once
#include <string>
#include <vector>
#include <cstdint>

class UARTSender {
public:
    UARTSender(const std::string& portName, int baudRate);
    bool sendBytes(const std::vector<uint8_t>& data);  // Sends data over UART
    bool receiveAck(uint16_t& sequenceNumber);  // Receives an acknowledgment from the receiver

private:
    int uartFd;  // File descriptor for the UART connection

    void configurePort(int baudRate);  // Configures the UART port
};
```

### `UARTSender.cpp`

This source file implements the `UARTSender` class, handling the low-level UART communication.

```cpp
#include "UARTSender.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>

UARTSender::UARTSender(const std::string& portName, int baudRate) {
    uartFd = open(portName.c_str(), O_RDWR | O_NOCTTY);
    if (uartFd == -1) {
        std::cerr << "Error opening UART: " << strerror(errno) << std::endl;
        return;
    }
    configurePort(baudRate);
}

void UARTSender::configurePort(int baudRate) {
    struct termios options;
    tcgetattr(uartFd, &options);
    cfsetispeed(&options, baudRate);
    cfsetospeed(&options, baudRate);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CRTSCTS;
    tcsetattr(uartFd, TCSANOW, &options);
}

bool UARTSender::sendBytes(const std::vector<uint8_t>& data) {
    if (write(uartFd, data.data(), data.size()) != data.size()) {
        std::cerr << "Failed to send data over UART" << std::endl;
        return false;
    }
    return true;
}

bool UARTSender::receiveAck(uint16_t& sequenceNumber) {
    uint8_t ack[2];
    int bytesRead = read(uartFd, ack, sizeof(ack));
    if (bytesRead == 2) {
        sequenceNumber = (ack[0] << 8) | ack[1];
        return true;
    }
    return false;
}
```

### `HexParser.hpp`

This header file defines the `HexParser` class, which parses Intel HEX files to extract binary firmware data.

```cpp
#pragma once
#include <vector>
#include <string>

class HexParser {
public:
    HexParser(const std::string& filePath);
    std::vector<uint8_t> parse();  // Parses the HEX file and returns binary data

private:
    std::string filePath;
    std::vector<uint8_t> parseLine(const std::string& line);  // Parses a single line of the HEX file
};
```

### `HexParser.cpp`

This source file implements the `HexParser` class, providing methods to parse the Intel HEX file format.

```cpp
#include "HexParser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

HexParser::HexParser(const std::string& filePath) : filePath(filePath) {}

std::vector<uint8_t> HexParser::parse() {
    std::ifstream file(filePath);
    std::string line;
    std::vector<uint8_t> data;

    while (std::getline(file, line)) {
        auto parsedLine = parseLine(line);
        data.insert(data.end(), parsedLine.begin(), parsedLine.end());
    }

    return data;
}

std::vector<uint8_t> HexParser::parseLine(const std::string& line) {
    std::vector<uint8_t> result;

    if (line[0] != ':') return result;

    size_t byteCount = std::stoi(line.substr(1, 2), nullptr, 16);
    uint32_t address = std::stoi(line.substr(3, 4), nullptr, 16);
    uint8_t recordType = std::stoi(line.substr(7, 2), nullptr, 16);

    if (recordType == 0x00) { // Data record
        for (size_t i = 0; i < byteCount; ++i) {
            result.push_back(std::stoi(line.substr(9 + i * 2, 2), nullptr, 16));
        }
    } else if (recordType == 0x01) { // End of file record
        // Handle EOF if necessary
    }

    return result;
}
```

### `FiniteStateMachine.hpp`

This header file defines a simple Finite State Machine (FSM) template that is used on both the sender and receiver sides to manage the various states of the bootloader process.

```cpp
#pragma once
#include <functional>
#include <unordered_map>

template <typename State>
class FiniteStateMachine {
public:
    using Action = std::function<void()>;

    FiniteStateMachine(State initialState) : currentState(initialState) {}

    void addTransition(State from, State to, Action action) {
        transitions[{from, to}] = action;
    }

    void transitionTo(State newState) {
        auto it = transitions.find({currentState, newState});
        if (it != transitions.end()) {
            it->second();  // Perform the action associated with the transition
            currentState = newState;
        } else {
            // Handle invalid transition
        }
    }

    State getCurrentState() const {
        return currentState;
    }

private:
    State currentState;
    std::unordered_map<std::pair<State, State>, Action> transitions;
};
```

### `Makefile`

This Makefile is used to compile the sender application on your computer.

```Makefile
# Makefile for UART Bootloader Sender

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
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/RDTProtocol.cpp $(SRC_DIR)/Packet.cpp $(SRC_DIR)/UARTSender.cpp $(SRC_DIR)/HexParser.cpp

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Output executable
TARGET = $(BIN_DIR)/uart_bootloader_sender

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

---

## Receiver Side

### `main.cpp`

The main entry point for the receiver application. This file initializes the UART connection, sets up the FSM, and starts the firmware receiving process.

```cpp
#include "RDTProtocol.hpp"
#include "UARTReceiver.hpp"
#include "FlashMemory.hpp"
#include "FiniteStateMachine.hpp"

int main() {
    UARTReceiver uart(115200); // Adjust to your UART port and baud rate
    FiniteStateMachine<ReceiverState> fsm(ReceiverState::Idle);
    RDTProtocol protocol(&uart, fsm);

    protocol.receiveFirmware();

    return 0

;
}
```

### `RDTProtocol.hpp`

This header file defines the `RDTProtocol` class for the receiver. It manages the reception of firmware over UART using the RDT protocol and handles transitions between FSM states.

```cpp
#pragma once
#include "UARTReceiver.hpp"
#include "Packet.hpp"
#include "FiniteStateMachine.hpp"
#include <vector>
#include <cstdint>
#include <map>

class RDTProtocol {
public:
    RDTProtocol(UARTReceiver* uart, FiniteStateMachine<ReceiverState>& fsm);
    bool receiveFirmware();        // Receives the firmware data

private:
    UARTReceiver* uart;
    FiniteStateMachine<ReceiverState>& fsm;
    std::map<uint16_t, Packet> packetBuffer;

    bool processPacket(const Packet& packet); // Processes a received packet
    bool sendAck(uint16_t sequenceNumber);    // Sends an acknowledgment back to the sender
};
```

### `RDTProtocol.cpp`

This source file implements the `RDTProtocol` class for the receiver, handling the logic for receiving the firmware, processing packets, and transitioning between FSM states.

```cpp
#include "RDTProtocol.hpp"
#include <iostream>
#include "FlashMemory.hpp"

RDTProtocol::RDTProtocol(UARTReceiver* uart, FiniteStateMachine<ReceiverState>& fsm)
    : uart(uart), fsm(fsm) {}

bool RDTProtocol::receiveFirmware() {
    Packet packet;
    fsm.transitionTo(ReceiverState::Receiving);
    while (uart->receivePacket(packet)) {
        if (!processPacket(packet)) {
            fsm.transitionTo(ReceiverState::Error);
            return false;
        }
        fsm.transitionTo(ReceiverState::Writing);
        if (!FlashMemory::writeData(packet.getData())) {
            fsm.transitionTo(ReceiverState::Error);
            return false;
        }
        fsm.transitionTo(ReceiverState::Receiving);
    }
    fsm.transitionTo(ReceiverState::Completed);
    return true;
}

bool RDTProtocol::processPacket(const Packet& packet) {
    uint16_t sequenceNumber = packet.getSequenceNumber();
    packetBuffer[sequenceNumber] = packet;
    return sendAck(sequenceNumber);
}

bool RDTProtocol::sendAck(uint16_t sequenceNumber) {
    std::vector<uint8_t> ack = { static_cast<uint8_t>(sequenceNumber >> 8), static_cast<uint8_t>(sequenceNumber & 0xFF) };
    return uart->sendBytes(ack);
}
```

### `Packet.hpp`

This header file defines the `Packet` class, which is shared between the sender and receiver. It handles the segmentation and reassembly of firmware data into packets.

```cpp
#pragma once
#include <vector>
#include <cstdint>

class Packet {
public:
    Packet(uint16_t sequenceNumber, const std::vector<uint8_t>& data);
    std::vector<uint8_t> serialize() const;  // Serializes the packet for transmission
    static Packet deserialize(const std::vector<uint8_t>& data);  // Deserializes received data into a packet

    uint16_t getSequenceNumber() const;  // Returns the packet's sequence number
    const std::vector<uint8_t>& getData() const;  // Returns the packet's data

private:
    uint16_t sequenceNumber;
    std::vector<uint8_t> data;
};
```

### `Packet.cpp`

This source file implements the `Packet` class, providing methods for packet serialization, deserialization, and accessing packet data.

```cpp
#include "Packet.hpp"
#include <cstring>

Packet::Packet(uint16_t sequenceNumber, const std::vector<uint8_t>& data)
    : sequenceNumber(sequenceNumber), data(data) {}

std::vector<uint8_t> Packet::serialize() const {
    std::vector<uint8_t> serializedData;
    serializedData.push_back(sequenceNumber >> 8);  // High byte of sequence number
    serializedData.push_back(sequenceNumber & 0xFF); // Low byte of sequence number
    serializedData.insert(serializedData.end(), data.begin(), data.end());

    return serializedData;
}

Packet Packet::deserialize(const std::vector<uint8_t>& data) {
    uint16_t sequenceNumber = (data[0] << 8) | data[1];
    std::vector<uint8_t> packetData(data.begin() + 2, data.end());

    return Packet(sequenceNumber, packetData);
}

uint16_t Packet::getSequenceNumber() const {
    return sequenceNumber;
}

const std::vector<uint8_t>& Packet::getData() const {
    return data;
}
```

### `UARTReceiver.hpp`

This header file defines the `UARTReceiver` class, which manages UART communication for the receiver side using the STM32F103C8's built-in UART hardware.

```cpp
#pragma once
#include <string>
#include <vector>
#include <cstdint>

class UARTReceiver {
public:
    UARTReceiver(int baudRate);
    bool receivePacket(Packet& packet);  // Receives a packet over UART
    bool sendBytes(const std::vector<uint8_t>& data);  // Sends acknowledgment over UART

private:
    int uartFd;  // File descriptor for the UART connection

    void configurePort(int baudRate);  // Configures the UART port
};
```

### `UARTReceiver.cpp`

This source file implements the `UARTReceiver` class, handling the low-level UART communication using the STM32F103C8's UART.

```cpp
#include "UARTReceiver.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>

UARTReceiver::UARTReceiver(int baudRate) {
    uartFd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
    if (uartFd == -1) {
        std::cerr << "Error opening UART: " << strerror(errno) << std::endl;
        return;
    }
    configurePort(baudRate);
}

void UARTReceiver::configurePort(int baudRate) {
    struct termios options;
    tcgetattr(uartFd, &options);
    cfsetispeed(&options, baudRate);
    cfsetospeed(&options, baudRate);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CRTSCTS;
    tcsetattr(uartFd, TCSANOW, &options);
}

bool UARTReceiver::receivePacket(Packet& packet) {
    uint8_t buffer[256 + 2];  // Max packet size + 2 bytes for sequence number
    int bytesRead = read(uartFd, buffer, sizeof(buffer));
    if (bytesRead >= 2) {
        packet = Packet::deserialize(std::vector<uint8_t>(buffer, buffer + bytesRead));
        return true;
    }
    return false;
}

bool UARTReceiver::sendBytes(const std::vector<uint8_t>& data) {
    if (write(uartFd, data.data(), data.size()) != data.size()) {
        std::cerr << "Failed to send acknowledgment over UART" << std::endl;
        return false;
    }
    return true;
}
```

### `FlashMemory.hpp`

This header file defines the `FlashMemory` class, which handles writing received firmware data to the STM32F103C8's flash memory using the microcontroller's built-in Flash driver.

```cpp
#pragma once
#include <vector>
#include <cstdint>

class FlashMemory {
public:
    FlashMemory();
    static bool writeData(const std::vector<uint8_t>& data);  // Writes data to flash memory

private:
    static void unlockFlash();  // Unlocks the flash memory for writing
    static void lockFlash();    // Locks the flash memory after writing
    static bool eraseSector(uint32_t address);  // Erases a flash memory sector
    static bool programWord(uint32_t address, uint32_t data);  // Programs a word in flash memory
};
```

### `FlashMemory.cpp`

This source file implements the `FlashMemory` class, providing methods to unlock, erase, program, and lock the STM32F103C8's flash memory.

```cpp
#include "FlashMemory.hpp"
#include <iostream>
#include "stm32f1xx_hal.h"  // Adjust the HAL include as per your project setup

FlashMemory::FlashMemory() {
    unlockFlash();
}

void FlashMemory::unlockFlash() {
    HAL_FLASH_Unlock(); // Provided by STM32 HAL libraries
}

void FlashMemory::lockFlash() {
    HAL_FLASH_Lock(); // Provided by STM32 HAL libraries
}

bool FlashMemory::eraseSector(uint32_t address) {
    FLASH_EraseInitTypeDef eraseInitStruct;
    uint32_t pageError = 0;

    eraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    eraseInitStruct.PageAddress = address;
    eraseInitStruct.NbPages = 1;

    if (HAL_FLASHEx_Erase(&eraseInitStruct, &pageError) != HAL_OK) {
        return false;
    }
    return true;
}

bool FlashMemory::programWord(uint32_t address, uint32_t data) {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, data) != HAL_OK) {
        return false;
    }
    return true;
}

bool FlashMemory::writeData(const std::vector<uint8_t>& data) {
    uint32_t address = 0x08000000; // Start address of flash memory
    for (size_t i = 0; i < data.size

(); i += 4) {
        uint32_t word = data[i] | (data[i + 1] << 8) | (data[i + 2] << 16) | (data[i + 3] << 24);
        if (!programWord(address, word)) {
            return false;
        }
        address += 4;
    }
    lockFlash();
    return true;
}
```

### `FiniteStateMachine.hpp`

This header file, shared between the sender and receiver, defines a simple Finite State Machine (FSM) template that manages the various states of the bootloader process.

```cpp
#pragma once
#include <functional>
#include <unordered_map>

template <typename State>
class FiniteStateMachine {
public:
    using Action = std::function<void()>;

    FiniteStateMachine(State initialState) : currentState(initialState) {}

    void addTransition(State from, State to, Action action) {
        transitions[{from, to}] = action;
    }

    void transitionTo(State newState) {
        auto it = transitions.find({currentState, newState});
        if (it != transitions.end()) {
            it->second();  // Perform the action associated with the transition
            currentState = newState;
        } else {
            // Handle invalid transition
        }
    }

    State getCurrentState() const {
        return currentState;
    }

private:
    State currentState;
    std::unordered_map<std::pair<State, State>, Action> transitions;
};
```

### `Makefile`

This Makefile is used to compile the receiver application on your computer, utilizing the ARM toolchain for STM32.

```Makefile
# Makefile for UART Bootloader Receiver

# Compiler
CXX = arm-none-eabi-g++  # Assuming a cross-compiler for STM32

# Compiler flags
CXXFLAGS = -Wall -std=c++11 -Iinclude

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include

# Source files
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/RDTProtocol.cpp $(SRC_DIR)/Packet.cpp $(SRC_DIR)/UARTReceiver.cpp $(SRC_DIR)/FlashMemory.cpp

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Output executable
TARGET = $(BIN_DIR)/uart_bootloader_receiver

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

---

## Usage

### Building the Project

1. **Clone the Repository**:
   ```bash
   git clone <repository_url>
   cd uart_bootloader
   ```

2. **Build the Sender**:
   Navigate to the `sender` directory and build the application using the provided `Makefile`.
   ```bash
   cd sender
   make
   ```
   This will compile the sender code and create an executable named `uart_bootloader_sender`.

3. **Build the Receiver**:
   The receiver code should be compiled using a cross-compiler appropriate for the STM32F103C8 microcontroller, such as `arm-none-eabi-gcc`. Follow your specific toolchain instructions to build and flash the receiver firmware to the microcontroller.

### Running the Bootloader

1. **Connect the Computer to the Microcontroller**:
   Use a USB-to-UART adapter or any other appropriate method to establish a UART connection between your computer and the microcontroller.

2. **Execute the Sender Application**:
   Run the sender application on your computer to start the firmware transfer.
   ```bash
   ./uart_bootloader_sender
   ```

3. **Monitor the Receiver**:
   The microcontroller will receive the firmware via UART, write it to flash memory, and send acknowledgments back to the sender.

4. **Verify the Firmware**:
   Once the process is complete, you should verify that the firmware was successfully written and that the microcontroller is running the new firmware.

### Testing

To test the bootloader:

1. **Simulate Packet Loss**:
   You can modify the sender or receiver code to simulate packet loss by randomly dropping packets. This will help you verify the reliability and retransmission features.

2. **Test with Different File Sizes**:
   Test the bootloader with various firmware sizes to ensure that it handles large and small files correctly.

3. **Check Error Handling**:
   Introduce errors in the data (e.g., corrupted packets) and verify that the bootloader correctly detects and handles these errors.

## Conclusion

This UART bootloader project provides a robust and reliable method for transferring firmware to an STM32F103C8 microcontroller using UART and RDT protocol version 3.0 principles. By incorporating a Finite State Machine (FSM), the project ensures better management of states, smoother transitions, and enhanced error handling. This makes the bootloader more modular, scalable, and easier to maintain.
