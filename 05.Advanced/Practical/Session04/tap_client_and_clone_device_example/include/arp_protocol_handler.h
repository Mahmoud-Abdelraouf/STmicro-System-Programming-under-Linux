/**
 * @file arp_protocol_handler.h
 * @brief Header file for ARP (Address Resolution Protocol) handling.
 */

#ifndef ARP_H
#define ARP_H

#include "ipv4_protocol_handler.h"

/// Time in minutes to check the ARP table entries
#define ARP_TABLE_TIME_TO_CHECK   2    

/// Time in minutes to delete the ARP table entries
#define ARP_TABLE_TIME_TO_DELETE 10    

/**
 * @brief Structure representing an ARP packet.
 *
 * This structure contains all the necessary fields for an ARP packet, 
 * including hardware and protocol address types, sizes, operation, 
 * and MAC and IP addresses for both source and destination.
 *
 * The `__attribute__((packed))` ensures that the compiler does not add 
 * any padding between the fields of the structure. This is important 
 * because ARP packets have a specific format that must be followed 
 * exactly when sending and receiving packets over the network.
 */
typedef struct
{
    uint16_t hardware_addresstype;    ///< Type of hardware address
    uint16_t protocol_addresstype;    ///< Type of protocol address
    uint8_t  hardware_addresssize;    ///< Size of hardware address
    uint8_t  protocol_addresssize;    ///< Size of protocol address
    uint16_t operation;               ///< ARP operation (1 for request, 2 for reply)
    uint8_t  source_mac[6];           ///< Source MAC address
    IP4_t    sourceIP;                ///< Source IP address
    uint8_t  dest_mac[6];             ///< Destination MAC address
    IP4_t    destIP;                  ///< Destination IP address
} __attribute__((packed)) arpPacket_t;

#endif // ARP_H
