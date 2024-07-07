# Overview of File Handling Examples in C

This README presents three C programs designed to showcase various aspects of file handling within UNIX-like operating systems.

## `dup_share_same_file_descriptor.c`

This program delves into the behavior of the `dup()` system call, a fundamental aspect of file handling. This call duplicates a file descriptor, allowing multiple references to the same open file. Key points include:

### Explanation:

1. The program opens a file specified by the user in write-only mode using `open()`.
2. Utilizing `lseek()`, it positions the file offset at a significant distance from the end of the file.
3. It then duplicates the file descriptor using `dup()`, obtaining a new file descriptor pointing to the same file.
4. Retrieving the current file offset for both descriptors, it demonstrates how they share the same open file description.
5. Finally, it writes data to the file using the original file descriptor, showcasing its impact on the duplicated descriptor.

## `open_get_different_file_descriptor.c`

This program highlights an intriguing aspect of file handling, where opening the same file twice yields different file descriptors. Key points include:

### Explanation:

1. The program opens the same file twice using two separate `open()` calls.
2. It illustrates the independent nature of file descriptors by retrieving and displaying their respective file offsets.
3. Despite opening the same file, each file descriptor maintains its own file offset and file status flags.
4. The program proceeds to write data to the file using one of the file descriptors, emphasizing their distinct identities.

## `shared_file_descriptor_linker.c`

This program serves as a practical demonstration of file handling and process management, showcasing how shared file descriptions impact inter-process communication. Key points include:

### Explanation:

1. The program initiates a child process using `fork()`, creating a parent-child relationship.
2. Both processes open the same file, enabling them to share a common file description.
3. Writing data to the file from either process demonstrates the immediate visibility of changes to the shared file description.
4. By observing file offsets and process IDs, the program provides insights into how changes made by one process affect the other.

---
These examples offer valuable insights into file handling mechanisms, ranging from basic operations like file duplication to more complex interactions between multiple processes sharing the same file description. They serve as essential educational resources for understanding the intricacies of file handling and system calls in C programming.