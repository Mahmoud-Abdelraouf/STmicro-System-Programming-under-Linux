# SerialHexUploader

## Overview
`SerialHexUploader` is a program designed to upload Intel HEX files via a serial port connection. It reads lines from the HEX file and sends them over the serial port to a connected device, waiting for acknowledgment responses to ensure successful transmission.

## Files
- `SerialHexUploader.c`: The main source code file containing the implementation of `SerialHexUploader`.

## Functionality
- `main`: The main function responsible for opening the serial port, reading the HEX file, sending data over the serial port, and handling acknowledgment responses.
- `start_Communication`: Function to initiate communication with the device and handle acknowledgment responses.
- `read_until_response`: Function to read data from the serial port until an expected response is received.

## How to Use
1. Compile the `SerialHexUploader` source code using a C compiler. For example:
    ```bash
    gcc -o SerialHexUploader shu.c
    ```
2. Run `SerialHexUploader` with the Intel HEX file as an argument. For example:
    ```bash
    ./SerialHexUploader file.hex
    ```

## Notes
- Ensure you have the appropriate permissions to access the serial port (usually requires root privileges).
- Make sure to specify the correct serial port device path in the code (`SERIAL_PORT` constant).
- This tool is for uploading Intel HEX files to devices that support serial communication protocols.

## Author
- Mahmoud Abdelraouf Mahmoud

## Version
- 0.1

## License
This project is licensed under the MIT License - see the [LICENSE](../../LICENSE) file for details.