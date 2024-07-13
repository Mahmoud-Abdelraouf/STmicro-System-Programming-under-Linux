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
sudo apt install rinse debootstrap systemd-container qemu-user-static dnf
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
   sudo vi /etc/rinse/rinse.conf
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
   sudo vi /etc/rinse/fedora-33.packages
   ```

   Add the following content:

   ```sh
   # fedora-33.packages
   # This is a package list for Fedora 33, used by rinse to create a minimal installation.

   # Basic system packages
   acl
   audit-libs
   basesystem
   bash
   bzip2-libs
   ca-certificates
   chkconfig
   coreutils
   coreutils-common
   coreutils-single
   cpio
   cracklib
   crypto-policies
   cryptsetup-libs
   curl
   curl-minimal
   cyrus-sasl-lib
   dbus
   dbus-libs
   device-mapper
   device-mapper-libs
   diffutils
   dnf
   dnf-automatic
   dnf-data
   dnf-plugin-diff
   dnf-plugin-ovl
   dnf-plugin-subscription-manager
   dnf-plugin-swidtags
   dnf-plugins-core
   dnf-utils
   elfutils-default-yama-scope
   elfutils-libelf
   elfutils-libs
   expat
   fedora-gpg-keys
   fedora-release
   fedora-repos
   file-libs
   filesystem
   gawk
   gdbm
   gdbm-libs
   generic-release
   glib2
   glibc
   glibc-common
   glibc-minimal-langpack
   gmp
   gnupg2
   gnutls
   gobject-introspection
   gpgme
   grep
   gzip
   ima-evm-utils
   info
   iptables-libs
   json-c
   keyutils-libs
   kmod-libs
   krb5-libs
   libacl
   libarchive
   libargon2
   libassuan
   libattr
   libblkid
   libcap
   libcap-ng
   libcom_err
   libcomps
   libcurl
   libcurl-minimal
   libdb
   libdb-utils
   libdnf
   libeconf
   libibverbs
   libnl
   libfdisk
   libffi
   libgcc
   libgcrypt
   libgpg-error
   libidn2
   libksba
   libmetalink
   libmodulemd
   libmount
   libnghttp2
   libnsl2
   libpcap
   libpsl
   libpwquality
   librepo
   libreport-filesystem
   libseccomp
   libselinux
   libsemanage
   libsepol
   libsigsegv
   libsmartcols
   libsolv
   libstdc++
   libssh
   libtasn1
   libtirpc
   libunistring
   libusbx
   libzck
   libutempter
   libuuid
   libverto
   libxcrypt
   libxml2
   libyaml
   libzstd
   lua-libs
   lz4-libs
   mpfr
   ncurses
   ncurses-base
   ncurses-libs
   nettle
   npth
   nspr
   nss
   nss-softokn
   nss-softokn-freebl
   nss-sysinit
   nss-util
   openldap
   openssl-libs
   p11-kit
   p11-kit-trust
   pam
   pcre
   pcre2
   popt
   publicsuffix-list-dafsa
   python3
   python3-dnf
   python3-gobject-base
   python3-gpg
   python3-hawkey
   python3-iniparse
   python3-libcomps
   python3-librepo
   python3-libs
   python3-pip
   python3-rpm
   python3-setuptools
   python3-six
   python3-smartcols
   qrencode-libs
   readline
   rpm
   rpm-build-libs
   rpm-libs
   rpm-plugin-selinux
   sed
   setup
   shadow-utils
   sqlite-libs
   systemd
   systemd-libs
   systemd-pam
   tzdata
   util-linux
   xz-libs
   zlib
   ```

4. **Use rinse to install Fedora into this directory:**

   ```sh
   sudo rinse --distribution fedora-33 --directory /var/lib/machines/fedora33 --arch amd64
   ```

5. **Unpack and Remove the RPM Packages**

   Navigate to the directory where the RPM packages are stored and run the following script to unpack and then remove the RPM packages:

   ```sh
   cd /var/lib/machines/fedora33
   for pkg in *.rpm; do
       sudo rpm2cpio $pkg | sudo cpio -idmv
       sudo rm -f $pkg
   done
   ```

6. **Handling Missing Packages**

   If you encounter any missing packages during the rinse process, you can manually add them to the `fedora-33.packages` file and re-run rinse:

   ```sh
   sudo vi /etc/rinse/fedora-33.packages
   ```

   Add the missing package names to the file, save, and exit.

   Re-run rinse:

   ```sh
   sudo rinse --distribution fedora-33 --directory /var/lib/machines/fedora33 --arch amd64
   ```

   Unpack the newly downloaded packages using the same script as above:

   ```sh
   cd /var/lib/machines/fedora33
   for pkg in *.rpm; do
       sudo rpm2cpio $pkg | sudo cpio -idmv
       sudo rm -f $pkg
   done
   ```

7. **Quick Way to Install Needed Extra Packages**

   For any additional packages needed, you can manually download and unpack them:

   ```sh
   cd /var/lib/machines/fedora33
   wget [URL to the RPM package]
   sudo rpm2cpio [package-name].rpm | sudo cpio -idmv
   sudo rm -f [package-name].rpm
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
   sudo vi /etc/systemd/nspawn/fedora33.nspawn
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
