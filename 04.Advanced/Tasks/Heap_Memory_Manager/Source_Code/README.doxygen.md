# Using Doxygen for Documentation

## Installation

To install Doxygen on your machine, you can use the following command:

```bash
sudo apt-get install -y doxygen
```

## Generating Documentation

1. Generate a default configuration file by running:

```bash
doxygen -g
```

2. Edit the generated configuration file (`Doxyfile`) and make the following changes:

```bash
# Set project name
PROJECT_NAME           = "My_Project"

# Optimize output for C
OPTIMIZE_OUTPUT_FOR_C  = YES

# Extract all documentation
EXTRACT_ALL            = YES

# Extract static members
EXTRACT_STATIC         = YES

# Set input directory
INPUT                  = src/

# Recursively search for input files
RECURSIVE              = YES

# Generate source browser
SOURCE_BROWSER         = YES

# Enable Graphviz for dot files
HAVE_DOT               = YES

# Set the number of threads for Graphviz
DOT_NUM_THREADS        = 4

# Generate call graphs
CALL_GRAPH             = YES

# Generate caller graphs
CALLER_GRAPH           = YES
```

3. Once you've made the necessary changes, run the following command to generate the documentation:

```bash
doxygen Doxyfile
```

## Additional Configuration

Feel free to explore other configuration options available in the `Doxyfile` to customize your documentation according to your project's needs.

For more detailed information about Doxygen and its features, refer to the official [Doxygen documentation](http://www.doxygen.nl/manual/index.html).
---

This README provides a concise guide for installing Doxygen, generating documentation, and customizing configuration options. Additionally, it includes a link to the official Doxygen documentation for further reference.
