#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>

typedef struct {
    uint8_t status;            /**< Status of the partition (e.g., active or inactive) */ 
    uint8_t first_chs[3];      /**< CHS (Cylinder-Head-Sector) address of the first sector in the partition */ 
    uint8_t partition_type;    /**< Type of the partition (e.g., FAT32, NTFS) */ 
    uint8_t last_chs[3];       /**< CHS address of the last sector in the partition */ 
    uint32_t lba;              /**< Logical block address of the first sector in the partition */ 
    uint32_t sector_count;     /**< Number of sectors in the partition */ 
} PartitionEntry;

int main(int argc, char **argv)
{
    char buf[512];  /**< Buffer to store the read data from the disk */ 

    /**< Open the disk device file for reading */ 
    int fd = open(argv[1], O_RDONLY);

    /**< Read the first 512 bytes (MBR) from the disk into the buffer */ 
    read(fd, buf, 512);

    /**< Pointer to the partition table entries within the buffer */ 
    PartitionEntry *table_entry_ptr = (PartitionEntry *) & buf[446];

    /**< Print the header for the partition table information */ 
    printf("%-5s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Device",
           "Boot", "Start", "End", "Sectors", "Size", "Id", "Type");

    /**< Iterate over each partition entry in the partition table */ 
    for (int i = 0; i < 4; i++) {
        /**< Print the details of each partition entry */ 
        printf("%s%-5d %-10c %-10u %-10u %-10u %uG      %-10X\n",
               argv[1],
               i + 1,
               table_entry_ptr[i].status == 0x80 ? '*' : ' ',                   /**< Check if partition is bootable */ 
               table_entry_ptr[i].lba,                                          /**< Start sector of the partition */ 
               table_entry_ptr[i].lba + table_entry_ptr[i].sector_count - 1,    /**< End sector of the partition */ 
               table_entry_ptr[i].sector_count,                                 /**< Number of sectors in the partition */ 
               (uint32_t) (((uint64_t) table_entry_ptr[i].sector_count *
                            512) / (1024 * 1024 * 1024)),                       /**< Size of the partition in GB */ 
               table_entry_ptr[i].partition_type);                              /**< Type of the partition */ 
    }

    return 0;
}
