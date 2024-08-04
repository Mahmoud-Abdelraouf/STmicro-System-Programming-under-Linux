# Capabilities in Linux Kernel and Containers

This directory demonstrates the capabilities in the Linux kernel, their relation to containers, and the transformation of capabilities. Below are the details of various experiments conducted to understand these capabilities.

## Table of Contents

1. [Introduction](#introduction)
2. [Capabilities Overview](#capabilities-overview)
   - [Equation for Capability Transformation](#equation-for-capability-transformation)
3. [Experiments](#experiments)
   - [Experiment 1](#experiment-1)
   - [Experiment 2](#experiment-2)
   - [Experiment 3](#experiment-3)
4. [Example Demonstrations](#example-demonstrations)
   - [Demo 1: Change Owner and Read File](#demo-1-change-owner-and-read-file)
   - [Demo 2: Read File with Different Capabilities](#demo-2-read-file-with-different-capabilities)
5. [Problem and Solution](#problem-and-solution)
6. [Additional Resources](#additional-resources)

---

## Introduction

This README provides a comprehensive guide to understanding and experimenting with Linux capabilities, particularly in the context of containers. It includes experiments demonstrating the transformation of capabilities and how they affect processes.

---

## Capabilities Overview

Linux capabilities are a partitioning of the all-powerful root privileges into distinct units. This allows for more fine-grained control over what a process can and cannot do.

### Equation for Capability Transformation

The transformation of capabilities is governed by the following equation from [man 7 capabilities](https://man7.org/linux/man-pages/man7/capabilities.7.html):

```
P'(permitted) = (P(inheritable) & F(inheritable)) |
                (F(permitted) & P(bounding)) | P'(ambient)
```

- `P'(permitted)`: New permitted capabilities
- `P(inheritable)`: Process inheritable capabilities
- `F(inheritable)`: File inheritable capabilities
- `F(permitted)`: File permitted capabilities
- `P(bounding)`: Bounding set
- `P'(ambient)`: Ambient set

In the experiments below, we explore how these capabilities are transformed under various scenarios.

---

## Experiments

The following experiments are conducted using example codes located in the `linux_capabilities_examples` directory.

### Experiment 1

1. **Set capabilities for `service1`:**
    ```bash
    sudo setcap cap_chown+p linux_capabilities_examples/bin/service1
    getcap linux_capabilities_examples/bin/service1
    # Output: linux_capabilities_examples/bin/service1 = cap_chown+p
    ```

2. **Set capabilities for `driver1`:**
    ```bash
    sudo setcap cap_chown,cap_dac_override+eip linux_capabilities_examples/bin/driver1
    getcap linux_capabilities_examples/bin/driver1
    # Output: linux_capabilities_examples/bin/driver1 = cap_chown,cap_dac_override+eip
    ```

3. **Run `driver1`:**
    ```bash
    linux_capabilities_examples/bin/driver1
    # Output:
    # effective=3
    # permitted=3
    # inheritable=0
    # ----  Exec service1
    # effective=0
    # permitted=1
    # inheritable=0
    ```

### Experiment 2

1. **Set capabilities for `service1`:**
    ```bash
    sudo setcap cap_chown+p linux_capabilities_examples/bin/service1
    getcap linux_capabilities_examples/bin/service1
    # Output: linux_capabilities_examples/bin/service1 = cap_chown+p
    ```

2. **Set capabilities for `driver2`:**
    ```bash
    sudo setcap cap_chown,cap_dac_override+eip linux_capabilities_examples/bin/driver2
    getcap linux_capabilities_examples/bin/driver2
    # Output: linux_capabilities_examples/bin/driver2 = cap_chown,cap_dac_override+eip
    ```

3. **Run `driver2`:**
    ```bash
    linux_capabilities_examples/bin/driver2
    # Output:
    # effective=3
    # permitted=3
    # inheritable=0
    # ----  Setting 2 Inheritable capabilities
    # effective=3
    # permitted=3
    # inheritable=3
    # ----  Exec service1
    # effective=0
    # permitted=1
    # inheritable=3
    ```

### Experiment 3

1. **Set capabilities for `service1`:**
    ```bash
    sudo setcap "cap_chown+ip cap_dac_override+i" linux_capabilities_examples/bin/service1
    getcap linux_capabilities_examples/bin/service1
    # Output: linux_capabilities_examples/bin/service1 = cap_chown+ip cap_dac_override+i
    ```

2. **Set capabilities for `driver2`:**
    ```bash
    sudo setcap cap_chown,cap_dac_override+eip linux_capabilities_examples/bin/driver2
    getcap linux_capabilities_examples/bin/driver2
    # Output: linux_capabilities_examples/bin/driver2 = cap_chown,cap_dac_override+eip
    ```

3. **Run `driver2`:**
    ```bash
    linux_capabilities_examples/bin/driver2
    # Output:
    # effective=3
    # permitted=3
    # inheritable=0
    # ----  Setting 2 Inheritable capabilities
    # effective=3
    # permitted=3
    # inheritable=3
    # ----  Exec service1
    # effective=0
    # permitted=3
    # inheritable=3
    ```

---

## Example Demonstrations

### Demo 1: Change Owner and Read File

This demonstration shows how to change the owner of a file and read it with different capabilities.

### Demo 2: Read File with Different Capabilities

This demonstration shows how to read a file with different capabilities.

---

## Additional Resources

- [Linux Capabilities (man 7 capabilities)](https://man7.org/linux/man-pages/man7/capabilities.7.html)
- [PR_SET_KEEPCAPS Documentation](https://man7.org/linux/man-pages/man2/prctl.2.html)
- [Capability Bounding Set](https://www.kernel.org/doc/html/latest/userspace-api)
