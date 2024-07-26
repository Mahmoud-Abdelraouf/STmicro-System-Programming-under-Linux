/**
 * @file tap_device_client.c
 * @brief Main program for the TAP device client.
 */

#include "tap_device_client.h"

int main(int argc, char** argv) {
    char tap_name[IFNAMSIZ];
    int tap_fd;
    unsigned char buffer[1500];
    int nread;
    int i;

    // Connect to the tap device
    strcpy(tap_name, "tap4");
    tap_fd = tun_alloc(tap_name, IFF_TAP | IFF_NO_PI);

    if (tap_fd < 0) {
        perror("Allocating interface");
        exit(1);
    }

    // Read data coming from the kernel
    while (1) {
        // Buffer should be at least the MTU size of the interface, eg 1500 bytes
        nread = read(tap_fd, buffer, sizeof(buffer));
        if (nread < 0) {
            perror("Reading from interface");
            close(tap_fd);
            exit(1);
        }

        printf("\n =========================================================\n");
        for (i = 0; i < nread; i++) {
            printf("%x ", buffer[i]);
            if (!(i % 10)) printf("\n");
        }
        // Send a ping reply
        replyToPing(tap_fd, buffer, nread);
    }
    return 0;
}

