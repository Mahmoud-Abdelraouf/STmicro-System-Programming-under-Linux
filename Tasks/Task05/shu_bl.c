/**
 * @file SerialHexUploader.c
 * @brief SerialHexUploader - A program to upload Intel HEX files via serial port.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <sys/time.h>
#include <sys/select.h>

#define SERIAL_PORT "/dev/ttyUSB0"	/**< Serial port device path */
#define RESPONSE_TIMEOUT_SEC 1		/**< Timeout in seconds for response */

/**
 * @brief Reads data from the specified file descriptor until the expected response is received.
 * 
 * This function reads data from the given file descriptor until the specified expected response
 * is received. It waits until the expected response is encountered or until an error occurs.
 * 
 * @param fd The file descriptor to read data from.
 * @param expected_response The expected response string to wait for.
 * @param resend_flag Flag indicating whether to request a resend if the expected response is not received (1 to request resend, 0 otherwise).
 * @return Returns 0 on success (response received), -1 on failure (error or timeout), or 1 if a resend request is triggered.
 */
int start_Communication(int fd, const char *expected_response);

/**
 * @brief Reads data from the specified file descriptor until the expected response is received.
 * 
 * This function reads data from the given file descriptor until the specified expected response
 * is received. It waits until the expected response is encountered or until an error occurs.
 * 
 * @param fd The file descriptor to read data from.
 * @param expected_response The expected response string to wait for.
 * @return Returns 0 on success (response received), -1 on failure (error or timeout).
 */
int read_until_response(int fd, const char *expected_response);

/**
 * @brief Main function to upload Intel HEX files via serial port.
 * @return Returns 0 on success, -1 on failure.
 */
int main(int argc, char *argv[])
{

    if (argc != 2) {
	printf("Usage: %s <HEX_File>\n", argv[0]);
	return -1;
    }

    int fd; /**< File descriptor for the serial port */
    struct termios serialPortSettings; /**< Structure to hold the settings for the serial port */

    /**< Open the serial port in blocking mode */
    fd = open(SERIAL_PORT, O_RDWR);
    if (fd == -1) {
	perror("Error opening serial port");
	exit(EXIT_FAILURE);
    }

    /**< Get the current serial port settings */
    tcgetattr(fd, &serialPortSettings);

    /**< Set the baud rate to 9600 */
    cfsetispeed(&serialPortSettings, B9600);
    cfsetospeed(&serialPortSettings, B9600);

    /**< Set other serial port settings */
    serialPortSettings.c_cflag &= ~PARENB;   /**< No parity */
    serialPortSettings.c_cflag &= ~CSTOPB;   /**< One stop bit */
    serialPortSettings.c_cflag &= ~CSIZE;    /**< Clear data size bits */
    serialPortSettings.c_cflag |= CS8;	     /**< 8 bits per byte */
    serialPortSettings.c_cflag &= ~CRTSCTS;  /**< No hardware flow control */
    serialPortSettings.c_cflag |= CREAD | CLOCAL; /**< Enable receiver, ignore control lines */

    /**< Apply the new settings */
    tcsetattr(fd, TCSANOW, &serialPortSettings);

    /**< Open the hex file */
    FILE *hexFile = fopen(argv[1], "r");
    if (hexFile == NULL) {
	perror("Error opening hex file");
	close(fd);
	exit(EXIT_FAILURE);
    }

    /**< Read lines from the hex file and send them over serial */
    char line[256]; /**< Buffer to store each line read from the hex file */
    size_t index = 0; /**< Index to keep track of the current position in the line buffer */
    int cLine; /**< Variable to store the character read from the hex file for each line */
    int response_status = 0; 
    int lineCount = 0;
    
    printf("Waiting for starting the communication...\n");
    
    do {
        response_status = start_Communication(fd, "str");
        if(response_status == 1) {
            write(fd, "n", strlen("n"));
        } else if(response_status == -1) {
            printf("Failed to start communication.\n"); /**< Print error message if failed to start communication */ 
        } else {
            write(fd, "k", strlen("k"));
        }
    } while(response_status != 0);
    
    sleep(1);
      
    while (1) {
    	printf("---------------------------- Line Number: %d ----------------------------\n", ++lineCount);
        do {
            cLine = fgetc(hexFile);

            if (cLine == EOF) {
                /**< Notify user that flashing is done fully */
                printf("Flash done successfully!\n");

                /**< Close the hex file */
                fclose(hexFile);

                /**< Close the serial port */
                close(fd);

                return 0; /**< Exit the program with success */ 
                
            } else if( cLine == '\n') {
            	/**< Add character to the line buffer */
            	if (write(fd, &cLine, 1) == -1) {
                    fprintf(stderr, "Error writing data to serial port\n"); /**< Print error message if failed to write data to serial port */ 
                    return -1; /**< Exit the program with error */ 
            	}
            	 read_until_response(fd, "ok"); /**< Wait until receiving "ok" response */ 
                printf("---------------------------- End of line: %d ----------------------------\n", lineCount); /**< Print the character being sent */ 
            } else {
            	printf("--------> Sending \'%c\'\n", cLine); /**< Print the character being sent */ 
            	/**< Add character to the line buffer */
            	if (write(fd, &cLine, 1) == -1) {
                    fprintf(stderr, "Error writing data to serial port\n"); /**< Print error message if failed to write data to serial port */ 
                    return -1; /**< Exit the program with error */ 
            	}
            	read_until_response(fd, "ok"); /**< Wait until receiving "ok" response */ 
            }
        } while (cLine != '\n');
        
	printf("Wait untill the parsing of line %d end...\n", lineCount);
        read_until_response(fd, "ok"); /**< Wait until receiving "ok" response */ 
        printf("Parsing of line %d, finished successfully!\n", lineCount);
    }

    return -1; /**< Return -1 (this line should be unreachable since the loop is infinite) */  
}

int start_Communication(int fd, const char *expected_response) {
    char response[10];
    int cmpFlag;

    ssize_t bytesRead = read(fd, response, sizeof(response) - 1);
    if (bytesRead > 0) {
        response[bytesRead] = '\0';
        printf("Received response: %s\n", response);
        if ((cmpFlag = strcmp(response, expected_response)) != 0) {
            fprintf(stderr, "Error: Unexpected response '%s'\n", response);
            printf("Requesting resend...\n");
            return 1; /**< Trigger resend request */ 
        } else {
            printf("Correct Ack: %s :)\n", response);
        }
    } else if (bytesRead == 0) {
        /**< No data available (timeout or closed connection) */ 
        printf("No data available.\n");
        cmpFlag = -1;
    } else {
        /**< Error reading from serial port */ 
        perror("Error reading from serial port");
        cmpFlag = -1;
    }
    
    return cmpFlag;
}

int read_until_response(int fd, const char *expected_response) {
    char response[10];
    int cmpFlag;

    do {
        ssize_t bytesRead = read(fd, response, sizeof(response) - 1);
        if (bytesRead > 0) {
            response[bytesRead] = '\0';
            printf("Received response: %s\n", response);
            if ((cmpFlag = strcmp(response, expected_response)) != 0) {
                fprintf(stderr, "Error: Unexpected response '%s'\n", response);
            } else {
                printf("Correct Ack: %s :)\n", response);
            }
        } else if (bytesRead == 0) {
            /**< No data available (timeout or closed connection) */ 
            printf("No data available.\n");
            cmpFlag = -1;
        } else {
            /**< Error reading from serial port */ 
            perror("Error reading from serial port");
            cmpFlag = -1;
        }
    } while (cmpFlag != 0);

    return cmpFlag;
}
