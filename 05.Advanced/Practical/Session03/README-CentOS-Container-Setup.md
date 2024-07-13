# Setting Up and Running a CentOS Container on Ubuntu using Rinse and Systemd-nspawn

## Overview

This guide provides step-by-step instructions to download CentOS and run it within a container using `rinse` and `systemd-nspawn` on an Ubuntu system.

## Table of Contents

1. [Install Required Packages](#install-required-packages)
2. [Download CentOS with Rinse](#download-centos-with-rinse)
3. [Configure the CentOS Container](#configure-the-centos-container)
4. [Start the CentOS Container](#start-the-centos-container)
5. [Enter the CentOS Container](#enter-the-centos-container)
6. [Troubleshooting](#troubleshooting)
7. [Additional Notes](#additional-notes)

---

## Install Required Packages

Ensure you have `rinse`, `debootstrap`, `systemd-container`, and `qemu-user-static` installed on your Ubuntu system:

```sh
sudo apt update
sudo apt install rinse debootstrap systemd-container qemu-user-static
```

---

## Download CentOS with Rinse

Use `rinse` to create a CentOS root filesystem.

1. **Create a directory for the CentOS root filesystem:**

   ```sh
   sudo mkdir -p /var/lib/machines/centos7
   ```

2. **Use rinse to install CentOS into this directory:**

   ```sh
   sudo rinse --distribution centos-7 --directory /var/lib/machines/centos7 --arch amd64
   ```

---

## Configure the CentOS Container

1. **Set a root password:**

   ```sh
   sudo systemd-nspawn -D /var/lib/machines/centos7 passwd
   ```

2. **Configure the container network (optional):**

   If you want to set up networking for the container, you can create a configuration file:

   ```sh
   sudo nano /etc/systemd/nspawn/centos7.nspawn
   ```

   Add the following lines to configure the network:

   ```ini
   [Network]
   Zone=trusted
   ```

3. **Ensure that the CentOS container has a working resolv.conf:**

   ```sh
   sudo cp /etc/resolv.conf /var/lib/machines/centos7/etc/resolv.conf
   ```

---

## Start the CentOS Container

Start the container using `systemd-nspawn`:

```sh
sudo systemd-nspawn -D /var/lib/machines/centos7 --boot
```

This will boot the CentOS container.

---

## Enter the CentOS Container

You can enter the CentOS container using:

```sh
sudo machinectl shell centos7
```

Or directly using `systemd-nspawn`:

```sh
sudo systemd-nspawn -D /var/lib/machines/centos7
```

---

## Troubleshooting

### Problem: Failed to Find a Distribution Mirror for CentOS 7

When running the `rinse` command, you might encounter the following error:

```sh
We failed to find a distribution mirror for centos-7 (amd64)
 in the file: /etc/rinse/rinse.conf

Aborting
```

#### Solution

1. **Update the Configuration File**:

   Ensure your `/etc/rinse/rinse.conf` has the correct entries for CentOS 7:

   ```conf
   [centos-7]
   mirror=http://vault.centos.org/7.9.2009/os/x86_64/Packages/
   baseurl=http://vault.centos.org/7.9.2009/os/x86_64/
   ```

2. **Retry the Rinse Command**:

   ```sh
   sudo rinse --distribution centos-7 --directory /var/lib/machines/centos7 --arch amd64
   ```

### Alternative Method: Using Docker Image

If the above steps still result in an error, you can use a Docker image to set up CentOS 7:

1. **Install Docker**:

   ```sh
   sudo apt-get update
   sudo apt-get install docker.io
   ```

2. **Pull the CentOS 7 Docker Image**:

   ```sh
   sudo docker pull centos:7
   ```

3. **Export the Docker Image to a Tar File**:

   ```sh
   sudo docker save centos:7 -o centos7.tar
   ```

4. **Create the CentOS 7 Filesystem**:

   ```sh
   sudo mkdir -p /var/lib/machines/centos7
   sudo tar -xf centos7.tar -C /var/lib/machines/centos7
   ```

5. **Start the Container with systemd-nspawn**:

   ```sh
   sudo systemd-nspawn -bD /var/lib/machines/centos7
   ```

---

## Additional Notes

- **Network Configuration:** You might need to configure networking within the CentOS container depending on your use case.
- **Persistent Storage:** Ensure that any persistent data is correctly mapped to volumes outside the container if necessary.
- **Resource Limits:** Configure resource limits for the container using systemd unit files if needed.

By following these steps, you will be able to download CentOS, create a container using rinse, and run it within systemd-nspawn on your Ubuntu system. If you encounter any issues, please let me know!
