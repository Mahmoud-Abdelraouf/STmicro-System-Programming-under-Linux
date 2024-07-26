/**
 * @file tap_device_client.h
 * @brief Header file for the TAP device client program.
 */

#ifndef TAP_DEVICE_CLIENT_H
#define TAP_DEVICE_CLIENT_H

#include <sys/socket.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "arp_protocol_handler.h"
#include "ethernet_frame_handler.h"
#include "icmp_protocol_handler.h"
#include "ipv4_protocol_handler.h"

/**
 * @brief Allocates and configures a TAP device.
 *
 * @param dev The name of the device to allocate.
 * @param flags Flags for the TAP device.
 * @return File descriptor for the TAP device, or -1 on error.
 */
int tun_alloc(char *dev, int flags);

/**
 * @brief Calculates the Internet checksum.
 *
 * @param addr Pointer to the data to be checksummed.
 * @param count Length of the data in bytes.
 * @param pseudoHeaderChecksum Initial checksum value (usually 0).
 * @return Calculated checksum.
 */
uint16_t internetChecksum(const void* addr, size_t count, uint32_t pseudoHeaderChecksum);

/**
 * @brief Sends a reply to a received ping (ICMP Echo Request).
 *
 * @param fd File descriptor for the TAP device.
 * @param buff Buffer containing the received packet.
 * @param buffSize Size of the received packet.
 */
void replyToPing(int fd, unsigned char *buff, int buffSize);

#endif // TAP_DEVICE_CLIENT_H

