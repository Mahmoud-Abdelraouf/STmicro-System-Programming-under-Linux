/**
 * @file ipv4_protocol_handler.h
 * @brief Header file for IPv4 (Internet Protocol version 4) handling.
 */

#ifndef IPV4_H
#define IPV4_H

/**
 * @brief Union representing an IPv4 address.
 *
 * This union allows access to an IPv4 address as both an array of 4 bytes
 * and a single 32-bit integer. The `__attribute__((packed))` ensures that
 * the compiler does not add any padding between the fields of the union.
 */
typedef union {
    uint8_t IP4[4];    ///< IPv4 address as an array of 4 bytes
    uint32_t iIP4;     ///< IPv4 address as a single 32-bit integer
} __attribute__((packed)) IP4_t;

/**
 * @brief Structure representing an IPv4 packet.
 *
 * This structure contains the essential fields for an IPv4 packet,
 * including the header length, version, type of service, total length,
 * identification, flags, fragment offset, time to live, protocol,
 * checksum, source IP address, and destination IP address.
 *
 * The `__attribute__((packed))` ensures that the compiler does not add
 * any padding between the fields of the structure. This is important
 * because IPv4 packets have a specific format that must be followed
 * exactly when sending and receiving packets over the network.
 */
typedef struct {
    uint8_t  ipHeaderLength   : 4;    ///< Header length (in 32-bit words)
    uint8_t  version          : 4;    ///< IP version (IPv4)
    uint8_t  typeOfService;           ///< Type of service
    uint16_t length;                  ///< Total length of the packet
    uint16_t identification;          ///< Identification
    uint16_t fragmentation;           ///< Flags and fragment offset
    uint8_t  ttl;                     ///< Time to live
    uint8_t  protocol;                ///< Protocol
    uint16_t checksum;                ///< Header checksum
    IP4_t    sourceIP;                ///< Source IP address
    IP4_t    destIP;                  ///< Destination IP address
} __attribute__((packed)) ipv4Packet_t;

#endif // IPV4_H

