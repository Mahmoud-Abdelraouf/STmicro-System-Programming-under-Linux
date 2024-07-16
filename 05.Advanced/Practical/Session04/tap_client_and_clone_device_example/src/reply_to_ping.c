/**
 * @file reply_to_ping.c
 * @brief Function to send a reply to a received ping (ICMP Echo Request).
 */

#include "tap_device_client.h"

void replyToPing(int fd, unsigned char* buff, int buffSize) {
    uint8_t myMacAddress[6] = {0xe4, 0xfa, 0xff, 0xaa, 0xba, 0xcc};
    static uint16_t id = 0;
    int nWrite;
    ethernet_t *ethernetPacketPointer;
    unsigned char copy_buff[1500];

    ethernetPacketPointer = (ethernet_t *) buff;
    memcpy(ethernetPacketPointer->recv_mac, ethernetPacketPointer->send_mac, 6);
    memcpy(ethernetPacketPointer->send_mac, myMacAddress, 6);

    // ARP Protocol
    if (ntohs(ethernetPacketPointer->type_len) == 0x0806) {
        arpPacket_t *arpPacketPointer;
        uint32_t tempIP;

        arpPacketPointer = (arpPacket_t *)(buff + sizeof(ethernet_t));
        tempIP = arpPacketPointer->destIP.iIP4;
        arpPacketPointer->destIP.iIP4 = arpPacketPointer->sourceIP.iIP4;
        arpPacketPointer->sourceIP.iIP4 = tempIP;

        // 1 for Request, 2 for Reply
        arpPacketPointer->operation = ntohs(2);
        memcpy(arpPacketPointer->dest_mac, arpPacketPointer->source_mac, 6);
        memcpy(arpPacketPointer->source_mac, myMacAddress, 6);

        nWrite = write(fd, buff, buffSize);
        if (nWrite < 0) {
            perror("Writing to interface");
            close(fd);
            exit(1);
        }
    }
    // IPv4 Protocol
    else if (ntohs(ethernetPacketPointer->type_len) == 0x0800) {
        ipv4Packet_t *ipv4PacketPointer;
        ipv4Packet_t *ipv4PacketPointer_copy;
        uint32_t tempIP;
        uint16_t tmpchecksum;
        ipv4PacketPointer = (ipv4Packet_t *)(buff + sizeof(ethernet_t));
        printf("IPv4 checksum=%x\n", ipv4PacketPointer->checksum);
        memcpy(copy_buff, buff, buffSize);
        ipv4PacketPointer_copy = (ipv4Packet_t *)(copy_buff + sizeof(ethernet_t));
        ipv4PacketPointer_copy->checksum = 0;
        printf("IPv4 checksum computed=%x\n", htons(internetChecksum(ipv4PacketPointer_copy, sizeof(ipv4Packet_t), 0)));

        // ICMP Protocol Only
        if (ipv4PacketPointer->protocol == 1) {
            tempIP = ipv4PacketPointer->destIP.iIP4;
            ipv4PacketPointer->destIP.iIP4 = ipv4PacketPointer->sourceIP.iIP4;
            ipv4PacketPointer->sourceIP.iIP4 = tempIP;
            ipv4PacketPointer->identification = ++id;
            ipv4PacketPointer->checksum = 0;
            ipv4PacketPointer->checksum = htons(internetChecksum(ipv4PacketPointer, sizeof(ipv4Packet_t), 0));
            int icmpDataLength = buffSize - (sizeof(ethernet_t) + sizeof(ipv4Packet_t) + sizeof(icmpheader_t));
            icmpheader_t *icmpPacketPointer;
            icmpPacketPointer = (icmpheader_t *)(buff + sizeof(ethernet_t) + sizeof(ipv4Packet_t));
            icmpPacketPointer->type = ICMP_ECHO_REPLY;
            printf("--------ICMP CHECKSUM \n");
            icmpPacketPointer->checksum = 0;
            tmpchecksum = internetChecksum(icmpPacketPointer, sizeof(icmpheader_t) + icmpDataLength, 0);
            icmpPacketPointer->checksum = htons(tmpchecksum);
            printf("debug id=%d checksum=%x\n", id, tmpchecksum);
            printf("debug icmpPacketPointer->id=%d icmpPacketPointer->seqnumber=%d\n", icmpPacketPointer->id, icmpPacketPointer->seqnumber);
            nWrite = write(fd, buff, buffSize);
            if (nWrite < 0) {
                perror("Writing to interface");
                close(fd);
                exit(1);
            }
        }
    }
}

