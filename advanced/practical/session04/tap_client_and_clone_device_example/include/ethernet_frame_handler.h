/**
 * @file ethernet_frame_handler.h
 * @brief Header file for Ethernet frame handling.
 */

#ifndef ETHERNET_H
#define ETHERNET_H

/**
 * @brief Structure representing an Ethernet frame.
 *
 * This structure contains the essential fields for an Ethernet frame,
 * including the source and destination MAC addresses and the type/length
 * field.
 *
 * The `__attribute__((packed))` ensures that the compiler does not add
 * any padding between the fields of the structure. This is important
 * because Ethernet frames have a specific format that must be followed
 * exactly when sending and receiving frames over the network.
 */
typedef struct {
    uint8_t recv_mac[6];  ///< Destination MAC address
    uint8_t send_mac[6];  ///< Source MAC address
    uint16_t type_len;    ///< Type (Ethernet II) or Length (IEEE 802.3)
} __attribute__((packed)) ethernet_t;

#endif // ETHERNET_H
