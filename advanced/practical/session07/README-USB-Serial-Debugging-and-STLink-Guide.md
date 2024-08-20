# **USB and Serial Device Identification and Debugging Guide**

This guide provides a comprehensive overview of commands, tools, and steps to identify, interact with, and debug USB and serial devices on a Linux system. The primary focus is on ST-Link devices and tools such as OpenOCD, ST-Link Utilities, and Minicom.

## **Table of Contents**

1. [Identifying USB Devices](#1-identifying-usb-devices)
2. [Mapping USB Devices to `/dev/bus/usb/`](#2-mapping-usb-devices-to-devbususb)
3. [Identifying Serial Devices (`/dev/tty*`)](#3-identifying-serial-devices-devtty)
4. [Using `udevadm` to Monitor Device Events](#4-using-udevadm-to-monitor-device-events)
5. [Identifying HIDRAW Devices (`/dev/hidraw*`)](#5-identifying-hidraw-devices-devhidraw)
6. [Debugging with ST-Link Tools](#6-debugging-with-st-link-tools)
7. [Using OpenOCD for STM32 Debugging](#7-using-openocd-for-stm32-debugging)
8. [Interacting with Serial Devices Using Minicom](#8-interacting-with-serial-devices-using-minicom)
9. [Useful Commands Overview](#9-useful-commands-overview)

---

## **1. Identifying USB Devices**

To identify USB devices connected to your system, use the `lsusb` command. This command lists all USB devices and provides information such as the device ID, manufacturer, and description.

### **Example**

```bash
lsusb
```

### **Output**

```
Bus 003 Device 013: ID 0483:3748 STMicroelectronics ST-LINK/V2
Bus 003 Device 002: ID 0cf3:e300 Qualcomm Atheros Communications QCA61x4 Bluetooth 4.0
```

### **Explanation**

- **Bus 003 Device 013**: Indicates the bus and device number.
- **ID 0483:3748**: Vendor and product ID for the ST-Link device.

---

## **2. Mapping USB Devices to `/dev/bus/usb/`**

After identifying a USB device using `lsusb`, you can map it to a file in `/dev/bus/usb/` using the bus and device numbers provided by `lsusb`.

### **Example**

```bash
ls /dev/bus/usb/003/
```

### **Output**

```
001  002  013  014
```

### **Explanation**

- The file `013` corresponds to the ST-Link device as identified by `lsusb`.

---

## **3. Identifying Serial Devices (`/dev/tty*`)**

Serial devices are usually listed under `/dev/tty*`. These could include devices like `/dev/ttyUSB0`, `/dev/ttyACM0`, or `/dev/ttyS0`. If you have many such devices, identifying the correct one can be tricky.

### **Checking Available Serial Devices**

```bash
ls /dev/tty*
```

### **Output**

```
/dev/tty        /dev/tty10      /dev/tty20      /dev/tty30      /dev/tty40
/dev/tty0       /dev/tty11      /dev/tty21      /dev/tty31      /dev/tty41
...
/dev/ttyS0      /dev/ttyS1      /dev/ttyS2      /dev/ttyS3
```

### **Identifying Serial Devices with `dmesg`**

```bash
sudo dmesg | grep ttyS
```

### **Explanation**

This command shows kernel messages related to serial ports, which helps in identifying the specific serial device associated with your hardware.

---

## **4. Using `udevadm` to Monitor Device Events**

The `udevadm` command is useful for monitoring device events in real-time, especially when connecting or disconnecting USB devices.

### **Monitoring Device Events**

```bash
sudo udevadm monitor --property --udev
```

### **Explanation**

- Run this command before connecting the device to observe which `/dev/` entry is created when the device is plugged in.

---

## **5. Identifying HIDRAW Devices (`/dev/hidraw*`)**

If your ST-Link or another device is recognized as a generic HID device, it will be listed under `/dev/hidraw*`. You can identify which `hidraw` device corresponds to your hardware.

### **Listing HIDRAW Devices**

```bash
ls /dev/hidraw*
```

### **Output**

```
/dev/hidraw0  /dev/hidraw1
```

### **Identifying HIDRAW Device Information**

```bash
sudo udevadm info --query=all --name=/dev/hidraw0
```

### **Explanation**

- This command will provide detailed information about the `hidraw0` device, helping to confirm if it is your ST-Link.

---

## **6. Debugging with ST-Link Tools**

The ST-Link tools provide utilities to interact with and debug STM32 devices. These include `st-info`, `st-util`, and others.

### **Installing ST-Link Tools**

```bash
sudo apt-get install stlink-tools
```

### **Using `st-info` to Get ST-Link Information**

```bash
st-info --probe
```

### **Output**

```
Found 1 stlink programmers
  version:    V2J45S7
  serial:     51004400060000544334544E
  flash:      131072 (pagesize: 1024)
  sram:       20480
  chipid:     0x0410
  descr:      F1xx Medium-density
```

### **Using `st-util` to Start a GDB Server**

```bash
st-util
```

### **Explanation**

- `st-util` starts a GDB server, allowing you to connect with GDB for debugging.

---

## **7. Using OpenOCD for STM32 Debugging**

OpenOCD is an open-source tool that provides debugging, in-system programming, and boundary-scan testing for embedded devices.

### **Installing OpenOCD**

```bash
sudo apt-get install openocd
```

### **Starting OpenOCD with ST-Link**

```bash
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg
```

### **Explanation**

- This command starts OpenOCD using the ST-Link interface configuration and targets the STM32F1 series.

### **Connecting GDB to OpenOCD**

```bash
arm-none-eabi-gdb
target remote localhost:3333
```

### **Explanation**

- Connect to the OpenOCD GDB server running on port 3333.

---

## **8. Interacting with Serial Devices Using Minicom**

Minicom is a text-based modem control and terminal emulation program that can be used to interact with serial devices.

### **Installing Minicom**

```bash
sudo apt-get install minicom
```

### **Starting Minicom with a Specific Serial Device**

```bash
minicom -b 115200 -D /dev/ttyS0
```

### **Explanation**

- `-b 115200`: Sets the baud rate to 115200.
- `-D /dev/ttyS0`: Specifies the serial device to use.

### **Exiting Minicom**

Press `Ctrl + A`, then `X` to exit Minicom.

---

## **9. Useful Commands Overview**

Here’s a quick overview of the useful commands discussed:

### **Listing USB Devices**

```bash
lsusb
```

### **Mapping USB Devices to `/dev/bus/usb/`**

```bash
ls /dev/bus/usb/BUS_NUMBER/
```

### **Listing Serial Devices**

```bash
ls /dev/tty*
```

### **Identifying Serial Devices Using `dmesg`**

```bash
sudo dmesg | grep ttyS
```

### **Monitoring Device Events with `udevadm`**

```bash
sudo udevadm monitor --property --udev
```

### **Identifying HIDRAW Devices**

```bash
sudo udevadm info --query=all --name=/dev/hidrawX
```

### **Using ST-Link Tools**

- **Probing ST-Link Devices:**
  ```bash
  st-info --probe
  ```
- **Starting GDB Server:**
  ```bash
  st-util
  ```

### **Using OpenOCD**

- **Starting OpenOCD:**
  ```bash
  openocd -f interface/stlink.cfg -f target/stm32f1x.cfg
  ```
- **Connecting GDB:**
  ```bash
  arm-none-eabi-gdb
  target remote localhost:3333
  ```

### **Using Minicom**

- **Starting Minicom:**
  ```bash
  minicom -b 115200 -D /dev/ttyS0
  ```
- **Exiting Minicom:**
  - Press `Ctrl + A`, then `X`.

