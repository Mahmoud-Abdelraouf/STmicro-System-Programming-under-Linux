# Session 03: Working with Yocto - System Programming under Linux

## Overview

This README provides a structured guide to setting up and working with Yocto, a powerful build system for creating custom Linux distributions for embedded devices. It includes steps for installing necessary prerequisites, downloading recipes, building images, and adding additional layers.

For more detailed documentation, refer to the [Yocto Project Documentation](https://docs.yoctoproject.org/index.html).

## Table of Contents

1. [Install Prerequisites](#install-prerequisites)
2. [Downloading and Setting Up Yocto](#downloading-and-setting-up-yocto)
3. [Building an Image](#building-an-image)
4. [Adding More Layers](#adding-more-layers)

---

## Install Prerequisites

Before setting up Yocto, ensure you have the required packages installed on your system. Follow the instructions provided in the [Yocto Project Quick Start Guide](https://docs.yoctoproject.org/brief-yoctoprojectqs/index.html).

Run the following command to install the prerequisites:

```sh
sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
    build-essential chrpath socat libsdl1.2-dev xterm lz4
```

---

## Downloading and Setting Up Yocto

1. **Clone the Poky Repository**

   Download the Yocto recipes by cloning the Poky repository. Make sure to use the appropriate branch (e.g., scarthgap):

   ```sh
   git clone -b scarthgap git://git.yoctoproject.org/poky
   ```

2. **Set Up the Build Environment**

   Navigate to the poky directory and set up the build environment:

   ```sh
   cd poky
   source oe-init-build-env ../build-qemuarm64
   ```

---

## Building an Image

1. **Configure Local Settings**

   Inside the build directory, update the machine and download directories in `conf/local.conf`:

   ```sh
   MACHINE ??= "qemuarm64"
   DL_DIR ?= "/home/mahmoud/yocto2024/alexandria/downloads"
   ```

2. **Build the Image**

   In the build directory, issue the following command to build a minimal core image:

   ```sh
   bitbake core-image-minimal
   ```

---

## Adding More Layers

You can add more layers to enhance your Yocto build. While this is not necessary, it is recommended.

1. **Clone Additional Layers**

   For example, to add the `meta-odroid` layer, clone the repository:

   ```sh
   cd poky
   git clone https://github.com/akuster/meta-odroid
   ```

2. **Check Out the Correct Branch**

   Ensure that the layer is on the same release branch as Yocto (Poky). For instance, if Poky is on the `scarthgap` branch:

   ```sh
   cd meta-odroid
   git checkout scarthgap
   ```

3. **Update `bblayers.conf`**

   Update `conf/bblayers.conf` to include the new layer:

   ```sh
   BBLAYERS ?= " \
     /home/mahmoud/yocto2024/kirkstone/poky/meta \
     /home/mahmoud/yocto2024/kirkstone/poky/meta-poky \
     /home/mahmoud/yocto2024/kirkstone/poky/meta-yocto-bsp \
     /home/mahmoud/yocto2024/kirkstone/poky/meta-odroid \
   "
   ```

The first three layers are added by default by Poky.

---

By following these steps, you will be able to set up and work with Yocto to create custom Linux distributions tailored to your needs. This guide covers the essentials of installing prerequisites, downloading and setting up Yocto, building images, and adding additional layers to enhance functionality.
