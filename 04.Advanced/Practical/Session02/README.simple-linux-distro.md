# Creating a Simple Linux Distro

This guide outlines the steps to create a basic Linux distribution using QEMU and ARM architecture. The process involves installing necessary tools, configuring and building the Linux kernel, compiling Busybox, creating the RootFS, compressing the file system, and running QEMU with the created file system.

## Cloned Steps Source
The steps provided here are cloned from [Minimalistic Linux System on QEMU ARM](https://lukaszgemborowski.github.io/articles/minimalistic-linux-system-on-qemu-arm.html).

## Installation and Setup

### 1. Install QEMU
```bash
sudo apt install qemu-system-arm
```

### 2. Select ARM Versatile PB board
We will utilize the ARM Versatile PB board for emulation. Refer to the [QEMU documentation](https://www.qemu.org/docs/master/system/arm/versatile.html) for more details.

### 3. Install Cross Compiler
```bash
sudo apt install gcc-arm-linux-gnueabi
```

## Building the Kernel

### 4. Download and Extract Linux Kernel
```bash
wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.7.6.tar.xz
tar xvf linux-6.7.6.tar.xz
```

### 5. Configure Kernel
```bash
cd linux-6.7.6
make O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- versatile_defconfig
```
You can modify the configuration using:
```bash
make O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- menuconfig
```

### 6. Build Kernel and Modules
```bash
time make -j8 O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
time make -j8 modules O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
```

### 7. Install Kernel Modules
```bash
time make -j8 modules_install O=./build/ ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- INSTALL_MOD_PATH=../rootfs
```

## Building Busybox

### 8. Download and Extract Busybox
Download the latest Busybox from [https://busybox.net/](https://busybox.net/) and untar it.

### 9. Compile Busybox
```bash
cd busybox-1.36.1
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- menuconfig
# Enable 'build busybox as a static binary' from Settings
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j8
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- install
```

## Creating the RootFS

### 10. Prepare RootFS
```bash
cd ../rootfs
mkdir -p bin sbin etc proc sys usr/{bin,sbin}
```

### 11. Create Init Script
Create the `init` script:
```bash
vim rootfs/init
```
Fill it with the following content:
```bash
#!/bin/sh
echo -e "\nHello from the init process\n"

mount -tproc none /proc
mount -tsysfs none /sys
mknod -m660 /dev/mem c 1 1

exec /bin/sh
```

### 12. Set Permissions
```bash
chmod +x rootfs/init
```

### 13. Copy Busybox Files
```bash
cp -av busybox-1.36.1/_install/* rootfs/
```

### 14. Create RootFS Directory Structure
```bash
mkdir -pv rootfs/{bin,sbin,etc,proc,sys,usr/{bin,sbin}}
```

## Compressing the File System

### 15. Compress File System
```bash
cd rootfs/
find . -print0 | cpio --null -ov --format=newc | gzip -9 > ../rootfs.cpio.gz
```

## Running QEMU

### 16. Run QEMU
```bash
cd ..
qemu-system-arm -M versatilepb -kernel linux-6.7.6/build/arch/arm/boot/zImage \
                -dtb linux-6.7.6/build/arch/arm/boot/dts/arm/versatile-pb.dtb \
                -initrd rootfs.cpio.gz -serial stdio -append "root=/dev/mem serial=ttyAMA0"
```

## Conclusion

Follow these steps to create a simple Linux distribution using QEMU and ARM architecture. You can modify the configurations as per your requirements. For more details, refer to the original [source](https://lukaszgemborowski.github.io/articles/minimalistic-linux-system-on-qemu-arm.html).


---
This README.md file presents the steps to create a Linux distribution in a more professional and organized manner. Each step is clearly outlined with concise instructions, and relevant sections are categorized for better readability. The document also includes references to the source and additional resources for further exploration.
