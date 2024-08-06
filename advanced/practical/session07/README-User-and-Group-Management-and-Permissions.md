# Users and Groups in Linux

## Table of Contents

1. [Overview](#overview)
2. [Users and Groups](#users-and-groups)
    - [Adding Users with `useradd`](#adding-users-with-useradd)
    - [Adding Users with `adduser`](#adding-users-with-adduser)
    - [Adding Groups](#adding-groups)
    - [Managing Users and Groups](#managing-users-and-groups)
3. [Special File Permissions](#special-file-permissions)
    - [Sticky Bit](#sticky-bit)
    - [Set GID Bit](#set-gid-bit)
    - [Set UID Bit](#set-uid-bit)
4. [Password Management](#password-management)
    - [/etc/passwd and /etc/shadow](#etcpasswd-and-etcshadow)
5. [Effective User ID](#effective-user-id)
6. [Examples and Usage](#examples-and-usage)
    - [Example 1: Adding a User](#example-1-adding-a-user)
    - [Example 2: Changing File Permissions](#example-2-changing-file-permissions)
    - [Example 3: Managing Passwords](#example-3-managing-passwords)
    - [Example 4: Creating Multiple Users and Groups](#example-4-creating-multiple-users-and-groups)
7. [Permissions in Directories](#permissions-in-directories)
    - [Available Permissions](#available-permissions)
    - [Examples of Directory Permissions](#examples-of-directory-permissions)
8. [Determining Permissions](#determining-permissions)
    - [Numeric Method](#numeric-method)
    - [Symbolic Method](#symbolic-method)
9. [Additional Commands for Users and Groups](#additional-commands-for-users-and-groups)
10. [Additional Topics](#additional-topics)
    - [User and Group Files](#user-and-group-files)
    - [NIS (Network Information Service)](#nis-network-information-service)
11. [Conclusion](#conclusion)
12. [Additional Resources](#additional-resources)

## Overview

This guide provides a comprehensive overview of user and group management in Linux, special file permissions (Sticky Bit, Set GID, Set UID), password management, effective user ID, and directory permissions. It includes practical examples and detailed explanations for each topic.

## Users and Groups

### Adding Users with `useradd`

The `useradd` command is a low-level utility for adding users in Linux. It offers a wide range of options for configuring new user accounts.

Usage:

```bash
sudo useradd [options] username
```

Common options:

- `--badname`: Allow names that do not conform to standards.
- `-b, --base-dir BASE_DIR`: Specify the default base directory.
- `-c, --comment COMMENT`: Add a comment (usually the user's full name).
- `-d, --home-dir HOME_DIR`: Specify the user's home directory.
- `-e, --expiredate EXPIRE_DATE`: Set the account expiration date.
- `-f, --inactive INACTIVE`: Set the number of days after a password expires until the account is disabled.
- `-g, --gid GROUP`: Specify the user's primary group.
- `-G, --groups GROUP1[,GROUP2,...]`: Add the user to supplementary groups.
- `-k, --skel SKEL_DIR`: Specify the skeleton directory for home directory creation.
- `-K, --key KEY=VALUE`: Override default values.
- `-m, --create-home`: Create the user's home directory.
- `-R, --root CHROOT_DIR`: Apply changes in the CHROOT_DIR directory.
- `-P, --prefix PREFIX_DIR`: Apply changes in the PREFIX_DIR directory.
- `-s, --shell SHELL`: Specify the user's login shell.
- `-u, --uid UID`: Specify the user's numeric ID.
- `-U, --user-group`: Create a group with the same name as the user.
- `-Z, --selinux-user SEUSER`: Specify the SELinux user for the user's login.

Example:

```bash
sudo useradd -m -c "John Doe" -s /bin/bash -G sudo -u 1001 johndoe
```

This command creates a user `johndoe` with a home directory, adds a comment, sets the login shell to `/bin/bash`, adds the user to the `sudo` group, and assigns the user ID `1001`.

### Adding Users with `adduser`

The `adduser` command is a higher-level utility for adding users in Linux. It is more user-friendly and offers interactive prompts.

Usage:

```bash
sudo adduser newuser
```

This command will prompt for user information, including password and user details.

### Adding Groups

To add a new group, use the `groupadd` command:

```bash
sudo groupadd newgroup
```

To add a user to a group:

```bash
sudo usermod -aG newgroup newuser
```

### Managing Users and Groups

- `usermod`: Modify a user account.
- `groupmod`: Modify a group.
- `userdel`: Delete a user account.
- `groupdel`: Delete a group.

Example:

```bash
sudo usermod -l newusername oldusername
sudo groupmod -n newgroupname oldgroupname
```

## Special File Permissions

### Sticky Bit

The Sticky Bit is a permission bit that is set on directories to restrict deletion or renaming of files to the file owner.

To set the Sticky Bit:

```bash
sudo chmod +t /path/to/directory
```

To find the Sticky Bit:

```bash
ls -ld /path/to/directory
```

The Sticky Bit is represented by a `t` in the permissions string:

```plaintext
drwxrwxrwt  2 root root  4096 Jul 23 12:34 /path/to/directory
```

### Set GID Bit

The Set Group ID (Set GID) bit is used to set a directory so that files created within it inherit the group ID of the directory, rather than the primary group ID of the user who created the file.

To set the Set GID bit:

```bash
sudo chmod g+s /path/to/directory
```

To find the Set GID bit:

```bash
ls -ld /path/to/directory
```

The Set GID bit is represented by an `s` in the group permissions:

```plaintext
drwxrwsr-x  2 root staff 4096 Jul 23 12:34 /path/to/directory
```

### Set UID Bit

The Set User ID (Set UID) bit is used to allow users to execute a file with the permissions of the file owner.

To set the Set UID bit:

```bash
sudo chmod u+s /path/to/file
```

To find the Set UID bit:

```bash
ls -l /path/to/file
```

The Set UID bit is represented by an `s` in the user permissions:

```plaintext
-rwsr-xr-x  1 root root  4096 Jul 23 12:34 /path/to/file
```

## Password Management

### /etc/passwd and /etc/shadow

- `/etc/passwd`: Contains user account information.
- `/etc/shadow`: Contains hashed passwords and password-related information.

To change a user's password:

```bash
sudo passwd username
```

The `passwd` command updates the password in `/etc/shadow`.

## Effective User ID

The effective user ID is the user ID that determines the permissions for accessing files and other system resources during a process's execution.

To change the effective user ID within a program, use the `seteuid` function in C:

```c
#include <unistd.h>
int seteuid(uid_t euid);
```

## Examples and Usage

### Example 1: Adding a User

1. Add a new user:

```bash
sudo useradd -m -c "John Doe" -s /bin/bash johndoe
```

2. Set a password for the new user:

```bash
sudo passwd johndoe
```

3. Add the user to a group:

```bash
sudo usermod -aG sudo johndoe
```

### Example 2: Changing File Permissions

1. Create a directory and set the Sticky Bit:

```bash
mkdir /tmp/testdir
sudo chmod +t /tmp/testdir
```

2. Set the Set GID bit on a directory:

```bash
mkdir /tmp/testdir
sudo chmod g+s /tmp/testdir
```

3. Set the Set UID bit on a file:

```bash
touch /tmp/testfile
sudo chmod u+s /tmp/testfile
```

### Example 3: Managing Passwords

1. Change a user's password:

```bash
sudo passwd johndoe
```

2. Verify the updated password in `/etc/shadow` (requires root privileges):

```bash
sudo cat /etc/shadow | grep johndoe
```

### Example 4: Creating Multiple Users and Groups

#### Using `useradd`

1. Create three groups for colleagues:

```bash
sudo groupadd devteam
sudo groupadd designtm
sudo groupadd markettm
```

2. Create six users and assign them to groups:

```bash
sudo useradd -m -G devteam -s /bin/bash alice
sudo useradd -m -G devteam,designtm -s /bin/bash bob
sudo useradd -m -G designtm -s /bin/bash charlie
sudo useradd -m -G markettm -

s /bin/bash dave
sudo useradd -m -G markettm,devteam -s /bin/bash eve
sudo useradd -m -G markettm -s /bin/bash frank
```

In this example, users `bob` and `eve` belong to two groups.

#### Using `adduser`

1. Create a new user and add to a group:

```bash
sudo adduser alice
sudo adduser alice devteam
```

2. Repeat for other users and groups.

## Permissions in Directories

### Available Permissions

- **Read (`r`)**: Allows listing the files in the directory.
- **Write (`w`)**: Allows creating, deleting, and renaming files in the directory.
- **Execute (`x`)**: Allows entering the directory and accessing files and subdirectories.

### Examples of Directory Permissions

1. **Read-only Access**:

```bash
mkdir /tmp/readonlydir
sudo chmod 755 /tmp/readonlydir
```

In this example, users can list and read files in the directory, but cannot create, delete, or modify files.

2. **Write Permission**:

```bash
mkdir /tmp/writabledir
sudo chmod 755 /tmp/writabledir
```

In this example, users can list, create, delete, and modify files in the directory.

3. **Restricted Deletion**:

```bash
mkdir /tmp/restricteddelete
sudo chmod 1777 /tmp/restricteddelete
```

In this example, only the file owner can delete or rename the files, even if others have write access.

4. **Execute Permission**:

The execute permission (`x`) on a directory allows users to enter the directory and access files and subdirectories within it.

```bash
mkdir /tmp/execdir
sudo chmod 711 /tmp/execdir
```

In this example, users can enter the directory and execute files, but cannot list the files in the directory.

### Numeric Method

In the numeric method, permissions are represented by a three-digit number, where each digit represents a different set of permissions.

- **Owner permissions**: The first digit.
- **Group permissions**: The second digit.
- **Others permissions**: The third digit.

Each digit is the sum of the permissions:

- Read (r) = 4
- Write (w) = 2
- Execute (x) = 1

Examples:

1. **755**:

```bash
chmod 755 /tmp/exampledir
```

This sets permissions to `rwxr-xr-x`, meaning the owner can read, write, and execute; the group can read and execute; others can read and execute.

2. **644**:

```bash
chmod 644 /tmp/examplefile
```

This sets permissions to `rw-r--r--`, meaning the owner can read and write; the group can read; others can read.

3. **700**:

```bash
chmod 700 /tmp/exampledir
```

This sets permissions to `rwx------`, meaning only the owner can read, write, and execute.

### Symbolic Method

The symbolic method uses characters to represent permissions and the `+`, `-`, and `=` operators to add, remove, or set permissions.

- `u`: User (owner)
- `g`: Group
- `o`: Others
- `a`: All (user, group, and others)

Examples:

1. Add execute permission to the user:

```bash
chmod u+x /tmp/examplefile
```

2. Remove write permission from the group:

```bash
chmod g-w /tmp/examplefile
```

3. Set read-only permission for others:

```bash
chmod o=r /tmp/examplefile
```

4. Set read, write, and execute permissions for user, read and execute permissions for group, and read-only permissions for others:

```bash
chmod u=rwx,g=rx,o=r /tmp/examplefile
```

## Additional Commands for Users and Groups

### Adding Users with `useradd`

The `useradd` command is a low-level utility for adding users in Linux. It offers a wide range of options for configuring new user accounts.

Usage:

```bash
sudo useradd [options] username
```

Common options:

- `--badname`: Allow names that do not conform to standards.
- `-b, --base-dir BASE_DIR`: Specify the default base directory.
- `-c, --comment COMMENT`: Add a comment (usually the user's full name).
- `-d, --home-dir HOME_DIR`: Specify the user's home directory.
- `-e, --expiredate EXPIRE_DATE`: Set the account expiration date.
- `-f, --inactive INACTIVE`: Set the number of days after a password expires until the account is disabled.
- `-g, --gid GROUP`: Specify the user's primary group.
- `-G, --groups GROUP1[,GROUP2,...]`: Add the user to supplementary groups.
- `-k, --skel SKEL_DIR`: Specify the skeleton directory for home directory creation.
- `-K, --key KEY=VALUE`: Override default values.
- `-m, --create-home`: Create the user's home directory.
- `-R, --root CHROOT_DIR`: Apply changes in the CHROOT_DIR directory.
- `-P, --prefix PREFIX_DIR`: Apply changes in the PREFIX_DIR directory.
- `-s, --shell SHELL`: Specify the user's login shell.
- `-u, --uid UID`: Specify the user's numeric ID.
- `-U, --user-group`: Create a group with the same name as the user.
- `-Z, --selinux-user SEUSER`: Specify the SELinux user for the user's login.

Example:

```bash
sudo useradd -m -c "John Doe" -s /bin/bash -G sudo -u 1001 johndoe
```

This command creates a user `johndoe` with a home directory, adds a comment, sets the login shell to `/bin/bash`, adds the user to the `sudo` group, and assigns the user ID `1001`.

### Adding Users with `adduser`

The `adduser` command is a higher-level utility for adding users in Linux. It is more user-friendly and offers interactive prompts.

Usage:

```bash
sudo adduser newuser
```

This command will prompt for user information, including password and user details.

### Adding Groups

To add a new group, use the `groupadd` command:

```bash
sudo groupadd newgroup
```

To add a user to a group:

```bash
sudo usermod -aG newgroup newuser
```

### Managing Users and Groups

- `usermod`: Modify a user account.
- `groupmod`: Modify a group.
- `userdel`: Delete a user account.
- `groupdel`: Delete a group.

Example:

```bash
sudo usermod -l newusername oldusername
sudo groupmod -n newgroupname oldgroupname
```

## Additional Topics

### User and Group Files

- `/etc/passwd`: Contains user account information.
- `/etc/group`: Contains group information.
- `/etc/shadow`: Contains hashed passwords and password-related information.

### NIS (Network Information Service)

NIS, also known as Yellow Pages (YP), is a client-server directory service protocol for distributing system configuration data such as user and host names between computers on a computer network.

## Conclusion

Managing users and groups in Linux involves understanding the various commands and options available for adding, modifying, and deleting users and groups, as well as setting special file permissions. By mastering these concepts, administrators can effectively manage system access and security.

## Additional Resources

- [Linux Man Pages](https://man7.org/linux/man-pages/)
- [Linux Documentation Project](https://www.tldp.org/)
- [NIS Documentation](https://www.tldp.org/HOWTO/NIS-HOWTO/)
