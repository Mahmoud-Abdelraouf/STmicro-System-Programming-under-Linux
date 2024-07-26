/**
 * @file icmp_protocol_handler.h
 * @brief Header file for ICMP (Internet Control Message Protocol) handling.
 */

#ifndef ICMP_H
#define ICMP_H

/// ICMP message types
#define ICMP_ECHO_REPLY                     0       ///< Echo Reply
#define ICMP_DESTINATION_UNREACHABLE        3       ///< Destination Unreachable
#define ICMP_SOURCE_QUENCH                  4       ///< Source Quench
#define ICMP_REDIRECT                       5       ///< Redirect
#define ICMP_ECHO_REQUEST                   8       ///< Echo Request
#define ICMP_ROUTER_ADVERTISEMENT           9       ///< Router Advertisement
#define ICMP_ROUTER_SOLICITATION           10       ///< Router Solicitation
#define ICMP_TIME_EXEEDED                  11       ///< Time Exceeded
#define ICMP_PARAMETER_PROBLEM             12       ///< Parameter Problem
#define ICMP_TIMESTAMP                     13       ///< Timestamp
#define ICMP_TIMESTAMP_REPLY               14       ///< Timestamp Reply
#define ICMP_INFORMATION_REQUEST           15       ///< Information Request
#define ICMP_INFORMATION_REPLY             16       ///< Information Reply
#define ICMP_ADDRESS_MASK_REQUEST          17       ///< Address Mask Request
#define ICMP_ADDRESS_MASK_REPLY            18       ///< Address Mask Reply
#define ICMP_TRACEROUTE                    30       ///< Traceroute
#define ICMP_DATAGRAM_CONVERSION_ERROR     31       ///< Datagram Conversion Error
#define ICMP_MOBILE_HOST_REDIRECT          32       ///< Mobile Host Redirect
#define ICMP_WHERE_ARE_YOU                 33       ///< Originally IPv6 Where-Are-You (replaced by ICMPv6)
#define ICMP_I_AM_HERE                     34       ///< Originally IPv6 I-Am-Here (replaced by ICMPv6)
#define ICMP_MOBILE_REGISTRATION_REQUEST   35       ///< Mobile Registration Request
#define ICMP_MOBILE_REGISTRATION_REPLY     36       ///< Mobile Registration Reply
#define ICMP_DOMAIN_NAME_REQUEST           37       ///< Domain Name Request
#define ICMP_DOMAIN_NAME_REPLY             38       ///< Domain Name Reply
#define ICMP_SKIP                          39       ///< SKIP
#define ICMP_PHOTURIS                      40       ///< Photuris
#define ICMP_SEAMOBY                       41       ///< ICMP messages utilized by experimental mobility protocols such as Seamoby

/**
 * @brief Structure representing an ICMP header.
 *
 * This structure contains the essential fields for an ICMP message,
 * including the type, code, checksum, identifier, and sequence number.
 *
 * The `__attribute__((packed))` ensures that the compiler does not add
 * any padding between the fields of the structure. This is important
 * because ICMP messages have a specific format that must be followed
 * exactly when sending and receiving messages over the network.
 */
typedef struct {
    uint8_t type;        ///< ICMP message type
    uint8_t code;        ///< ICMP message code
    uint16_t checksum;   ///< ICMP message checksum
    uint16_t id;         ///< ICMP message identifier
    uint16_t seqnumber;  ///< ICMP message sequence number
} __attribute__((packed)) icmpheader_t;

#endif // ICMP_H

