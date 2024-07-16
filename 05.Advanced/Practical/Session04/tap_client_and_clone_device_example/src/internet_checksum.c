/**
 * @file internet_checksum.c
 * @brief Function to calculate the Internet checksum.
 */

#include "tap_device_client.h"

uint16_t internetChecksum(const void* addr, size_t count, uint32_t pseudoHeaderChecksum) {
    uint32_t sum  = pseudoHeaderChecksum;
    const uint8_t* data = addr;

    // Inner loop
    while (count > 1) {
        printf("data[%ld]=%x data[%ld]=%x\n", count, data[0], count - 1, data[1]);
        // Big Endian
        sum   += (data[0] << 8) | data[1];
        data  += 2;
        count -= 2;
    }

    // Add left-over byte, if any
    if (count > 0) {
        sum += data[0] << 8;
    }

    // Fold 32-bit sum to 16 bits
    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }
    printf("-----Checksum return=%x\n", (~sum & 0xFFFF));
    return ~sum & 0xFFFF;
}

