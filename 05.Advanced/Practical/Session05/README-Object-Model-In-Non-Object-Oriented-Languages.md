# Object Model in Non-Object-Oriented Languages

## Table of Contents

1. [Introduction](#introduction)
2. [Basic Concepts](#basic-concepts)
   - [Structures](#structures)
   - [Function Pointers](#function-pointers)
3. [Creating a Simple Object Model](#creating-a-simple-object-model)
   - [Defining Types](#defining-types)
   - [Encapsulation](#encapsulation)
   - [Polymorphism](#polymorphism)
4. [Inheritance in Object Models](#inheritance-in-object-models)
   - [Nested Structures](#nested-structures)
5. [Lifecycle Management](#lifecycle-management)
   - [Creation and Initialization](#creation-and-initialization)
   - [Destruction](#destruction)
6. [Advanced Object Models](#advanced-object-models)
   - [QEMU Object Model](#qemu-object-model)
     - [Explanation of QEMU Object Model](#explanation-of-qemu-object-model)
   - [Linux Kernel Object Model](#linux-kernel-object-model)
     - [Explanation of Linux Kernel Object Model](#explanation-of-linux-kernel-object-model)
     - [Example Implementations](#example-implementations)
       - [Character Device Drivers](#character-device-drivers)
       - [File Systems](#file-systems)
7. [Library Management System Project](#library-management-system-project)
8. [Best Practices](#best-practices)
9. [Resources](#resources)
10. [Conclusion](#conclusion)

## Introduction

In non-object-oriented languages, object models provide a structured way to implement concepts such as encapsulation, inheritance, and polymorphism. This guide will help you understand how to create and use object models in C, using simple examples that gradually increase in complexity. We'll also explore the QEMU and Linux Kernel object models.

## Basic Concepts

### Structures

Structures in C are used to group related data together. They serve as the foundation for creating objects.

```c
#include <stdio.h>

// Define a structure for a simple object
struct Object {
    int id;
    char name[50];
};
```

### Function Pointers

Function pointers allow functions to be stored in variables, providing a way to implement methods and polymorphism.

```c
#include <stdio.h>

// Define a function pointer type
typedef void (*FunctionPointer)();

// Define a function to be pointed to
void say_hello() {
    printf("Hello, World!\n");
}

int main() {
    // Declare a function pointer and assign it to the function
    FunctionPointer fp = say_hello;
    
    // Call the function using the function pointer
    fp();
    
    return 0;
}
```

## Creating a Simple Object Model

### Defining Types

Define types using `typedef` and `struct` to represent objects.

```c
#include <stdio.h>
#include <string.h>

// Define a structure for an object
typedef struct {
    int id;
    char name[50];
} Object;
```

### Encapsulation

Encapsulation is achieved by grouping data and related functions together.

```c
#include <stdio.h>
#include <string.h>

// Define a structure for an object
typedef struct {
    int id;
    char name[50];
} Object;

// Function to initialize an object
void init_object(Object *obj, int id, const char *name) {
    obj->id = id;
    strcpy(obj->name, name);
}

// Function to print an object's details
void print_object(const Object *obj) {
    printf("Object ID: %d, Name: %s\n", obj->id, obj->name);
}

int main() {
    Object obj;
    init_object(&obj, 1, "MyObject");
    print_object(&obj);
    return 0;
}
```

### Polymorphism

Polymorphism is implemented using function pointers within structures.

```c
#include <stdio.h>
#include <string.h>

// Define a structure for an object
typedef struct {
    int id;
    char name[50];
    void (*print)(struct Object *obj); // Function pointer for polymorphism
} Object;

// Function to initialize an object
void init_object(Object *obj, int id, const char *name, void (*print_func)(struct Object *)) {
    obj->id = id;
    strcpy(obj->name, name);
    obj->print = print_func;
}

// Function to print an object's details
void print_object(Object *obj) {
    printf("Object ID: %d, Name: %s\n", obj->id, obj->name);
}

int main() {
    Object obj;
    init_object(&obj, 1, "MyObject", print_object);
    obj.print(&obj); // Call the function via function pointer
    return 0;
}
```

## Inheritance in Object Models

### Nested Structures

Inheritance can be simulated using nested structures.

```c
#include <stdio.h>
#include <string.h>

// Base structure
typedef struct {
    int id;
    char name[50];
    void (*print)(struct Base *base);
} Base;

// Derived structure
typedef struct {
    Base base; // Inherit from Base
    int extra_property;
} Derived;

// Function to print base details
void print_base(Base *base) {
    printf("Base ID: %d, Name: %s\n", base->id, base->name);
}

// Function to print derived details
void print_derived(Base *base) {
    Derived *derived = (Derived *)base; // Cast to derived type
    printf("Derived ID: %d, Name: %s, Extra: %d\n", derived->base.id, derived->base.name, derived->extra_property);
}

int main() {
    Derived derived;
    derived.base.id = 2;
    strcpy(derived.base.name, "DerivedObject");
    derived.extra_property = 42;
    derived.base.print = print_derived;

    derived.base.print((Base *)&derived); // Call derived print function
    return 0;
}
```

## Lifecycle Management

### Creation and Initialization

Manage the lifecycle of objects with functions for creation and initialization.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for an object
typedef struct {
    int id;
    char name[50];
    void (*print)(struct Object *obj);
} Object;

// Function to create an object
Object *create_object(int id, const char *name, void (*print_func)(struct Object *)) {
    Object *obj = (Object *)malloc(sizeof(Object));
    if (obj != NULL) {
        obj->id = id;
        strcpy(obj->name, name);
        obj->print = print_func;
    }
    return obj;
}

// Function to print an object's details
void print_object(Object *obj) {
    printf("Object ID: %d, Name: %s\n", obj->id, obj->name);
}

int main() {
    Object *obj = create_object(1, "MyObject", print_object);
    if (obj != NULL) {
        obj->print(obj); // Call the function via function pointer
        free(obj); // Free the allocated memory
    }
    return 0;
}
```

### Destruction

Provide functions for proper object destruction to free resources.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for an object
typedef struct {
    int id;
    char name[50];
    void (*print)(struct Object *obj);
} Object;

// Function to create an object
Object *create_object(int id, const char *name, void (*print_func)(struct Object *)) {
    Object *obj = (Object *)malloc(sizeof(Object));
    if (obj != NULL) {
        obj->id = id;
        strcpy(obj->name, name);
        obj->print = print_func;
    }
    return obj;
}

// Function to destroy an object
void destroy_object(Object *obj) {
    // Perform any cleanup if necessary
    free(obj);
}

// Function to print an object's details
void print_object(Object *obj) {
    printf("Object ID: %d, Name: %s\n", obj->id, obj->name);
}

int main() {
    Object *obj = create_object(1, "MyObject", print_object);
    if (obj != NULL) {
        obj->print(obj); // Call the function via function pointer
        destroy_object(obj); // Destroy the object
    }
    return 0;
}
```

## Advanced Object Models

### QEMU Object Model

QEMU uses a custom object model to handle various types of hardware emulation.

```c
#define TYPE_MY_DEVICE "my-device"
#define MY_DEVICE(obj) \
    OBJECT_CHECK(MyDevice, (obj), TYPE_MY_DEVICE)

typedef struct MyDevice {
    DeviceState parent_obj;
    int my_property;
} MyDevice;

static void my_device_init(Object *obj)
{
    MyDevice *dev = MY_DEVICE(obj);
    dev->my_property = 0;
}

static void my_device_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    dc->reset = my_device_reset;
}

static const TypeInfo my_device_info = {
    .name = TYPE_MY_DEVICE,
    .parent = TYPE_DEVICE,
    .instance_size = sizeof(MyDevice),
    .instance_init = my_device_init,
    .class_init = my_device_class_init,
};

static void my_device_register_types(void)
{
    type_register_static(&my_device_info);
}

type_init(my_device_register_types);
```

#### Explanation of QEMU Object Model

1. **Type Registration:** Types are registered with a unique name using `TypeInfo`.
2. **Inheritance

:** The `parent` field in `TypeInfo` supports inheritance.
3. **Object Creation:** Objects are created and initialized using type-specific constructors (`my_device_init`).
4. **Methods:** Function pointers in structures (like `DeviceClass`) are used to implement methods, supporting polymorphism.

### Linux Kernel Object Model

The Linux Kernel uses a similar model, particularly in its implementation of various subsystems.

```c
struct file_operations {
    struct module *owner;
    loff_t (*llseek) (struct file *, loff_t, int);
    ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
    ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
    int (*open) (struct inode *, struct file *);
    int (*release) (struct inode *, struct file *);
};

// Function prototypes for file operations
static loff_t my_llseek(struct file *file, loff_t offset, int whence) {
    // Implementation of llseek
    return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t count, loff_t *pos) {
    // Implementation of read
    return 0;
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *pos) {
    // Implementation of write
    return count;
}

static int my_open(struct inode *inode, struct file *file) {
    // Implementation of open
    return 0;
}

static int my_release(struct inode *inode, struct file *file) {
    // Implementation of release
    return 0;
}

static struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .llseek = my_llseek,
    .read = my_read,
    .write = my_write,
    .open = my_open,
    .release = my_release,
};

static int __init my_init(void)
{
    int result;
    result = register_chrdev(0, "my_device", &my_fops);
    if (result < 0) {
        printk(KERN_WARNING "Can't get major number\n");
        return result;
    }
    return 0;
}

static void __exit my_exit(void)
{
    unregister_chrdev(my_major, "my_device");
}

module_init(my_init);
module_exit(my_exit);
```

#### Explanation of Linux Kernel Object Model

1. **Structures:** `struct file_operations` defines the operations (methods) that can be performed on a file.
2. **Function Pointers:** Methods like `llseek`, `read`, `write`, `open`, and `release` are implemented as function pointers within the structure.
3. **Initialization and Cleanup:** The `module_init` and `module_exit` macros manage the lifecycle of the module.

#### Example Implementations

- **Character Device Drivers:**
  Implementations can be found in the character device driver files, such as [drivers/char/mem.c](https://elixir.bootlin.com/linux/latest/source/drivers/char/mem.c).

- **File Systems:**
  Look into the file system source files, such as [fs/ext2/file.c](https://elixir.bootlin.com/linux/latest/source/fs/ext2/file.c) for implementations related to file systems.

## Library Management System Project

### Overview

We will create a library management system using the object model approach inspired by QEMU and the Linux kernel. The system will manage books and members.

### Defining Structures

#### Book Structure

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    int id;
    char title[100];
    char author[100];
    void (*print_details)(struct Book *book);
} Book;

void print_book_details(Book *book) {
    printf("Book ID: %d, Title: %s, Author: %s\n", book->id, book->title, book->author);
}

Book *create_book(int id, const char *title, const char *author) {
    Book *book = (Book *)malloc(sizeof(Book));
    if (book != NULL) {
        book->id = id;
        strcpy(book->title, title);
        strcpy(book->author, author);
        book->print_details = print_book_details;
    }
    return book;
}

void destroy_book(Book *book) {
    free(book);
}
```

#### Member Structure

```c
typedef struct Member {
    int id;
    char name[100];
    void (*print_details)(struct Member *member);
} Member;

void print_member_details(Member *member) {
    printf("Member ID: %d, Name: %s\n", member->id, member->name);
}

Member *create_member(int id, const char *name) {
    Member *member = (Member *)malloc(sizeof(Member));
    if (member != NULL) {
        member->id = id;
        strcpy(member->name, name);
        member->print_details = print_member_details;
    }
    return member;
}

void destroy_member(Member *member) {
    free(member);
}
```

### Library Management

```c
typedef struct Library {
    Book *books[100];
    int book_count;
    Member *members[100];
    int member_count;
} Library;

Library *create_library() {
    Library *library = (Library *)malloc(sizeof(Library));
    if (library != NULL) {
        library->book_count = 0;
        library->member_count = 0;
    }
    return library;
}

void add_book(Library *library, Book *book) {
    if (library->book_count < 100) {
        library->books[library->book_count++] = book;
    }
}

void add_member(Library *library, Member *member) {
    if (library->member_count < 100) {
        library->members[library->member_count++] = member;
    }
}

void list_books(Library *library) {
    for (int i = 0; i < library->book_count; i++) {
        library->books[i]->print_details(library->books[i]);
    }
}

void list_members(Library *library) {
    for (int i = 0; i < library->member_count; i++) {
        library->members[i]->print_details(library->members[i]);
    }
}

void destroy_library(Library *library) {
    for (int i = 0; i < library->book_count; i++) {
        destroy_book(library->books[i]);
    }
    for (int i = 0; i < library->member_count; i++) {
        destroy_member(library->members[i]);
    }
    free(library);
}
```

### Main Function

```c
int main() {
    Library *library = create_library();

    Book *book1 = create_book(1, "The C Programming Language", "Brian W. Kernighan, Dennis M. Ritchie");
    Book *book2 = create_book(2, "Expert C Programming", "Peter van der Linden");

    add_book(library, book1);
    add_book(library, book2);

    Member *member1 = create_member(1, "Alice");
    Member *member2 = create_member(2, "Bob");

    add_member(library, member1);
    add_member(library, member2);

    printf("Books in the library:\n");
    list_books(library);

    printf("\nMembers in the library:\n");
    list_members(library);

    destroy_library(library);

    return 0;
}
```

## Best Practices

- **Consistent Naming:** Use consistent naming conventions for types and functions.
- **Documentation:** Comment your code to explain the purpose and usage of each part.
- **Memory Management:** Ensure proper memory allocation and deallocation.
- **Error Handling:** Implement robust error handling for resource management.

## Resources

Here are some valuable resources for further reading and understanding:

1. **Books:**
   - "Expert C Programming: Deep C Secrets" by Peter van der Linden
   - "The C Programming Language" by Brian W. Kernighan and Dennis M. Ritchie

2. **Online Tutorials:**
   - [QEMU Documentation](https://qemu-project.gitlab.io/qemu/system/)
   - [Linux Kernel Documentation](https://www.kernel.org/doc/html/latest/)

3. **Articles:**
   - [Understanding the QEMU Object Model](https://developer.ibm.com/articles/au-qemu/)
   - [Linux Kernel Module Programming Guide](https://tldp.org/LDP/lkmpg/2.6/html/)

4. **Courses:**
   - [Introduction to Operating Systems](https://www.udacity.com/course/introduction-to-operating-systems--ud923)
   - [Advanced C Programming](https://www.coursera.org/learn/advanced-c-programming)

5. **Source Code:**
   - [Linux Source Code at Bootlin](https://elixir.bootlin.com/linux/latest/source/include/linux/fs.h#L1845) - Refer to this for definitions and implementations of structures like `file_operations`.
   - Example implementations in [Character Device Drivers](https://elixir.bootlin.com/linux/latest/source/drivers/char/mem.c).
   - Example implementations in [File Systems](https://elixir.bootlin.com/linux/latest/source/fs/ext2/file.c).

## Conclusion

By understanding and implementing object models in non-object-oriented languages, you can bring the benefits of encapsulation, inheritance, and polymorphism to your projects. This guide provides a foundation, gradually building up from basic concepts to more complex examples like those used in QEMU and the Linux Kernel. Happy coding!
