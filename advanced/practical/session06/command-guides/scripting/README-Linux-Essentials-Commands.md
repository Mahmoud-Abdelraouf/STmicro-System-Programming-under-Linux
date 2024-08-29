# Most Used Linux Commands: A Comprehensive Guide

## Table of Contents

1. [Introduction](#1-introduction)
2. [Basic Commands](#2-basic-commands)
   - 2.1 [Navigating the Filesystem](#21-navigating-the-filesystem)
   - 2.2 [File and Directory Operations](#22-file-and-directory-operations)
   - 2.3 [Viewing and Editing Files](#23-viewing-and-editing-files)
3. [System Information and Management](#3-system-information-and-management)
   - 3.1 [System Information](#31-system-information)
   - 3.2 [Process Management](#32-process-management)
   - 3.3 [User Management](#33-user-management)
4. [File Permissions and Ownership](#4-file-permissions-and-ownership)
   - 4.1 [Changing Permissions](#41-changing-permissions)
   - 4.2 [Changing Ownership](#42-changing-ownership)
5. [Networking](#5-networking)
   - 5.1 [Network Configuration](#51-network-configuration)
   - 5.2 [Testing Connectivity](#52-testing-connectivity)
6. [Archiving and Compression](#6-archiving-and-compression)
   - 6.1 [Creating Archives](#61-creating-archives)
   - 6.2 [Extracting Archives](#62-extracting-archives)
7. [Text Processing](#7-text-processing)
   - 7.1 [Searching Text](#71-searching-text)
   - 7.2 [Text Manipulation](#72-text-manipulation)
8. [Disk Usage and Monitoring](#8-disk-usage-and-monitoring)
   - 8.1 [Checking Disk Usage](#81-checking-disk-usage)
   - 8.2 [Monitoring Disk Activity](#82-monitoring-disk-activity)
9. [Package Management](#9-package-management)
   - 9.1 [Installing and Removing Packages](#91-installing-and-removing-packages)
   - 9.2 [Updating System](#92-updating-system)
10. [Conclusion](#10-conclusion)

---

## 1. Introduction

This guide provides a comprehensive overview of the most commonly used Linux commands, helping both beginners and experienced users navigate the Linux operating system efficiently. Each command is accompanied by examples to illustrate practical usage.

---

## 2. Basic Commands

### 2.1 Navigating the Filesystem

- **`pwd`**: Print the current working directory.
  
  ```bash
  pwd
  ```
  - Output: `/home/user`

- **`cd`**: Change directory.
  
  ```bash
  cd /path/to/directory
  cd ~  # Go to home directory
  cd .. # Move up one directory level
  ```

- **`ls`**: List directory contents.
  
  ```bash
  ls             # List files and directories
  ls -l          # Detailed list with permissions, ownership, and size
  ls -a          # Include hidden files
  ls -lh         # Detailed list with human-readable sizes
  ls -R          # Recursively list subdirectories
  ```

### 2.2 File and Directory Operations

- **`touch`**: Create an empty file or update the timestamp of an existing file.
  
  ```bash
  touch newfile.txt
  touch file1 file2
  ```

- **`mkdir`**: Create a directory.
  
  ```bash
  mkdir newdir
  mkdir -p /path/to/newdir  # Create parent directories as needed
  ```

- **`cp`**: Copy files and directories.
  
  ```bash
  cp source.txt destination.txt         # Copy file
  cp -r /source/directory /destination  # Copy directory recursively
  ```

- **`mv`**: Move or rename files and directories.
  
  ```bash
  mv oldname.txt newname.txt    # Rename file
  mv file.txt /path/to/directory  # Move file to another directory
  ```

- **`rm`**: Remove files or directories.
  
  ```bash
  rm file.txt                    # Remove file
  rm -r /path/to/directory       # Remove directory and its contents
  rm -f file.txt                 # Force remove without prompt
  ```

### 2.3 Viewing and Editing Files

- **`cat`**: Display the contents of a file.
  
  ```bash
  cat file.txt
  ```

- **`less`**: View the contents of a file page by page.
  
  ```bash
  less largefile.txt
  ```

- **`head` and `tail`**: Display the beginning or end of a file.
  
  ```bash
  head file.txt    # First 10 lines
  head -n 20 file.txt  # First 20 lines
  tail file.txt    # Last 10 lines
  tail -n 20 file.txt  # Last 20 lines
  tail -f logfile.txt  # Follow a log file as it grows
  ```

- **`nano`**: A simple text editor.
  
  ```bash
  nano file.txt
  ```

- **`vi` or `vim`**: A powerful text editor.
  
  ```bash
  vi file.txt
  vim file.txt
  ```

---

## 3. System Information and Management

### 3.1 System Information

- **`uname`**: Print system information.
  
  ```bash
  uname -a      # Kernel name, version, and other details
  uname -r      # Kernel version
  uname -m      # System architecture
  ```

- **`df`**: Report filesystem disk space usage.
  
  ```bash
  df -h         # Human-readable sizes
  df -T         # Show filesystem type
  ```

- **`du`**: Estimate file space usage.
  
  ```bash
  du -h /path/to/directory    # Disk usage of a directory
  du -sh /path/to/directory   # Total disk usage of a directory
  ```

- **`free`**: Display memory usage.
  
  ```bash
  free -h   # Human-readable format
  ```

- **`uptime`**: Show how long the system has been running.
  
  ```bash
  uptime
  ```

- **`top`**: Display real-time system information and processes.
  
  ```bash
  top
  ```

### 3.2 Process Management

- **`ps`**: Report a snapshot of current processes.
  
  ```bash
  ps aux       # Detailed list of all running processes
  ```

- **`kill`**: Terminate a process by PID.
  
  ```bash
  kill 1234    # Terminate process with PID 1234
  kill -9 1234 # Force terminate process
  ```

- **`pkill`**: Kill processes by name.
  
  ```bash
  pkill firefox   # Kill all processes with name "firefox"
  ```

- **`htop`**: Interactive process viewer (requires installation).
  
  ```bash
  htop
  ```

### 3.3 User Management

- **`whoami`**: Display the current user.
  
  ```bash
  whoami
  ```

- **`id`**: Display user and group information.
  
  ```bash
  id
  ```

- **`sudo`**: Execute a command as another user, typically as root.
  
  ```bash
  sudo command  # Run command as root
  sudo -u username command  # Run command as another user
  ```

- **`adduser` or `useradd`**: Add a new user.
  
  ```bash
  sudo adduser newuser
  sudo useradd newuser  # Alternative command
  ```

- **`passwd`**: Change a user's password.
  
  ```bash
  passwd        # Change current user's password
  sudo passwd newuser  # Change another user's password
  ```

---

## 4. File Permissions and Ownership

### 4.1 Changing Permissions

- **`chmod`**: Change file or directory permissions.
  
  ```bash
  chmod 644 file.txt           # Set read/write for owner, read for others
  chmod +x script.sh           # Add execute permission
  chmod -R 755 /path/to/dir    # Recursively set directory permissions
  ```

### 4.2 Changing Ownership

- **`chown`**: Change file or directory ownership.
  
  ```bash
  sudo chown user:group file.txt     # Change owner and group
  sudo chown -R user:group /path/to/dir  # Recursively change ownership
  ```

---

## 5. Networking

### 5.1 Network Configuration

- **`ifconfig`**: Display or configure a network interface (deprecated, use `ip`).
  
  ```bash
  ifconfig
  ```

- **`ip`**: Show/manipulate routing, devices, and tunnels.
  
  ```bash
  ip addr show             # Show IP addresses
  ip link show             # Show network interfaces
  ip route show            # Show routing table
  ```

### 5.2 Testing Connectivity

- **`ping`**: Send ICMP echo requests to test network connectivity.

  ```bash
  ping google.com         # Ping a website to test internet connection
  ping -c 4 google.com    # Send 4 packets and stop
  ```

- **`curl`**: Transfer data from or to a server.

  ```bash
  curl http://example.com        # Fetch a webpage
  curl -O http://example.com/file.txt  # Download a file
  ```

- **`wget`**: Download files from the web.

  ```bash
  wget http://example.com/file.txt    # Download a file
  wget -r http://example.com          # Recursively download an entire website
  ```

- **`netstat`**: Network statistics (deprecated, use `ss`).

  ```bash
  netstat -tuln            # List listening ports
  netstat -a               # Show all network connections
  ```

- **`ss`**: Show socket statistics.

  ```bash
  ss -tuln                 # List listening ports
  ss -s                    # Display summary statistics
  ```

---

## 6. Archiving and Compression

### 6.1 Creating Archives

- **`tar`**: Create an archive.

  ```bash
  tar -cvf archive.tar /path/to/directory      # Create a tar archive
  tar -czvf archive.tar.gz /path/to/directory  # Create a gzip-compressed tar archive
  tar -cjvf archive.tar.bz2 /path/to/directory # Create a bzip2-compressed tar archive
  ```

### 6.2 Extracting Archives

- **`tar`**: Extract an archive.

  ```bash
  tar -xvf archive.tar             # Extract a tar archive
  tar -xzvf archive.tar.gz         # Extract a gzip-compressed tar archive
  tar -xjvf archive.tar.bz2        # Extract a bzip2-compressed tar archive
  ```

- **`unzip`**: Extract a ZIP archive.

  ```bash
  unzip archive.zip                # Extract a ZIP archive
  ```

---

## 7. Text Processing

### 7.1 Searching Text

- **`grep`**: Search for patterns in text files.

  ```bash
  grep "pattern" file.txt          # Search for a pattern in a file
  grep -r "pattern" /path/to/dir   # Recursively search in a directory
  grep -i "pattern" file.txt       # Case-insensitive search
  ```

- **`find`**: Search for files and directories.

  ```bash
  find /path/to/search -name "*.txt"        # Find files by name
  find /path/to/search -type d -name "dir"  # Find directories by name
  ```

### 7.2 Text Manipulation

- **`sed`**: Stream editor for filtering and transforming text.

  ```bash
  sed 's/old/new/g' file.txt         # Replace text in a file
  sed -i 's/old/new/g' file.txt      # Replace text and save changes
  ```

- **`awk`**: A programming language for text processing.

  ```bash
  awk '/pattern/ { action }' file.txt        # Apply action to lines matching a pattern
  awk '{ print $1, $3 }' file.txt            # Print specific columns
  ```

- **`cut`**: Remove sections from each line of files.

  ```bash
  cut -d',' -f1,3 file.csv           # Extract fields from a CSV
  cut -c1-5 file.txt                 # Extract the first 5 characters of each line
  ```

---

## 8. Disk Usage and Monitoring

### 8.1 Checking Disk Usage

- **`du`**: Estimate file space usage.

  ```bash
  du -sh /path/to/directory           # Total disk usage of a directory
  du -h /path/to/directory            # Disk usage of a directory and its contents
  ```

- **`df`**: Report file system disk space usage.

  ```bash
  df -h                               # Human-readable disk space usage
  df -T                               # Show filesystem type
  ```

### 8.2 Monitoring Disk Activity

- **`iostat`**: Report CPU and I/O statistics.

  ```bash
  iostat                              # Display basic I/O statistics
  iostat -d 1                         # Display I/O statistics every second
  ```

- **`iotop`**: Display I/O usage by processes (requires installation).

  ```bash
  iotop                               # Display I/O usage by processes
  ```

---

## 9. Package Management

### 9.1 Installing and Removing Packages

- **Debian/Ubuntu**: Use `apt` or `apt-get`.

  ```bash
  sudo apt update                     # Update package lists
  sudo apt install package            # Install a package
  sudo apt remove package             # Remove a package
  sudo apt autoremove                 # Remove unnecessary packages
  ```

- **Red Hat/CentOS**: Use `yum` or `dnf`.

  ```bash
  sudo yum install package            # Install a package
  sudo yum remove package             # Remove a package
  sudo yum update                     # Update all packages
  ```

### 9.2 Updating System

- **Debian/Ubuntu**:

  ```bash
  sudo apt update                     # Update package lists
  sudo apt upgrade                    # Upgrade installed packages
  sudo apt dist-upgrade               # Upgrade with distribution-specific changes
  ```

- **Red Hat/CentOS**:

  ```bash
  sudo yum update                     # Update installed packages
  sudo yum upgrade                    # Upgrade all packages
  ```

---

## 10. Conclusion

This guide covers the most essential Linux commands to help you navigate, manage, and interact with your Linux system smoothly. By mastering these commands, you'll be well-equipped to handle a wide range of tasks in the Linux environment.
