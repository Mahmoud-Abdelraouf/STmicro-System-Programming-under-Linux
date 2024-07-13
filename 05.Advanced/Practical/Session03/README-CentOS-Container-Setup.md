# Setting Up and Running a Fedora Container on Ubuntu using Rinse and Systemd-nspawn

## Overview

This guide provides step-by-step instructions to download Fedora and run it within a container using `rinse` and `systemd-nspawn` on an Ubuntu system.

## Table of Contents

1. [Install Required Packages](#install-required-packages)
2. [Download Fedora with Rinse](#download-fedora-with-rinse)
3. [Configure the Fedora Container](#configure-the-fedora-container)
4. [Start the Fedora Container](#start-the-fedora-container)
5. [Enter the Fedora Container](#enter-the-fedora-container)
6. [Additional Notes](#additional-notes)

---

## Install Required Packages

Ensure you have `rinse`, `debootstrap`, `systemd-container`, and `qemu-user-static` installed on your Ubuntu system:

```sh
sudo apt update
sudo apt install rinse debootstrap systemd-container qemu-user-static
```

---

## Download Fedora with Rinse

Use `rinse` to create a Fedora root filesystem.

1. **Create a directory for the Fedora root filesystem:**

   ```sh
   sudo mkdir -p /var/lib/machines/fedora33
   ```

2. **Update the Rinse Configuration**

   Edit the `/etc/rinse/rinse.conf` file to ensure it has the correct Fedora 33 entries:

   ```sh
   sudo nano /etc/rinse/rinse.conf
   ```

   Ensure it contains:

   ```conf
   [fedora-33]
   mirror=http://archives.fedoraproject.org/pub/archive/fedora/linux/releases/33/Everything/x86_64/os/Packages/
   mirror.amd64=http://archives.fedoraproject.org/pub/archive/fedora/linux/releases/33/Everything/x86_64/os/Packages/
   ```

3. **Create the `fedora-33.packages` File**

   Create and edit the `fedora-33.packages` file:

   ```sh
   sudo nano /etc/rinse/fedora-33.packages
   ```

   Add the following content:

   ```sh
   acl
   audit-libs
   basesystem
   bash
   coreutils
   findutils
   grep
   gzip
   iputils
   net-tools
   procps-ng
   shadow-utils
   util-linux
   vim-minimal
   yum
   ```

4. **Use rinse to install Fedora into this directory:**

   ```sh
   sudo rinse --distribution fedora-33 --directory /var/lib/machines/fedora33 --arch amd64
   ```

---

## Configure the Fedora Container

1. **Set a root password:**

   ```sh
   sudo systemd-nspawn -D /var/lib/machines/fedora33 passwd
   ```

2. **Configure the container network (optional):**

   If you want to set up networking for the container, you can create a configuration file:

   ```sh
   sudo nano /etc/systemd/nspawn/fedora33.nspawn
   ```

   Add the following lines to configure the network:

   ```ini
   [Network]
   Zone=trusted
   ```

3. **Ensure that the Fedora container has a working resolv.conf:**

   ```sh
   sudo cp /etc/resolv.conf /var/lib/machines/fedora33/etc/resolv.conf
   ```

---

## Start the Fedora Container

Start the container using `systemd-nspawn`:

```sh
sudo systemd-nspawn -D /var/lib/machines/fedora33 --boot
```

This will boot the Fedora container.

---

## Enter the Fedora Container

You can enter the Fedora container using:

```sh
sudo machinectl shell fedora33
```

Or directly using `systemd-nspawn`:

```sh
sudo systemd-nspawn -D /var/lib/machines/fedora33
```

---

## Additional Notes

- **Network Configuration:** You might need to configure networking within the Fedora container depending on your use case.
- **Persistent Storage:** Ensure that any persistent data is correctly mapped to volumes outside the container if necessary.
- **Resource Limits:** Configure resource limits for the container using systemd unit files if needed.

By following these steps, you will be able to download Fedora, create a container using rinse, and run it within systemd-nspawn on your Ubuntu system. If you encounter any issues, please let me know!
