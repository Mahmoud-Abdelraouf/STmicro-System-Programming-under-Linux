# Session 04: Comprehensive Networking and Virtualization Guide

## Overview

This guide covers the essential aspects of networking, including different topologies, networking layers, IP addressing, virtual networking devices, and practical demonstrations using various scripts and tools. It is designed to provide a thorough understanding of these concepts, making it suitable for both beginners and advanced users.

## Table of Contents

1. [Networking Topologies](#networking-topologies)
2. [Networking Layers](#networking-layers)
3. [Ethernet Packets](#ethernet-packets)
4. [IPv4 Addressing](#ipv4-addressing)
5. [IPv6 Addressing](#ipv6-addressing)
6. [ICMP Packets](#icmp-packets)
7. [ARP Packets](#arp-packets)
8. [MAC and IP Address Resolution](#mac-and-ip-address-resolution)
9. [Default Router in Linux](#default-router-in-linux)
10. [Virtual Network Devices](#virtual-network-devices)
11. [TAP and TUN Devices](#tap-and-tun-devices)
12. [VirtIO and Virtual Machines](#virtio-and-virtual-machines)
13. [Static Routing and Bridging](#static-routing-and-bridging)
14. [Practical Scripts](#practical-scripts)
15. [Resources](#resources)

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
2. **Transport Layer**
3. **Network Layer**
4. **Data Link Layer**
5. **Physical Layer**

### Detailed Explanation
- **Application Layer**: Interfaces directly with end-user applications, providing services like HTTP, FTP, SMTP, etc.
- **Transport Layer**: Manages end-to-end communication, reliability, and flow control. Protocols: TCP, UDP.
- **Network Layer**: Handles logical addressing and routing. Protocol: IP.
- **Data Link Layer**: Manages physical addressing and error detection. Protocols: Ethernet, PPP.
- **Physical Layer**: Deals with the physical connection between devices. Components: Cables, switches, etc.

---

## Ethernet Packets

Ethernet packets are the fundamental unit of data transmitted over Ethernet networks. They consist of several fields:

1. **Preamble**: 7 bytes, used for synchronization.
2. **Start Frame Delimiter (SFD)**: 1 byte, indicates the start of the frame.
3. **Destination MAC Address**: 6 bytes, address of the receiving device.
4. **Source MAC Address**: 6 bytes, address of the sending device.
5. **EtherType**: 2 bytes, indicates the protocol used in the payload.
6. **Payload**: 46-1500 bytes, the actual data being transmitted.
7. **Frame Check Sequence (FCS)**: 4 bytes, error checking code.

---

## IPv4 Addressing

### IP Address Format
- **IPv4**: 32-bit address, divided into four 8-bit octets.
- **Netmask**: Defines the network portion of the IP address.

### IPv4 Classes
IPv4 addresses are divided into five classes, based on the leading bits:

- **Class A**
  - Range: `1.0.0.0` to `126.0.0.0`
  - Default Subnet Mask: `255.0.0.0`
  - Number of Networks: 128 (2^7)
  - Number of Hosts per Network: 16,777,214 (2^24 - 2)
  - Example: `10.0.0.0` (Private Range)

- **Class B**
  - Range: `128.0.0.0` to `191.255.0.0`
  - Default Subnet Mask: `255.255.0.0`
  - Number of Networks: 16,384 (2^14)
  - Number of Hosts per Network: 65,534 (2^16 - 2)
  - Example: `172.16.0.0` (Private Range)

- **Class C**
  - Range: `192.0.0.0` to `223.255.255.0`
  - Default Subnet Mask: `255.255.255.0`
  - Number of Networks: 2,097,152 (2^21)
  - Number of Hosts per Network: 254 (2^8 - 2)
  - Example: `192.168.0.0` (Private Range)

- **Class D**
  - Range: `224.0.0.0` to `239.255.255.255`
  - Used for multicast.

- **Class E**
  - Range: `240.0.0.0` to `255.255.255.255`
  - Reserved for future use and research.

### Numerical Example for Subnetting
Let's take an IP address `192.168.1.0/24` and subnet it into smaller networks.

1. **Original Network**: `192.168.1.0/24`
   - Subnet Mask: `255.255.255.0`
   - Number of Subnets: 1
   - Number of Hosts: 256 - 2 = 254

2. **Subnet into Two**: `192.168.1.0/25` and `192.168.1.128/25`
   - Subnet Mask: `255.255.255.128`
   - Number of Subnets: 2
   - Number of Hosts: 128 - 2 = 126

3. **Subnet into Four**: `192.168.1.0/26`, `192.168.1.64/26`, `192.168.1.128/26`, and `192.168.1.192/26`
   - Subnet Mask: `255.255.255.192`
   - Number of Subnets: 4
   - Number of Hosts: 64 - 2 = 62

---

## IPv6 Addressing

### IP Address Format
- **IPv6**: 128-bit address, written as eight groups of four hexadecimal digits.

### Example Address
- `2001:0db8:85a3:0000:0000:8a2e:0370:7334`

### Address Types
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
- **Adding a Route**:
  ```sh
  sudo ip route add <network> via <gateway-ip>
  ```
- **Example**:
  ```sh
  sudo ip route add 192.168.2.0/24 via 192.168.1.1
  ```

### Bridging
- **Creating a Bridge**:
  ```sh
  sudo ip link add name br0 type bridge
  sudo ip link set dev br0 up
  ```
- **Adding Interfaces to the Bridge**:
  ```sh
  sudo ip link set dev eth0 master br0
  sudo ip link set dev tap0 master br0
  ```

---

## Practical Scripts

### Cleanup Script for Three Machines
```sh
#!/bin/bash

ip link set dev vport11 nomaster
ip tuntap del mode tap vport11

ip link set dev vport12 nomaster
ip tuntap del mode tap vport12

ip link set dev vport21 nomaster
ip tuntap del mode tap vport21

ip link set dev vport22 nomaster
ip tuntap del mode tap vport22

ip link delete dev br1
ip link delete dev br2
```

### Cleanup Script for Two Machines
```sh
#!/bin/bash

ip link set dev veth0 nomaster
ip link del dev veth0

ip link set dev vport11 nomaster
ip tuntap del mode tap vport11

ip link set dev vport12 nomaster
ip tuntap del mode tap vport12

ip link delete dev br1
```

### Start Script for Three Machines
```sh
#!/bin/bash

ip link add name br1 type bridge
ip link set br1 up

ip link add name br2 type bridge
ip link set br2 up

ip tuntap add mode tap vport11
ip link set vport11 up
ip link set vport11 master br1

ip tuntap add mode tap vport12
ip link set vport12 up
ip link set vport12 master br1

ip tuntap add mode tap vport21
ip link set vport21 up
ip link set vport21 master br2

ip tuntap add mode tap vport22
ip link set vport22 up
ip link set vport22 master br2

qemu-system-x86_64 -kernel vms3/bzImageh1.bin -m 1G \
    -drive "file=vms3/h1.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7B' \
    -netdev tap,id=net0,ifname=vport11,script=no,downscript=no \
    -name h1 -daemonize --append "root=/dev/vda rw"

qemu-system-x86_64 -kernel vms3/bzImagert2.bin -m 1G \
    -drive "file=vms3/rt2.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:74' \
    -netdev tap,id=net0,ifname=vport12,script=no,downscript=no \
    -device virtio-net-pci,netdev=net1,mac='12:34:56:AB:CD:75' \
    -netdev tap,id=net1,ifname=vport22,script=no,downscript=no \
    -name rt2 -daemonize --append "root=/dev/vda rw"

qemu-system-x86_64 -kernel vms3/bzImageh2.bin -m 1G \
    -drive "file=vms3/h2.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7C' \
    -netdev tap,id=net0,ifname=vport21,script=no,downscript=no \
    -name h2 -daemonize --append "root=/dev/vda rw"
```

### Start Script for Two Machines
```sh
#!/bin/bash

ip link add name br1 type bridge
ip link set br1 up

ip tuntap add mode tap vport11
ip link set vport11 up
ip link set vport11 master br1

ip tuntap add mode tap vport12
ip link set vport12 up
ip link set vport12 master br1

qemu-system-x86_64 -kernel vms2/bzImageh1.bin -m 1G \
    -drive "file=vms2/h1.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7B' \
    -netdev tap,id=net0,ifname=vport11,script=no,downscript=no \
    -name h1 -daemonize --append "root=/dev/vda rw"

qemu-system-x86_64 -kernel vms2/bzImageh2.bin -m 1G \
    -drive "file=vms2/h2.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7C' \
    -netdev tap,id=net0,ifname=vport12,script=no,downscript=no \
    -name h2 -daemonize --append "root=/dev/vda rw"
```

---

## Resources

- [IPv4 Classes and Private IP Ranges](https://www.meridianoutpost.com/resources/articles/IP-classes.php)
- [Linux `ip` Command Examples](https://www.tecmint.com/15-practical-examples-of-linux-ip-command-for-interfaces/)
- [QEMU Documentation](https://www.qemu.org/documentation/)
- [TUN/TAP Interface Configuration](https://www.kernel.org/doc/Documentation/networking/tuntap.txt)

By following these steps and explanations, you will have a comprehensive understanding of networking, virtual network devices, and practical implementation using scripts. This guide aims to cover both theoretical and practical aspects to provide a holistic view of networking in Linux environments.
