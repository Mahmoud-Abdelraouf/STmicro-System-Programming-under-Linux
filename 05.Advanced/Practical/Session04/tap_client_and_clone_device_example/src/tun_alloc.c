/**
 * @file tun_alloc.c
 * @brief Function to allocate and configure a TAP device.
 */

#include "tap_device_client.h"

int tun_alloc(char *dev, int flags) {
    struct ifreq ifr;
    int fd, err;
    char *clonedev = "/dev/net/tun";

    // Open the clone device
    if ((fd = open(clonedev, O_RDWR)) < 0) {
        return fd;
    }

    // Preparation of the struct ifr, of type "struct ifreq"
    memset(&ifr, 0, sizeof(ifr));

    // IFF_TUN or IFF_TAP, plus maybe IFF_NO_PI
    ifr.ifr_ifru.ifru_flags = flags;
    if (*dev) {
        // If a device name was specified, put it in the structure; otherwise,
        // the kernel will try to allocate the "next" device of the specified type
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    }
    // Try to create the device
    if ((err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0) {
        close(fd);
        return err;
    }
    // If the operation was successful, write back the name of the interface to the variable "dev"
    // so the caller can know it. Note that the caller MUST reserve space in *dev (see calling code below)
    strcpy(dev, ifr.ifr_name);

    // This is the special file descriptor that the caller will use to talk with the virtual interface
    return fd;
}

