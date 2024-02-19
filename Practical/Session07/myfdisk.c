#define _LARGEFILE64_SOURCE
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

void process_partition_table(char *device, uint8_t paration_number, PartitionEntry *table_entry_ptr) {
    /**< Print the details of each partition entry */ 
    printf("%-8s%-4d  %-4c %-10u %-10u %-10u %06.2fG %5X\n",
           device,                                                        /**< Device name */ 
           paration_number + 1,                                           /**< Partition number */ 
           table_entry_ptr->status == 0x80 ? '*' : ' ',                   /**< Boot flag */ 
           table_entry_ptr->lba,                                          /**< Start sector */ 
           table_entry_ptr->lba + table_entry_ptr->sector_count - 1,      /**< End sector */ 
           table_entry_ptr->sector_count,                                 /**< Number of sectors */ 
           (double)table_entry_ptr->sector_count * 512 / (1024 * 1024 * 1024), /**< Size in GB */ 
           table_entry_ptr->partition_type);                              /**< Partition type */ 
}

void read_ebr_partition_table(char *device, uint32_t ebr_lba, int ebr_number) {
    char buf[512];  /**< Buffer to store the read data from the disk */ 

    /**< Open the disk device file for reading */ 
    int fd = open(device, O_RDONLY);

    /**< Check if the file opened successfully */
    if (fd == -1) {
        fprintf(stderr, "myfdisk: cannot open '%s': Permission denied\n", device);
        return;
    }

    /**< Read the EBR from the disk into the buffer */ 
    off64_t file_offset = ((off64_t)(ebr_lba)) * 512; /**< Calculate the offset for lseek64 */ 
    off64_t current_offset = lseek64(fd, file_offset, SEEK_SET); /**< Move to the position of the EBR */ 
    if (current_offset != file_offset) {
        perror("Error seeking file");
        close(fd);
        return;
    }
    
    ssize_t bytes_read = read(fd, buf, 512);
    
    /**< Check if reading from the file was successful */
    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd); /**< Close the file descriptor before returning */ 
        return;
    }

    /**< Pointer to the partition table entries within the buffer */ 
    PartitionEntry *table_entry_ptr = ((PartitionEntry *) &buf[446]);
    table_entry_ptr[0].lba += ebr_lba;
    process_partition_table(device, ebr_number, &table_entry_ptr[0]);
    
    while(1) {
    	if(table_entry_ptr[1].sector_count == 0) {
    	    break;
    	}
        /**< Read the EBR from the disk into the buffer */ 
    	off64_t offset = ((off64_t)(ebr_lba + table_entry_ptr[1].lba)); /**< Calculate the offset for lseek64 */ 
    	off64_t current_offset = lseek64(fd, offset * (off64_t)512, SEEK_SET); /**< Move to the position of the EBR */ 
    
    ssize_t bytes_read = read(fd, buf, 512);
    
    /**< Check if reading from the file was successful */
    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd); /**< Close the file descriptor before returning */ 
        return;
    }

    /**< Pointer to the partition table entries within the buffer */ 
    PartitionEntry *table_entry_ptr = ((PartitionEntry *) &buf[446]);
    table_entry_ptr[0].lba += offset;
    process_partition_table(device, ebr_number, &table_entry_ptr[0]);
    

    
    }
    
    /**< Close the file descriptor */ 
    close(fd);
}

void read_partition_table(char *device) {
    char buf[512];  /**< Buffer to store the read data from the disk */ 

    /**< Open the disk device file for reading */ 
    int fd = open(device, O_RDONLY);

    /**< Check if the file opened successfully */
    if (fd == -1) {
        fprintf(stderr, "myfdisk: cannot open '%s': Permission denied\n", device);
        return;
    }

    /**< Read the first 512 bytes (MBR) from the disk into the buffer */ 
    ssize_t bytes_read = read(fd, buf, 512);
    
    /**< Check if reading from the file was successful */
    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd); /**< Close the file descriptor before returning */ 
        return;
    }

    /**< Pointer to the partition table entries within the buffer */ 
    PartitionEntry *table_entry_ptr = ((PartitionEntry *) &buf[446]);

    /**< Print the header for the partition table information with bold text */ 
    printf("\033[1m%-10s %5s   %-10s %-10s %-10s %-10s %-5s %-5s\033[0m\n", "Device",
           "Boot", "Start", "End", "Sectors", "Size", "Id", "Type");

    /**< Iterate over each partition entry in the partition table */ 
    for (int i = 0; i < 4; i++) {
        /**< Print the details of each partition entry */ 
        process_partition_table(device, i, &table_entry_ptr[i]);
        if (table_entry_ptr[i].partition_type == 0x05 && table_entry_ptr[i].sector_count > 0) {
            /**< If the partition type is 0x05 (Extended Partition), read the EBR partition table */ 
            read_ebr_partition_table(device, table_entry_ptr[i].lba, 4);
        }
    }

    close(fd); /**< Close the file descriptor */ 
}

int main(int argc, char **argv) {
    /**< Check if the number of arguments is correct */
    if (argc != 2) {
        printf("Usage: %s <device_file>\n", argv[0]);
        return -1; /**< Return error code -1 for incorrect usage */ 
    }

    read_partition_table(argv[1]);

    return 0;
}

