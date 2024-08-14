# Testing the RDT 3.0 Protocol Implementation in C++

This README provides instructions on how to test the RDT (Reliable Data Transfer) protocol version 3.0, which is implemented in this project. These tests cover basic functionality, packet loss handling, network delay, large data transfers, congestion control, and end-to-end data integrity.

## 1. Basic Functionality Test

This test ensures that the client can successfully send data to the server, and that the server can receive it and send back acknowledgments.

### Steps:
1. **Run the Server**: Start the server on your machine.
   ```bash
   ./bin/rdt_server
   ```

2. **Run the Client**: Start the client on the same machine or another machine within the network.
   ```bash
   ./bin/rdt_client
   ```

3. **Check the Output**: Verify that the client sends data packets and receives ACKs, and that the server receives and acknowledges the data. The output should show no errors during the transmission.

### Expected Results:
- The client sends data packets, and the server receives them without errors.
- The server sends acknowledgments back, which the client receives successfully.

## 2. Packet Loss Simulation

This test checks how the RDT protocol handles packet loss by randomly dropping packets during transmission.

### Steps:
1. **Modify the Code**: Introduce packet loss simulation in the `UDPClient` and `UDPServer` classes by randomly dropping packets before sending them.

   Example:
   ```cpp
   bool UDPClient::sendBytes(const std::vector<uint8_t>& data) {
       if (rand() % 10 == 0) {  // Simulate 10% packet loss
           std::cerr << "Simulated packet loss." << std::endl;
           return true;  // Pretend the packet was sent
       }
       ssize_t sentBytes = sendto(udpFd, data.data(), data.size(), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
       return sentBytes == data.size();
   }
   ```

2. **Run the Server and Client**: Start the server and client as before.

3. **Monitor Retransmissions**: Check if the client correctly retransmits lost packets and if the server eventually receives all packets.

### Expected Results:
- The client detects missing ACKs and retransmits the corresponding packets.
- The server eventually receives all packets, despite simulated packet loss.

## 3. Network Delay Simulation

This test checks how the RDT protocol handles network delays by introducing artificial delays in packet transmission.

### Steps:
1. **Modify the Code**: Introduce delays in the `sendBytes` or `receiveBytes` methods in `UDPClient` and `UDPServer`.

   Example:
   ```cpp
   bool UDPClient::sendBytes(const std::vector<uint8_t>& data) {
       std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Simulate 50ms network delay
       ssize_t sentBytes = sendto(udpFd, data.data(), data.size(), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
       return sentBytes == data.size();
   }
   ```

2. **Run the Server and Client**: Start the server and client as before.

3. **Check for Timeouts and Retransmissions**: Observe if the client experiences timeouts due to delays and correctly retransmits packets. Verify if the server still successfully receives all data.

### Expected Results:
- The client handles network delays by waiting for ACKs, timing out, and retransmitting as needed.
- The server receives all packets, though with delays.

## 4. Large Data Transfer Test

This test checks how the RDT protocol handles large amounts of data.

### Steps:
1. **Increase Data Size**: Modify the client to send a significantly larger dataset (e.g., several MBs of data).

   Example in `main.cpp`:
   ```cpp
   std::vector<uint8_t> dataToSend(1024 * 1024, 0xAB);  // 1MB of data
   ```

2. **Run the Server and Client**: Start the server and client as before.

3. **Monitor the Transfer**: Observe how the RDT protocol handles the large data transfer, including congestion control and flow control.

### Expected Results:
- The client successfully sends the large dataset, managing the sending rate according to the network and server conditions.
- The server receives the entire dataset without loss or corruption.

## 5. Congestion Control Test

This test checks the effectiveness of the congestion control mechanism by simulating a congested network.

### Steps:
1. **Introduce Network Congestion**: Simulate congestion by limiting the bandwidth or increasing the round-trip time (RTT) using network simulation tools like `tc` on Linux.

   Example:
   ```bash
   sudo tc qdisc add dev eth0 root netem delay 100ms rate 1mbit
   ```

2. **Run the Server and Client**: Start the server and client as before.

3. **Monitor the Congestion Control Behavior**: Observe how the RDT client adjusts its sending rate in response to network congestion.

### Expected Results:
- The client should reduce its sending rate when detecting congestion (e.g., increased packet loss or delay).
- The server should still receive data, albeit at a reduced rate, without overwhelming the network.

## 6. End-to-End Integrity Test

This test checks that the data sent by the client is received exactly as intended by the server.

### Steps:
1. **Send Known Data**: Modify the client to send a specific, known pattern of data.

   Example:
   ```cpp
   std::vector<uint8_t> dataToSend = {0x01, 0x02, 0x03, 0x04, 0x05};  // Example data pattern
   ```

2. **Run the Server and Client**: Start the server and client as before.

3. **Verify Data Integrity**: On the server side, compare the received data against the expected pattern.

   Example in `server/main.cpp`:
   ```cpp
   if (receivedData == std::vector<uint8_t>{0x01, 0x02, 0x03, 0x04, 0x05}) {
       std::cout << "Data integrity verified!" << std::endl;
   } else {
       std::cerr << "Data integrity check failed." << std::endl;
   }
   ```

### Expected Results:
- The server should confirm that the data received matches exactly with what was sent by the client.

## Tools and Tips for Testing

- **Wireshark**: Use Wireshark to capture and analyze UDP packets to see how your protocol behaves on the wire.
- **tc (Traffic Control)**: Use Linux’s `tc` command to simulate different network conditions, such as latency, packet loss, and bandwidth constraints.
- **Automated Testing**: Write scripts to automate the testing process, especially for repeated tests like packet loss simulation or large data transfers.

## Conclusion

By conducting these tests, you can ensure that your RDT implementation is robust, handles adverse network conditions gracefully, and provides reliable data transfer over UDP. Adjustments and optimizations can be made based on the results to further improve the protocol's performance and reliability.

