# Session 05: Advanced Network Virtualization and Routing with QEMU

## Overview

In this session, we continue our exploration of network virtualization and routing using QEMU, focusing on advanced concepts and configurations. We discuss QEMU's backend and frontend network devices, the role of VirtIO and vhost in enhancing performance, user space I/O, Data Plane Development Kit (DPDK), and more. We also provide detailed scripts for setting up a complex network with six virtual machines (VMs) and the necessary configurations for ensuring optimal communication between these VMs.

## Table of Contents

1. [QEMU Network Backends and Frontends](#qemu-network-backends-and-frontends)
2. [VirtIO and vhost](#virtio-and-vhost)
3. [User Space I/O and DPDK](#user-space-io-and-dpdk)
4. [Network Address Translation (NAT)](#network-address-translation-nat)
5. [QEMU User Mode Networking](#qemu-user-mode-networking)
6. [SLIP and PPP](#slip-and-ppp)
7. [QEMU Object Model](#qemu-object-model)
8. [QEMU SLIRP](#qemu-slirp)
9. [Ports and Sockets in Linux](#ports-and-sockets-in-linux)
10. [Ephemeral Ports and Server Ports](#ephemeral-ports-and-server-ports)
11. [Masquerading vs NAT](#masquerading-vs-nat)
12. [Setting Up a Complex Network with Six VMs](#setting-up-a-complex-network-with-six-vms)
13. [Network Configuration Notes](#network-configuration-notes)
14. [Useful Resources](#useful-resources)

---

## QEMU Network Backends and Frontends

QEMU provides various backends and frontends for network virtualization. The backend refers to the host-side network implementation, while the frontend is the guest-side implementation.

### Common Network Devices in QEMU
- **VirtIO**: A paravirtualized device for high-performance I/O.
- **e1000**: Emulates Intel E1000 network card.
- **rtl8139**: Emulates Realtek RTL8139 network card.

### Network Backends
- **tap**: Connects the guest to a network bridge.
- **user**: Simplifies setup but is less performant, typically used for NAT.
- **vhost**: Offloads the packet forwarding to the kernel for improved performance.

---

## VirtIO and vhost

### VirtIO
VirtIO is a virtualization standard for network and disk device drivers. It provides high-performance I/O through paravirtualization.

### vhost
vhost is a kernel-level accelerator for VirtIO, offloading data plane operations to the kernel. This reduces latency and CPU usage compared to user-space I/O.

#### How vhost Speeds Up Operations
- **Direct Memory Access**: Uses /dev/vhost-net to facilitate faster communication between the host and guest.
- **Kernel Offloading**: Offloads packet processing to the kernel, bypassing the user space.

vhost only works with VirtIO and does not support other NIC types.

For more details, see:
- [Introduction to VirtIO Networking and vhost-net](https://www.redhat.com/en/blog/introduction-virtio-networking-and-vhost-net)
- [Deep Dive into VirtIO Networking and vhost-net](https://www.redhat.com/en/blog/deep-dive-virtio-networking-and-vhost-net)

#### Example: Setting Up a Network with vhost

##### Create a Network Bridge and TAP Interfaces

```bash
#!/bin/bash

ip link add name br1 type bridge
ip link set br1 up

ip tuntap add mode tap vport11
ip link set vport11 up
ip link set vport11 master br1

ip tuntap add mode tap vport12
ip link set vport12 up
ip link set vport12 master br1
```

##### Launching Virtual Machines with vhost

###### Machine 1

```bash
#!/bin/bash

sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms2/bzImageh1.bin -m 1G \
        -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms2/h1.ext4,if=virtio,format=raw" \
        -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7B' \
        -netdev tap,id=net0,ifname=vport11,script=no,downscript=no,vhost=on \
        -name h1 --append "root=/dev/vda console=ttyS0 rw" -nographic -D ./log1.txt
```

###### Machine 2

```bash
#!/bin/bash

sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms2/bzImageh2.bin -m 1G \
        -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms2/h2.ext4,if=virtio,format=raw" \
        -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7C' \
        -netdev tap,id=net0,ifname=vport12,script=no,downscript=no,vhost=on \
        -name h2 --append "root=/dev/vda console=ttyS0 rw" -nographic -D ./log2.txt
```

---

## User Space I/O and DPDK

### User Space I/O
User space I/O allows for high-performance network and disk I/O directly from user space. This is often used in conjunction with DPDK.

### Data Plane Development Kit (DPDK)
DPDK is a set of libraries and drivers for fast packet processing in user space. It bypasses the kernel network stack, achieving high throughput and low latency.

For further reading, refer to the [Linux Driver Implementer’s API Guide](https://www.kernel.org/doc/html/v4.14/driver-api/basics.html).

---

## Network Address Translation (NAT)

### NAT Overview
NAT translates private IP addresses to a public IP address, enabling multiple devices on a private network to share a single public IP.

### Types of NAT
- **Static NAT**: One-to-one mapping between private and public IPs.
- **Dynamic NAT**: Maps private IPs to a pool of public IPs.
- **PAT (Port Address Translation)**: Maps multiple private IPs to a single public IP by differentiating traffic using ports.

For more details, see Cisco's [Introduction to NAT](https://www.cisco.com/c/en/us/products/routers/network-address-translation.html).

---

## QEMU User Mode Networking

QEMU user mode networking simplifies the process of connecting VMs to the outside world by using NAT. It does not require root privileges to run and is particularly useful for scenarios where ease of setup is more critical than raw performance.

### Address Translation
- **Guest to Host**: Guest sees the host as 127.0.0.1.
- **Host to Guest**: Host sees the guest using translated IPs.

### Running a VM in User Mode

```bash
qemu-system-x86_64 \
    -drive file=core-image-minimal-qemux86-64.ext4,if=virtio,format=raw \
    -device virtio-net-pci,netdev=net0,mac=52:54:00:12:34:02 \
    -netdev user,id=net0 \
    -kernel bzImage-qemux86-64.bin -nographic \
    -append "root=/dev/vda rw mem=256M console=ttyS0"
```

---

## SLIP and PPP

### SLIP (Serial Line Internet Protocol)
SLIP is an older protocol used to connect devices over serial interfaces. It encapsulates IP packets over serial links.

### PPP (Point-to-Point Protocol)
PPP is a more advanced protocol than SLIP, providing error detection, compression, and authentication.

### Serial Device Communication
Serial devices can communicate over SLIP or PPP, enabling network layer communications over serial connections.

### SLIRP
SLIRP is a program that provides network connectivity similar to SLIP but is used primarily in user-mode networking in QEMU.

---

## QEMU Object Model

QEMU's object model allows for flexible and dynamic creation and management of devices. It supports various network configurations through its comprehensive model.

### QEMU SLIRP
SLIRP provides user mode networking for QEMU, emulating network protocols for guest connectivity. See the [QEMU Networking Documentation](https://wiki.qemu.org/Documentation/Networking) for more details.

### slirp4netns
slirp4netns allows running containers with rootless networking, leveraging SLIRP for user mode network emulation.

---

## Ports and Sockets in Linux

### Ports
Ports are used by the transport layer (TCP/UDP) to identify specific processes or services.

### Sockets
Sockets are endpoints for communication, defined by an IP address and port number.

#### Source Port and Destination Port
- **Source Port**: The port from which a message originates.
- **Destination Port**: The port to which a message is addressed.

### Ephemeral Ports and Server Ports
- **Ephemeral Ports**: Temporary ports assigned to client applications.
- **Server Ports**: Well-known ports assigned to server applications.

---

## Masquerading vs NAT

### Masquerading
Masquerading is a type of NAT where the source IP address and port are changed for outgoing traffic, allowing multiple devices to share a

 single public IP.

### NAT
NAT includes masquerading and other types, such as static and dynamic NAT.

---

## Setting Up a Complex Network with Six VMs

### Preparation Script

```bash
#!/bin/bash 

for i in $(seq 1 6)
do
    ip link add name br${i} type bridge
    ip link set br${i} up
    for j in $(seq 1 2)
    do
        ip tuntap add mode tap vport${i}${j}
        ip link set vport${i}${j} up
        ip link set vport${i}${j} master br${i}
    done
done

# Create virtual ethernet and connect it to br1
ip link add dev veth0 type veth peer name veth1
ip link set veth0 up
ip link set veth0 master br1
ip address add 10.20.10.4/24 dev veth1
ip link set veth1 up
```

### Launching Multiple Routers and Hosts

#### Script to Set Up the Network

```bash
#!/bin/bash

# Cleanup script
./cleanup.sh 

# Create bridges and TAP interfaces
for i in $(seq 1 6)
do
    ip link add name br${i} type bridge
    ip link set br${i} up
    for j in $(seq 1 2)
    do
        ip tuntap add mode tap vport${i}${j}
        ip link set vport${i}${j} up
        ip link set vport${i}${j} master br${i}
    done
done

# Create virtual ethernet and connect it to br1
ip link add dev veth0 type veth peer name veth1
ip link set veth0 up
ip link set veth0 master br1
ip address add 10.20.10.4/24 dev veth1
ip link set veth1 up

# Start up routers
# rt1
qemu-system-x86_64 -kernel vms/bzImagert1.bin -m 1G \
-drive "file=vms/rt1.ext4,if=virtio,format=raw" \
-device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:71' \
-netdev tap,id=net0,ifname=vport11,script=no,downscript=no \
-device virtio-net-pci,netdev=net1,mac='12:34:56:AB:CD:72' \
-netdev tap,id=net1,ifname=vport21,script=no,downscript=no \
-device virtio-net-pci,netdev=net2,mac='12:34:56:AB:CD:73' \
-netdev tap,id=net2,ifname=vport31,script=no,downscript=no \
-name rt1 -daemonize --append "root=/dev/vda rw"

# rt2
qemu-system-x86_64 -kernel vms/bzImagert2.bin -m 1G \
-drive "file=vms/rt2.ext4,if=virtio,format=raw" \
-device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:74' \
-netdev tap,id=net0,ifname=vport22,script=no,downscript=no \
-device virtio-net-pci,netdev=net1,mac='12:34:56:AB:CD:75' \
-netdev tap,id=net1,ifname=vport42,script=no,downscript=no \
-name rt2 -daemonize --append "root=/dev/vda rw"

# rt3
qemu-system-x86_64 -kernel vms/bzImagert3.bin -m 1G \
-drive "file=vms/rt3.ext4,if=virtio,format=raw" \
-device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:76' \
-netdev tap,id=net0,ifname=vport32,script=no,downscript=no \
-device virtio-net-pci,netdev=net1,mac='12:34:56:AB:CD:77' \
-netdev tap,id=net1,ifname=vport52,script=no,downscript=no \
-name rt3 -daemonize --append "root=/dev/vda rw"

# rt4
qemu-system-x86_64 -kernel vms/bzImagert4.bin -m 1G \
-drive "file=vms/rt4.ext4,if=virtio,format=raw" \
-device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:78' \
-netdev tap,id=net0,ifname=vport41,script=no,downscript=no \
-device virtio-net-pci,netdev=net1,mac='12:34:56:AB:CD:79' \
-netdev tap,id=net1,ifname=vport51,script=no,downscript=no \
-device virtio-net-pci,netdev=net2,mac='12:34:56:AB:CD:7A' \
-netdev tap,id=net2,ifname=vport61,script=no,downscript=no \
-name rt4 -daemonize --append "root=/dev/vda rw"

# Start up hosts
# h1
qemu-system-x86_64 -kernel vms/bzImageh1.bin -m 1G \
-drive "file=vms/h1.ext4,if=virtio,format=raw" \
-device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7B' \
-netdev tap,id=net0,ifname=vport12,script=no,downscript=no \
-name h1 -daemonize --append "root=/dev/vda rw"

# h2
qemu-system-x86_64 -kernel vms/bzImageh2.bin -m 1G \
-drive "file=vms/h2.ext4,if=virtio,format=raw" \
-device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7C' \
-netdev tap,id=net0,ifname=vport62,script=no,downscript=no \
-name h2 -daemonize --append "root=/dev/vda rw"

# Test Host
ip tuntap add mode tap vport13
ip link set vport13 up
ip link set vport13 master br1

# htest
qemu-system-x86_64 -kernel vms/bzImagehtest.bin -m 1G \
-drive "file=vms/htest.ext4,if=virtio,format=raw" \
-device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7D' \
-netdev tap,id=net0,ifname=vport13,script=no,downscript=no \
-name htest -daemonize --append "root=/dev/vda rw"
```

#### Router 1 (rt1)

```bash
sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms/bzImagert1.bin -m 1G \
    -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms/rt1.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:71' -netdev tap,id=net0,ifname=vport11,script=no,downscript=no \
    -device virtio-net-pci,netdev=net1,mac='12:34:56:AB:CD:72' -netdev tap,id=net1,ifname=vport21,script=no,downscript=no \
    -device virtio-net-pci,netdev=net2,mac='12:34:56:AB:CD:73' -netdev tap,id=net2,ifname=vport31,script=no,downscript=no \
    -name rt1 -daemonize --append "root=/dev/vda rw"
```

#### Router 2 (rt2)

```bash
sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms/bzImagert2.bin -m 1G \
    -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms/rt2.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:74' -netdev tap,id=net0,ifname=vport22,script=no,downscript=no \
    -device virtio-net-pci,netdev=net1,mac='12:34:56:AB:CD:75' -netdev tap,id=net1,ifname=vport42,script=no,downscript=no \
    -name rt2 -daemonize --append "root=/dev/vda rw"
```

#### Router 3 (rt3)

```bash
sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms/bzImagert3.bin -m 1G \
    -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms/rt3.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:76' -netdev tap,id=net0,ifname=vport32,script=no,downscript=no \
    -device virtio-net-pci,netdev=net1,mac='12:34:56:AB:CD:77' -netdev tap,id=net1,ifname=vport52,script=no,downscript=no \
    -name rt3 -daemonize --append "root=/dev/vda rw"
```

#### Router 4 (rt4)

```bash
sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms/bzImagert4.bin -m 1G \
    -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms/rt4.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:78' -netdev tap,id=net0,ifname=vport41,script=no,downscript=no \
    -device virtio-net-pci,netdev=net1,mac='12:34:56:AB:CD:79' -netdev tap,id=net1,ifname=vport51,script=no,downscript=no \
    -device virtio-net-pci,netdev=net2,mac='12:34:56:AB:CD:7A' -netdev tap,id=net2,ifname=vport61,script=no,downscript=no \
    -name rt4 -daemonize --append "root=/dev/vda rw"
```

#### Host 1 (h1)

```bash
sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms/bzImageh1.bin -m 1G \
    -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms/h1.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7B' -netdev tap,id=net0,ifname=vport12,script=no,downscript=no \
    -name h1 -daemonize --append "root=/dev/vda rw"
```

#### Host 2 (h2)

```bash
sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms/bzImageh2.bin -m 1G \
    -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms/h2.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7C' -netdev tap,id=net0,ifname=vport62,script=no,downscript=no \
    -name h2 -daemonize --append "root=/dev/vda rw"
```

#### Test Host (htest)

```bash
ip tuntap add mode tap vport13
ip link set vport13 up
ip link set vport13 master br1

sudo qemu-system-x86_64 -kernel /home/$USER/yocto2024/<release-name>/saved-images/vms/bzImagehtest.bin -m 1G \
    -drive "file=/home/$USER/yocto2024/<release-name>/saved-images/vms/htest.ext4,if=virtio,format=raw" \
    -device virtio-net-pci,netdev=net0,mac='12:34:56:AB:CD:7D' -netdev tap,id=net0,ifname=vport13,script=no,downscript=no \
    -name htest -daemonize --append "root=/dev/vda rw"
```

### Cleanup Script

```bash
#!/bin/bash

# Delete the virtual ethernet tunnel
ip link set dev veth0 nomaster
ip link del dev veth0

# Delete htest port
ip link set dev vport13 nomaster
ip tuntap del mode tap vport13

# Delete bridges and TAP interfaces
for i in $(seq 1 6)
do
    for j in $(seq 1 2)
    do
        ip link set dev vport${i}${j} nomaster
        ip tuntap del mode tap "vport${i}${j}"
    done
    ip link delete dev br${i}
done
```

---

## Network Configuration Notes

### Enabling IP Forwarding on All Routers

Edit the sysctl configuration to enable IP forwarding:

```bash
echo "net.ipv4.ip_forward = 1" >> /etc/sysctl.conf
sysctl -p
```

### Host 1 Configuration

```bash
# /etc/network/interfaces -- configuration file for ifup(8), ifdown(8)

auto lo eth0
iface lo inet loopback

iface eth0 inet static
    address 10.20.10.2
    netmask 255.255.255.0
    broadcast 10.20.10.255
    network 10.20.10.0

up route add default gw 10.20.10.1 dev eth0
```

### Router 1 Configuration

```bash
# /etc/network/interfaces -- configuration file for ifup(8), ifdown(8)

auto lo eth0 eth1 eth2
iface lo inet loopback

iface eth0 inet static
    address 10.20.10.1
    netmask 255.255.255.0
    broadcast 10.20.10.255
    network 10.20.10.0

iface eth1 inet static
    address 10.20.20.1
    netmask 255.255.255.0
    broadcast 10.20.20.255
    network 10.20.20.0

iface eth2 inet static
    address 10.20.30.1
    netmask 255.255.255.0
    broadcast 

10.20.30.255
    network 10.20.30.0

# static route
up route add -net 10.20.60.0/24 gw 10.20.20.2 dev eth1
up route add -net 10.20.40.0/24 gw 10.20.20.2 dev eth1
up route add -net 10.20.50.0/24 gw 10.20.30.2 dev eth2
```

### Router 2 Configuration

```bash
# /etc/network/interfaces -- configuration file for ifup(8), ifdown(8)

auto lo eth0 eth1
iface lo inet loopback

iface eth0 inet static
    address 10.20.20.2
    netmask 255.255.255.0
    broadcast 10.20.20.255
    network 10.20.20.0

iface eth1 inet static
    address 10.20.40.2
    netmask 255.255.255.0
    broadcast 10.20.40.255
    network 10.20.40.0

# static route
up route add -net 10.20.10.0/24 gw 10.20.20.1 dev eth0
up route add -net 10.20.60.0/24 gw 10.20.40.1 dev eth1
```

### Router 3 Configuration

```bash
# /etc/network/interfaces -- configuration file for ifup(8), ifdown(8)

auto lo eth0 eth1
iface lo inet loopback

iface eth0 inet static
    address 10.20.30.2
    netmask 255.255.255.0
    broadcast 10.20.30.255
    network 10.20.30.0

iface eth1 inet static
    address 10.20.50.2
    netmask 255.255.255.0
    broadcast 10.20.50.255
    network 10.20.50.0

# static route
up route add -net 10.20.10.0/24 gw 10.20.30.1 dev eth0
up route add -net 10.20.60.0/24 gw 10.20.50.1 dev eth1
```

### Router 4 Configuration

```bash
# /etc/network/interfaces -- configuration file for ifup(8), ifdown(8)

auto lo eth0 eth1 eth2
iface lo inet loopback

iface eth0 inet static
    address 10.20.40.1
    netmask 255.255.255.0
    broadcast 10.20.40.255
    network 10.20.40.0

iface eth1 inet static
    address 10.20.50.1
    netmask 255.255.255.0
    broadcast 10.20.50.255
    network 10.20.50.0

iface eth2 inet static
    address 10.20.60.1
    netmask 255.255.255.0
    broadcast 10.20.60.255
    network 10.20.60.0

# static route
up route add -net 10.20.10.0/24 gw 10.20.40.2 dev eth0
up route add -net 10.20.20.0/24 gw 10.20.40.2 dev eth0
up route add -net 10.20.30.0/24 gw 10.20.50.2 dev eth1
```

### Host 2 Configuration

```bash
# /etc/network/interfaces -- configuration file for ifup(8), ifdown(8)

auto lo eth0
iface lo inet loopback

iface eth0 inet static
    address 10.20.60.2
    netmask 255.255.255.0
    broadcast 10.20.60.255
    network 10.20.60.0

up route add default gw 10.20.60.1 dev eth0
```

---

## Useful Resources

- [Introduction to VirtIO Networking and vhost-net](https://www.redhat.com/en/blog/introduction-virtio-networking-and-vhost-net)
- [Deep Dive into VirtIO Networking and vhost-net](https://www.redhat.com/en/blog/deep-dive-virtio-networking-and-vhost-net)
- [Linux Driver Implementer’s API Guide](https://www.kernel.org/doc/html/v4.14/driver-api/basics.html)
- [QEMU Networking Documentation](https://wiki.qemu.org/Documentation/Networking)
- [Cisco's Introduction to NAT](https://www.cisco.com/c/en/us/products/routers/network-address-translation.html)

---

This guide provides a comprehensive overview of advanced network virtualization and routing using QEMU, emphasizing high-performance networking with VirtIO and vhost. It includes detailed scripts and configurations for setting up a robust testing environment with multiple VMs, enabling in-depth simulation and testing of complex network scenarios.
