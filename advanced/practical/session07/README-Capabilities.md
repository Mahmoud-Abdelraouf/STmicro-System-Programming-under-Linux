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
4. [Code Examples](#code-examples)
   - [Driver1](#driver1)
   - [Driver2](#driver2)
   - [Service1](#service1)
   - [Service2](#service2)
5. [Example Demonstrations](#example-demonstrations)
   - [Demo 1: Change Owner and Read File](#demo-1-change-owner-and-read-file)
   - [Demo 2: Read File with Different Capabilities](#demo-2-read-file-with-different-capabilities)

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

### Experiment 1

1. **Set capabilities for `service1`:**
    ```bash
    sudo setcap cap_chown+p service1
    getcap service1
    # Output: service1 = cap_chown+p
    ```

2. **Set capabilities for `driver1`:**
    ```bash
    sudo setcap cap_chown,cap_dac_override+eip driver1
    getcap driver1
    # Output: driver1 = cap_chown,cap_dac_override+eip
    ```

3. **Run `driver1`:**
    ```bash
    ./driver1
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
    sudo setcap cap_chown+p service1
    getcap service1
    # Output: service1 = cap_chown+p
    ```

2. **Set capabilities for `driver2`:**
    ```bash
    sudo setcap cap_chown,cap_dac_override+eip driver2
    getcap driver2
    # Output: driver2 = cap_chown,cap_dac_override+eip
    ```

3. **Run `driver2`:**
    ```bash
    ./driver2
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
    sudo setcap "cap_chown+ip cap_dac_override+i" service1
    getcap service1
    # Output: service1 = cap_chown+ip cap_dac_override+i
    ```

2. **Set capabilities for `driver2`:**
    ```bash
    sudo setcap cap_chown,cap_dac_override+eip driver2
    getcap driver2
    # Output: driver2 = cap_chown,cap_dac_override+eip
    ```

3. **Run `driver2`:**
    ```bash
    ./driver2
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

## Code Examples

### Driver1

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    cap_user_header_t header;
    cap_user_data_t capdata;

    header = malloc(sizeof(*header));
    capdata = malloc(sizeof(*capdata));

    capget(header, NULL);
    header->pid = 0;
    capget(header, capdata);

    printf("effective=%x\n", capdata->effective);
    printf("permitted=%x\n", capdata->permitted);
    printf("inheritable=%x\n", capdata->inheritable);

    printf("----  Exec service1\n");
    execlp("service1", "service1", (char *) 0);
    free(header);
    free(capdata);
    return 0;
}
```

### Driver2

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    cap_user_header_t header;
    cap_user_data_t capdata;

    header = malloc(sizeof(*header));
    capdata = malloc(sizeof(*capdata));

    capget(header, NULL);
    header->pid = 0;
    capget(header, capdata);

    printf("effective=%x\n", capdata->effective);
    printf("permitted=%x\n", capdata->permitted);
    printf("inheritable=%x\n", capdata->inheritable);

    printf("----  Setting 2 Inheritable capabilities\n");
    capdata->inheritable |= ((1 << CAP_CHOWN) | (1 << CAP_DAC_OVERRIDE));
    header->pid = 0;
    if (capset(header, capdata) == -1) perror("capset1");

    capget(header, capdata);

    printf("effective=%x\n", capdata->effective);
    printf("permitted=%x\n", capdata->permitted);
    printf("inheritable=%x\n", capdata->inheritable);

    printf("----  Exec service1\n");
    execlp("service1", "service1", (char *) 0);
    free(header);
    free(capdata);
    return 0;
}
```

### Service1

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    cap_user_header_t header;
    cap_user_data_t capdata;

    header = malloc(sizeof(*header));
    capdata = malloc(sizeof(*capdata));

    capget(header, NULL);
    header->pid = 0;
    capget(header, capdata);

    printf("effective=%x\n", capdata->effective);
    printf("permitted=%x\n", capdata->permitted);
    printf("inheritable=%x\n", capdata->inheritable);

    free(header);
    free(capdata);
    return 0;
}
```

### Service2

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/capability.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/prctl.h>

int main(int argc, char **argv) {
    cap_user_header_t header;
    cap_user_data_t capdata;

    header = malloc(sizeof(*header));
    capdata = malloc(sizeof(*capdata));

    capget(header, NULL);
    header->pid = 0;
    capget(header, capdata);

    printf("effective=%x\n", capdata->effective);
    printf("permitted=%x\n", capdata->permitted);
    printf("inheritable=%x\n", capdata->inheritable);

    capdata->inheritable |= ((1 << CAP_CHOWN) | (1 << CAP_DAC_OVERRIDE));
    header->pid = getpid() * (-1);
    capset(header, capdata);

    prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, CAP_CHOWN, 0, 0);
    prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, CAP_DAC_OVERRIDE, 0, 0

);
    prctl(PR_SET_KEEPCAPS, 1);

    printf("-----------------  after PR_SET_KEEPCAPS\n");
    capget(header, capdata);

    printf("effective=%x\n", capdata->effective);
    printf("permitted=%x\n", capdata->permitted);
    printf("inheritable=%x\n", capdata->inheritable);
    if (fork()) exit(0);

    printf("-----------------  before exec\n");
    capget(header, capdata);

    printf("effective=%x\n", capdata->effective);
    printf("permitted=%x\n", capdata->permitted);
    printf("inheritable=%x\n", capdata->inheritable);

    execlp("readfile", "readfile", "test1", "test2", (char *) 0);
    free(header);
    free(capdata);
    return 0;
}
```

---

## Conclusion

These experiments and demonstrations illustrate how Linux capabilities are managed and transformed within processes and containers. By manipulating these capabilities, we can achieve fine-grained control over process privileges, enhancing security and flexibility.

---

## Additional Resources

- [Linux Capabilities (man 7 capabilities)](https://man7.org/linux/man-pages/man7/capabilities.7.html)
- [PR_SET_KEEPCAPS Documentation](https://man7.org/linux/man-pages/man2/prctl.2.html)
- [Capability Bounding Set](https://www.kernel.org/doc/html/latest/userspace-api/capabilities.html)

