# Session 04: Comprehensive Networking and Virtualization Guide

## Overview

This guide covers the essential aspects of networking, including different topologies, networking layers, IP addressing, virtual networking devices, and practical demonstrations using various scripts and tools. It is designed to provide a thorough understanding of these concepts, making it suitable for both beginners and advanced users.

## Table of Contents

1. [Networking Topologies](#networking-topologies)
2. [Networking Layers](#networking-layers)
3. [Ethernet Packets](#ethernet-packets)
4. [IP Addressing and Subnetting](#ip-addressing-and-subnetting)
5. [IPv4 Addressing](#ipv4-addressing)
6. [IPv6 Addressing](#ipv6-addressing)
7. [ICMP Packets](#icmp-packets)
8. [ARP Packets](#arp-packets)
9. [MAC and IP Address Resolution](#mac-and-ip-address-resolution)
10. [Default Router in Linux](#default-router-in-linux)
11. [Virtual Network Devices](#virtual-network-devices)
12. [TAP and TUN Devices](#tap-and-tun-devices)
13. [VirtIO and Virtual Machines](#virtio-and-virtual-machines)
14. [Static Routing and Bridging](#static-routing-and-bridging)
15. [Practical Scripts](#practical-scripts)
16. [Resources](#resources)

---

## Networking Topologies

### Bus Topology
- A single central cable (the bus) to which all network devices are connected.
- **Advantages**: Simple, easy to implement.
- **Disadvantages**: Limited cable length, difficult to troubleshoot.

### Star Topology
- All network devices are connected to a central hub or switch.
- **Advantages**: Easy to manage, scalable.
- **Disadvantages**: Single point of failure (the hub/switch).

### Mesh Topology
- Devices are interconnected, allowing for multiple paths for data to travel.
- **Advantages**: High redundancy, reliable.
- **Disadvantages**: Expensive, complex setup.

### Wireless Topology
- Devices are connected using wireless signals.
- **Advantages**: Mobility, easy to set up.
- **Disadvantages**: Limited range, potential interference.

---

## Networking Layers

### OSI Model Layers
1. **Application Layer**
2. **Presentation Layer**
3. **Session Layer**
4. **Transport Layer**
5. **Network Layer**
6. **Data Link Layer**
7. **Physical Layer**

### Detailed Explanation

#### 1. Application Layer
- **Function**: Interfaces directly with end-user applications, providing network services.
- **Protocols**: HTTP, FTP, SMTP, DNS, Telnet, SSH
- **Examples**:
  - **HTTP**: Used by web browsers to fetch web pages from web servers.
  - **FTP**: Used to transfer files between computers on a network.
  - **SMTP**: Used for sending emails.
- **Types**:
  - **Web Protocols**: HTTP, HTTPS
  - **File Transfer Protocols**: FTP, TFTP
  - **Email Protocols**: SMTP, IMAP, POP3
  - **Directory Services**: LDAP
  - **Remote Access Protocols**: Telnet, SSH

#### 2. Presentation Layer
- **Function**: Responsible for data translation, encryption, and compression.
- **Examples**:
  - **Data Translation**: Converts data formats like EBCDIC to ASCII.
  - **Encryption**: SSL/TLS protocols used to secure data transmission over the internet.
  - **Compression**: Reduces the number of bits that need to be transmitted on the network.
- **Types**:
  - **Data Formats**: JPEG, GIF, TIFF
  - **Encryption**: SSL/TLS, Kerberos
  - **Compression**: MPEG, GIF

#### 3. Session Layer
- **Function**: Manages sessions between applications. It establishes, manages, and terminates connections between applications.
- **Examples**:
  - **Session Management**: In web conferencing, it manages the session to ensure all participants can communicate in real-time.
  - **Synchronization**: In a file transfer, it ensures the file transfer can be resumed from the same point if the connection drops.
- **Types**:
  - **Session Management**: NetBIOS
  - **Dialog Control**: RPC (Remote Procedure Call)
  - **Synchronization**: PPTP (Point-to-Point Tunneling Protocol)

#### 4. Transport Layer
- **Function**: Ensures reliable data transfer with error correction and flow control. It segments and reassembles data into a data stream.
- **Protocols**: TCP, UDP
- **Examples**:
  - **TCP**: Ensures reliable, ordered, and error-checked delivery of a stream of data between applications.
  - **UDP**: Provides a simpler, connectionless communication model with minimal protocol mechanism.
- **Types**:
  - **Connection-Oriented**: TCP (Transmission Control Protocol)
  - **Connectionless**: UDP (User Datagram Protocol)
  - **Message-Oriented**: SCTP (Stream Control Transmission Protocol)

#### 5. Network Layer
- **Function**: Handles logical addressing and routing. It determines the best path to move data from source to destination.
- **Protocols**: IP, ICMP, IGMP
- **Examples**:
  - **IP**: Responsible for addressing and routing packets of data so they can travel across networks and arrive at the correct destination.
  - **ICMP**: Used for diagnostic purposes like the ping command to test connectivity between hosts.
- **Types**:
  - **Routing Protocols**: OSPF (Open Shortest Path First), BGP (Border Gateway Protocol)
  - **Addressing Protocols**: IPv4, IPv6
  - **Messaging Protocols**: ICMP (Internet Control Message Protocol)
  - **Multicast Protocols**: IGMP (Internet Group Management Protocol)

#### 6. Data Link Layer
- **Function**: Manages physical addressing and error detection. It ensures that data transferred is free from errors.
- **Protocols**: Ethernet, PPP, Switches, Bridges
- **Examples**:
  - **Ethernet**: Defines wiring and signaling standards for the physical layer, as well as data packet formats and protocols for the data link layer.
  - **MAC Addressing**: Provides unique identifiers assigned to network interfaces for communications on the physical network segment.
- **Types**:
  - **LLC (Logical Link Control)**: Manages frames to identify network layer protocols.
  - **MAC (Media Access Control)**: Manages protocols for accessing the physical medium.
  - **Error Detection**: CRC (Cyclic Redundancy Check)

#### 7. Physical Layer
- **Function**: Deals with the physical connection between devices. It transmits raw bitstreams over a physical medium.
- **Components**: Cables, switches, hubs, network adapters
- **Examples**:
  - **Cables**: Coaxial, optical fiber, and twisted pair cables.
  - **Physical Transmission**: The actual hardware that transmits the raw data bits over the network medium, such as Ethernet cables or fiber optics.
- **Types**:
  - **Transmission Media**: Copper cables, fiber optic cables, wireless
  - **Hardware Devices**: Hubs, repeaters, network adapters
  - **Signaling**: Electrical signals, light signals
  
---

## 1. IP Addressing and Subnetting

### 1.1. IPv4 Addressing

#### 1.1.1. IP Address Format
- **IPv4**: 32-bit address, divided into four 8-bit octets.
- **Netmask**: Defines the network portion of the IP address.
- **CIDR Notation**: The `/` notation following an IP address indicates the number of bits used for the network portion (e.g., `192.168.1.0/24`).

#### 1.1.2. IPv4 Classes
IPv4 addresses are divided into five classes, based on the leading bits:

- **Class A**
  - **Range**: `1.0.0.0` to `126.0.0.0`
  - **Default Subnet Mask**: `255.0.0.0`
  - **Number of Networks**: 128 (2^7)
  - **Number of Hosts per Network**: 16,777,214 (2^24 - 2)
  - **Example**: `10.0.0.0` (Private Range)

- **Class B**
  - **Range**: `128.0.0.0` to `191.255.0.0`
  - **Default Subnet Mask**: `255.255.0.0`
  - **Number of Networks**: 16,384 (2^14)
  - **Number of Hosts per Network**: 65,534 (2^16 - 2)
  - **Example**: `172.16.0.0` (Private Range)

- **Class C**
  - **Range**: `192.0.0.0` to `223.255.255.0`
  - **Default Subnet Mask**: `255.255.255.0`
  - **Number of Networks**: 2,097,152 (2^21)
  - **Number of Hosts per Network**: 254 (2^8 - 2)
  - **Example**: `192.168.0.0` (Private Range)

- **Class D**
  - **Range**: `224.0.0.0` to `239.255.255.255`
  - **Used for**: Multicast.

- **Class E**
  - **Range**: `240.0.0.0` to `255.255.255.255`
  - **Reserved for**: Future use and research.

#### 1.1.3. Subnetting and Netmask
Subnetting allows dividing a larger network into smaller sub-networks, which helps in efficient IP management and security.

##### Subnet Mask
- **Purpose**: Determines which portion of an IP address is the network and which part is the host.
- **Example**: `255.255.255.0` (binary: `11111111.11111111.11111111.00000000`)

#### 1.1.4. Numerical Example for Subnetting
Let's take an IP address `192.168.1.0/24` and subnet it into smaller networks.

1. **Original Network**: `192.168.1.0/24`
   - **Subnet Mask**: `255.255.255.0`
   - **Number of Subnets**: 1
   - **Number of Hosts**: 256 - 2 = 254
   - **Binary Subnet Mask**: `11111111.11111111.11111111.00000000`

2. **Subnet into Two**: `192.168.1.0/25` and `192.168.1.128/25`
   - **Subnet Mask**: `255.255.255.128`
   - **Number of Subnets**: 2
   - **Number of Hosts**: 128 - 2 = 126
   - **Binary Subnet Mask**: `11111111.11111111.11111111.10000000`

   **Explanation**:
   - **192.168.1.0/25**:
     - Binary: `11000000.10101000.00000001.0XXXXXXX`
     - First Address: `192.168.1.0`
     - Last Address: `192.168.1.127`
     - **First Address (Binary)**: `11000000.10101000.00000001.00000000`
     - **Last Address (Binary)**: `11000000.10101000.00000001.01111111`

   - **192.168.1.128/25**:
     - Binary: `11000000.10101000.00000001.1XXXXXXX`
     - First Address: `192.168.1.128`
     - Last Address: `192.168.1.255`
     - **First Address (Binary)**: `11000000.10101000.00000001.10000000`
     - **Last Address (Binary)**: `11000000.10101000.00000001.11111111`

3. **Subnet into Four**: `192.168.1.0/26`, `192.168.1.64/26`, `192.168.1.128/26`, and `192.168.1.192/26`
   - **Subnet Mask**: `255.255.255.192`
   - **Number of Subnets**: 4
   - **Number of Hosts**: 64 - 2 = 62
   - **Binary Subnet Mask**: `11111111.11111111.11111111.11000000`

   **Explanation**:
   - **192.168.1.0/26**:
     - Binary: `11000000.10101000.00000001.00XXXXXX`
     - First Address: `192.168.1.0`
     - Last Address: `192.168.1.63`
     - **First Address (Binary)**: `11000000.10101000.00000001.00000000`
     - **Last Address (Binary)**: `11000000.10101000.00000001.00111111`

   - **192.168.1.64/26**:
     - Binary: `11000000.10101000.00000001.01XXXXXX`
     - First Address: `192.168.1.64`
     - Last Address: `192.168.1.127`
     - **First Address (Binary)**: `11000000.10101000.00000001.01000000`
     - **Last Address (Binary)**: `11000000.10101000.00000001.01111111`

   - **192.168.1.128/26**:
     - Binary: `11000000.10101000.00000001.10XXXXXX`
     - First Address: `192.168.1.128`
     - Last Address: `192.168.1.191`
     - **First Address (Binary)**: `11000000.10101000.00000001.10000000`
     - **Last Address (Binary)**: `11000000.10101000.00000001.10111111`

   - **192.168.1.192/26**:
     - Binary: `11000000.10101000.00000001.11XXXXXX`
     - First Address: `192.168.1.192`
     - Last Address: `192.168.1.255`
     - **First Address (Binary)**: `11000000.10101000.00000001.11000000`
     - **Last Address (Binary)**: `11000000.10101000.00000001.11111111`

#### 1.1.5. Practical Commands for IPv4

- **View IP Address**:
  ```sh
  ip addr show
  ```

- **Assign IP Address**:
  ```sh
  sudo ip addr add 192.168.1.10/24 dev eth0
  ```

- **Add Default Gateway**:
  ```sh
  sudo ip route add default via 192.168.1.1
  ```

- **View Routing Table**:
  ```sh
  ip route show
  ```

#### 1.1.6. Routing and Default Gateway
A router forwards data packets between computer networks. A default gateway routes traffic from a local network to other networks or the internet.

- **Example**:
  - To set a default gateway: `sudo ip route add default via 192.168.1.1`
  - To view the routing table: `ip route show`

#### 1.1.7. ICMP and ARP
- **ICMP (Internet Control Message Protocol)**: Used for error messages and operational information (e.g., `ping` command).
- **ARP (Address Resolution Protocol)**: Resolves IP addresses to MAC (hardware) addresses within a local network.

#### 1.1.8. Data Transmission in a Network
When a device wants to communicate with another device:

1. **Local Network**:
   - The sender sends an ARP request to get the MAC address of the recipient.
   - If the recipient is in the same network, it responds with its

 MAC address.
   - Data is then sent directly to the recipient using the MAC address.

2. **Different Network**:
   - The sender sends data to the default gateway (router).
   - The router forwards the data to the next router, and this process continues until the data reaches the recipient’s network.
   - ARP is used within each local network to resolve MAC addresses.

#### 1.1.9. ARP and ICMP
- **ARP (Address Resolution Protocol)**: Resolves IP addresses to MAC (hardware) addresses within a local network. 
- **ICMP (Internet Control Message Protocol)**: Used for error messages and operational information (e.g., `ping` command).

##### Example of ARP
1. **Local Network Communication**:
   - **Sender**: Sends an ARP request to get the MAC address of the recipient.
   - **Recipient**: If in the same network, it responds with its MAC address.
   - **Data Transmission**: Data is sent directly to the recipient using the MAC address.

2. **Different Network Communication**:
   - **Sender**: Sends data to the default gateway (router).
   - **Router**: Forwards the data to the next router, and this process continues until the data reaches the recipient’s network.
   - **ARP**: Used within each local network to resolve MAC addresses.

##### Types of Casts
- **Unicast**: Communication between a single sender and a single receiver.
- **Broadcast**: Communication from one sender to all possible receivers in the network.
- **Multicast**: Communication from one sender to a group of receivers.

#### 1.1.10. ARP Packet
- **Purpose**: Determine the MAC address corresponding to an IP address.
- **Process**: 
  - **Sender**: Broadcasts an ARP request asking "Who has IP address X?"
  - **Recipient**: Responds with its MAC address.

---

## 2. IPv6 Addressing

### 2.1. IP Address Format
- **IPv6**: 128-bit address, written as eight groups of four hexadecimal digits (e.g., `2001:0db8:85a3:0000:0000:8a2e:0370:7334`).

### 2.2. IPv6 Features
- **Larger Address Space**: Provides a virtually unlimited number of IP addresses.
- **Simplified Header**: Improves routing efficiency and performance.
- **Auto-Configuration**: Devices can automatically configure their own IP addresses.
- **Integrated Security**: IPsec is mandatory in IPv6.
- **No Broadcasts**: Uses multicast and anycast instead of broadcast.

### 2.3. Example Address
- `2001:0db8:85a3:0000:0000:8a2e:0370:7334`

### 2.4. Subnetting in IPv6
IPv6 uses prefix length to denote subnetting (similar to CIDR in IPv4).

- **Example**:
  - Global Unicast Address: `2001:0db8::/32`
  - Subnet ID: `2001:0db8:abcd::/48`
  - Interface ID: `2001:0db8:abcd:0012:0000:0000:0000:0001/64`

### 2.5. Transition from IPv4 to IPv6
- **Dual Stack**: Devices run both IPv4 and IPv6.
- **Tunneling**: Encapsulating IPv6 traffic within IPv4 packets.
- **Translation**: Converting IPv6 packets to IPv4 packets and vice versa.

### 2.6. Practical Usage
- Configure IPv6 on a network interface:
  ```sh
  sudo ip -6 addr add 2001:db8::1/64 dev eth0
  ```
- Add an IPv6 route:
  ```sh
  sudo ip -6 route add 2001:db8:abcd::/64 via 2001:db8::1
  ```
  
### 2.7. Address Types
- **Unicast**: Identifies a single network interface.
- **Multicast**: Identifies multiple network interfaces.
- **Anycast**: Identifies the nearest of multiple network interfaces.

---

## ICMP Packets

### ICMP (Internet Control Message Protocol)
- Used for error messages and operational information.
- Common messages: Echo Request (ping), Echo Reply (pong), Destination Unreachable.

### Packet Structure
1. **Type**: 8 bits, indicates the type of message.
2. **Code**: 8 bits, provides further information about the type.
3. **Checksum**: 16 bits, for error-checking.
4. **Rest of the Header**: Varies based on the type and code.

### Example
- **Ping**:
  - Type: 8 (Echo Request)
  - Code: 0

---

## ARP Packets

### ARP (Address Resolution Protocol)
- Used to map an IP address to a MAC address within a local network.

### ARP Process
1. **ARP Request**: Broadcasted by a device to find the MAC address associated with an IP address.
2. **ARP Reply**: Sent by the device with the requested IP address, containing its MAC address.

### Packet Structure
1. **Hardware Type**: 16 bits, indicates the network type (e.g., Ethernet).
2. **Protocol Type**: 16 bits, indicates the protocol (e.g., IP).
3. **Hardware Address Length**: 8 bits.
4. **Protocol Address Length**: 8 bits.
5. **Operation**: 16 bits, indicates request (1) or reply (2).
6. **Sender Hardware Address**: 48 bits.
7. **Sender Protocol Address**: 32 bits.
8. **Target Hardware Address**: 48 bits.
9. **Target Protocol Address**: 32 bits.

### Example of ARP Communication
- Device A wants to communicate with Device B.
- Device A sends an ARP request: "Who has IP address 192.168.1.2? Tell 192.168.1.1."
- Device B responds: "192.168.1.2 is at MAC address 00:14:22:01:23:45."

---

## MAC and IP Address Resolution

### MAC Address


- A unique identifier assigned to network interfaces for communications at the data link layer.
- Format: 48-bit address, usually written as six groups of two hexadecimal digits separated by colons.

### IP Address
- A numerical label assigned to each device connected to a computer network that uses the Internet Protocol for communication.

### ARP Process in Detail
1. **Device A wants to communicate with Device B** within the same network.
2. **Device A broadcasts an ARP request** to all devices on the local network: "Who has IP address 192.168.1.2? Tell 192.168.1.1."
3. **Device B receives the ARP request** and replies with its MAC address: "192.168.1.2 is at MAC address 00:14:22:01:23:45."
4. **Device A stores the MAC address** in its ARP cache and uses it to send packets directly to Device B.

### Communicating with a Device on a Different Network
1. **Device A wants to communicate with Device B** on a different network.
2. **Device A checks its routing table** and finds the route to the default gateway (router).
3. **Device A sends packets to the router's MAC address**.
4. **The router forwards the packets** to Device B's network, using its routing table to determine the next hop.
5. **Device B receives the packets** and sends responses back to Device A through the router.

### Default Router in Linux
- A default router (or gateway) is the device that routes traffic from a local network to other networks or the internet.
- **Configuring the Default Gateway**:
  ```sh
  sudo ip route add default via <router-ip>
  ```
- **Example**:
  ```sh
  sudo ip route add default via 192.168.1.1
  ```

---

## Virtual Network Devices

### TUN and TAP Devices
- **TAP Device**: Emulates an Ethernet device and operates with layer 2 packets such as Ethernet frames.
- **TUN Device**: Emulates a network layer device and operates with layer 3 packets such as IP packets.

### Creating and Managing TAP/TUN Devices
- **Create a TAP device**:
  ```sh
  sudo ip tuntap add dev tap0 mode tap
  sudo ip link set dev tap0 up
  ```
- **Create a TUN device**:
  ```sh
  sudo ip tuntap add dev tun0 mode tun
  sudo ip link set dev tun0 up
  ```

---

## VirtIO and Virtual Machines

### VirtIO
- A virtualization standard for network and disk device drivers.
- **Advantages**: Provides a more efficient interface between virtual machines and hypervisors, improving performance.

### Running Virtual Machines with QEMU
- **Example Command**:
  ```sh
  qemu-system-x86_64 -kernel bzImage -m 1G \
    -drive file=rootfs.img,if=virtio \
    -netdev tap,id=net0,ifname=tap0,script=no,downscript=no \
    -device virtio-net-pci,netdev=net0 \
    -append "root=/dev/vda rw" -daemonize
  ```

---

## Static Routing and Bridging

### Static Routing

Static routing is a type of network routing technique in which routes are manually configured and managed by the network administrator, as opposed to dynamic routing where routes are automatically adjusted by network protocols. Static routes are useful for small networks or for networks with a predictable and stable topology.

#### How Static Routing Works
Static routing involves manually adding routes to the routing table of a router or host. The routing table is a data structure that contains information about the paths that data packets take to reach their destinations. Each entry in the routing table specifies the destination network, the subnet mask, and the next-hop IP address (gateway).

#### Adding a Static Route
To add a static route, you use the `ip route add` command followed by the destination network and the gateway IP address.

- **Command**:
  ```sh
  sudo ip route add <network> via <gateway-ip>
  ```
- **Example**:
  To add a route to the network `192.168.2.0/24` via the gateway `192.168.1.1`, you would use the following command:
  ```sh
  sudo ip route add 192.168.2.0/24 via 192.168.1.1
  ```

This command tells the system that any traffic destined for the `192.168.2.0/24` network should be sent through the gateway `192.168.1.1`.

### Bridging

Bridging is a technique used to connect two or more network segments, making them function as a single network. A network bridge forwards traffic between these segments based on MAC addresses, effectively making the separate segments behave as one.

#### How Bridging Works
A bridge operates at the Data Link layer (Layer 2) of the OSI model and is used to connect different network segments. It filters and forwards traffic based on MAC addresses. By doing so, it reduces the collision domain but maintains the broadcast domain. This is useful in scenarios where you want to extend the network without adding routers.

#### Creating a Network Bridge
To create a bridge, you use the `ip link add` command to create a bridge interface, and the `ip link set` command to bring the bridge interface up.

- **Commands**:
  ```sh
  sudo ip link add name br0 type bridge
  sudo ip link set dev br0 up
  ```

#### Adding Interfaces to the Bridge
Once the bridge is created, you can add network interfaces to it. This is done by using the `ip link set` command to set the network interfaces as members of the bridge.

- **Commands**:
  ```sh
  sudo ip link set dev eth0 master br0
  sudo ip link set dev tap0 master br0
  ```

In this example, `eth0` and `tap0` are added to the bridge `br0`. This effectively makes `eth0` and `tap0` part of the same network segment.

### Practical Examples

#### Adding a Static Route
```sh
sudo ip route add 192.168.2.0/24 via 192.168.1.1
```

#### Creating a Bridge
```sh
sudo ip link add name br0 type bridge
sudo ip link set dev br0 up
```

#### Adding Interfaces to the Bridge
```sh
sudo ip link set dev eth0 master br0
sudo ip link set dev tap0 master br0
```

By understanding and utilizing static routing and bridging, network administrators can effectively manage and optimize network traffic, ensuring efficient and reliable communication within and across networks.

---

## Practical Scripts

### Start Script for Two Machines
```sh
#!/bin/bash

# Create a bridge device named br1
ip link add name br1 type bridge
# Set the bridge device br1 up
ip link set br1 up

# Create a tap device named vport11
ip tuntap add mode tap vport11
# Set the tap device vport11 up
ip link set vport11 up
# Add the tap device vport11 to the bridge br1
ip link set vport11 master br1

# Create a tap device named vport12
ip tuntap add mode tap vport12
# Set the tap device vport12 up
ip link set vport12 up
# Add the tap device vport12 to the bridge br1
ip link set vport12 master br1

# Start the first virtual machine h1 using QEMU
qemu-system-x86_64 -kernel vms2/bzImageh1.bin -m 1G \
    -drive "file=vms2/h1.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7B' \
    -netdev tap,id=net0,ifname=vport11,script=no,downscript=no \
    -name h1 -daemonize --append "root=/dev/vda rw"

# Start the second virtual machine h2 using QEMU
qemu-system-x86_64 -kernel vms2/bzImageh2.bin -m 1G \
    -drive "file=vms2/h2.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7C' \
    -netdev tap,id=net0,ifname=vport12,script=no,downscript=no \
    -name h2 -daemonize --append "root=/dev/vda rw"
```

### Cleanup Script for Two Machines
```sh
#!/bin/bash

# Detach the virtual ethernet device veth0 from its bridge
ip link set dev veth0 nomaster
# Delete the virtual ethernet device veth0
ip link del dev veth0

# Detach the tap device vport11 from its bridge
ip link set dev vport11 nomaster
# Delete the tap device vport11
ip tuntap del mode tap vport11

# Detach the tap device vport12 from its bridge
ip link set dev vport12 nomaster
# Delete the tap device vport12
ip tuntap del mode tap vport12

# Delete the bridge device br1
ip link delete dev br1
```

### Start Script for Three Machines
```sh
#!/bin/bash

# Create a bridge device named br1
ip link add name br1 type bridge
# Set the bridge device br1 up
ip link set br1 up

# Create a bridge device named br2
ip link add name br2 type bridge
# Set the bridge device br2 up
ip link set br2 up

# Create a tap device named vport11
ip tuntap add mode tap vport11
# Set the tap device vport11 up
ip link set vport11 up
# Add the tap device vport11 to the bridge br1
ip link set vport11 master br1

# Create a tap device named vport12
ip tuntap add mode tap vport12
# Set the tap device vport12 up
ip link set vport12 up
# Add the tap device vport12 to the bridge br1
ip link set vport12 master br1

# Create a tap device named vport21
ip tuntap add mode tap vport21
# Set the tap device vport21 up
ip link set vport21 up
# Add the tap device vport21 to the bridge br2
ip link set vport21 master br2

# Create a tap device named vport22
ip tuntap add mode tap vport22
# Set the tap device vport22 up
ip link set vport22 up
# Add the tap device vport22 to the bridge br2
ip link set vport22 master br2

# Start the first virtual machine h1 using QEMU
qemu-system-x86_64 -kernel vms3/bzImageh1.bin -m 1G \
    -drive "file=vms3/h1.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7B' \
    -netdev tap,id=net0,ifname=vport11,script=no,downscript=no \
    -name h1 -daemonize --append "root=/dev/vda rw"

# Start the second virtual machine rt2 using QEMU
qemu-system-x86_64 -kernel vms3/bzImagert2.bin -m 1G \
    -drive "file=vms3/rt2.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:74' \
    -netdev tap,id=net0,ifname=vport12,script=no,downscript=no \
    -device virtio-net-pci,netdev=net1,mac='12:34:56:AB:CD:75' \
    -netdev tap,id=net1,ifname=vport22,script=no,downscript=no \
    -name rt2 -daemonize --append "root=/dev/vda rw"

# Start the third virtual machine h2 using QEMU
qemu-system-x86_64 -kernel vms3/bzImageh2.bin -m 1G \
    -drive "file=vms3/h2.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7C' \
    -netdev tap,id=net0,ifname=vport21,script=no,downscript=no \
    -name h2 -daemonize --append "root=/dev/vda rw"
```

### Cleanup Script for Three Machines
```sh
#!/bin/bash

# Detach the tap device vport11 from its bridge
ip link set dev vport11 nomaster
# Delete the tap device vport11
ip tuntap del mode tap vport11

# Detach the tap device vport12 from its bridge
ip link set dev vport12 nomaster
# Delete the tap device vport12
ip tuntap del mode tap vport12

# Detach the tap device vport21 from its bridge
ip link set dev vport21 nomaster
# Delete the tap device vport21
ip tuntap del mode tap vport21

# Detach the tap device vport22 from its bridge
ip link set dev vport22 nomaster
# Delete the tap device vport22
ip tuntap del mode tap vport22

# Delete the bridge device br1
ip link delete dev br1
# Delete the bridge device br2
ip link delete dev br2
```

---

## Resources

- [IPv4 Classes and Private IP Ranges](https://www.meridianoutpost.com/resources/articles/IP-classes.php)
- [Linux `ip` Command Examples](https://www.tecmint.com/ip-command-examples/)
- [QEMU Documentation](https://www.qemu.org/documentation/)
- [TUN/TAP Interface Configuration](https://www.kernel.org/doc/Documentation/networking/tuntap.txt)

By following these steps and explanations, you will have a comprehensive understanding of networking, virtual network devices, and practical implementation using scripts. This guide aims to cover both theoretical and practical aspects to provide a holistic view of networking in Linux environments.
