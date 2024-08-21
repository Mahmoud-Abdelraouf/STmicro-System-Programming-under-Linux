# **Doxygen Documentation Guide**

This guide provides detailed instructions on how to set up and use Doxygen to generate professional and comprehensive documentation for your project. Doxygen is a powerful tool that can produce high-quality documentation from annotated C/C++ sources, making it a critical tool in any developer's toolkit.

## **Table of Contents**
1. [Installation](#installation)
2. [Generating Documentation](#generating-documentation)
   - [Configuration Setup](#configuration-setup)
   - [Running Doxygen](#running-doxygen)
3. [Additional Features and Configurations](#additional-features-and-configurations)
   - [Customizing Output Formats](#customizing-output-formats)
   - [Enabling Diagrams and Charts](#enabling-diagrams-and-charts)
   - [Documenting Private Members](#documenting-private-members)
   - [Enabling Markdown Support](#enabling-markdown-support)
   - [Setting Up the Main Page](#setting-up-the-main-page)
   - [Improving Code Documentation](#improving-code-documentation)
   - [Using Doxygen Tags](#using-doxygen-tags)
4. [Dependency Management](#dependency-management)
5. [Conclusion](#conclusion)

---

## **Installation**

To begin using Doxygen, install it on your system using the following command:

```bash
sudo apt-get install -y doxygen
```

Additionally, if you plan to generate diagrams and charts, you will need Graphviz:

```bash
sudo apt-get install -y graphviz
```

## **Generating Documentation**

### **Configuration Setup**

1. **Generate a Default Configuration File:**

   Run the following command to create a `Doxyfile` configuration:

    ```bash
    doxygen -g
    ```

2. **Edit the Generated Configuration File (`Doxyfile`):**

   Open the `Doxyfile` in your preferred text editor and make the following modifications:

   ```bash
   # Set project name
   PROJECT_NAME = "My_Project"

   # Optimize output for C
   OPTIMIZE_OUTPUT_FOR_C = YES

   # Extract all documentation, including static and private members
   EXTRACT_ALL = YES
   EXTRACT_STATIC = YES
   EXTRACT_PRIVATE = YES

   # Set input directory (Assuming source and header files are in src/ and include/)
   INPUT = src include

   # Recursively search for input files
   RECURSIVE = YES

   # Generate source browser and include code comments
   SOURCE_BROWSER = YES
   INLINE_SOURCES = YES
   STRIP_CODE_COMMENTS = NO

   # Enable Graphviz for generating diagrams
   HAVE_DOT = YES
   DOT_NUM_THREADS = 4

   # Generate call graphs and caller graphs
   CALL_GRAPH = YES
   CALLER_GRAPH = YES

   # Set output directory
   OUTPUT_DIRECTORY = docs/doxygen_output

   # Enable HTML output and LaTeX for PDF generation
   GENERATE_HTML = YES
   GENERATE_LATEX = YES
   GENERATE_PDF = YES
   ```

### **Running Doxygen**

After configuring the `Doxyfile`, generate your documentation by running:

```bash
doxygen Doxyfile
```

This command processes your source files and generates the documentation in the specified output directory.

## **Additional Features and Configurations**

### **Customizing Output Formats**

Doxygen can produce documentation in several formats, including HTML, PDF, RTF, and man pages. Enable these formats in the `Doxyfile`:

```bash
# Generate various output formats
GENERATE_HTML = YES
GENERATE_LATEX = YES
GENERATE_RTF = YES
GENERATE_XML = YES
GENERATE_MAN = YES
```

### **Enabling Diagrams and Charts**

Visual elements such as diagrams can significantly enhance your documentation. Doxygen supports Graphviz for generating various types of diagrams:

```bash
# Enable Graphviz and generate diagrams
HAVE_DOT = YES
CLASS_DIAGRAMS = YES
COLLABORATION_GRAPH = YES
INCLUDE_GRAPH = YES
INCLUDED_BY_GRAPH = YES
GRAPHICAL_HIERARCHY = YES
DOT_IMAGE_FORMAT = svg
```

Ensure Graphviz is installed on your system to enable these features.

### **Documenting Private Members**

To include private members in your documentation:

```bash
# Extract documentation for private members
EXTRACT_PRIVATE = YES
```

### **Enabling Markdown Support**

If you prefer using Markdown for your documentation:

```bash
# Enable Markdown support and treat .md files as documentation
MARKDOWN_SUPPORT = YES
EXTENSION_MAPPING = md=markdown
```

### **Setting Up the Main Page**

To set up a custom main page for your documentation:

1. **Create a Markdown or Text File** (e.g., `mainpage.md`):

   ```markdown
   # My_Project Documentation

   Welcome to the documentation for My_Project. This project is designed to...

   ![Project Logo](images/logo.png)
   ```

2. **Configure the `Doxyfile`:**

   ```bash
   # Set the main page to your markdown file
   USE_MDFILE_AS_MAINPAGE = mainpage.md
   ```

3. **Ensure the images are referenced correctly in your Markdown file**.

### **Improving Code Documentation**

Enhance the readability and completeness of your code documentation by using:

```bash
# Show brief descriptions of functions/classes on a single line
INLINE_INHERITED_MEMB = YES

# Document all code entities
EXTRACT_ALL = YES
```

### **Using Doxygen Tags**

Leverage Doxygen tags to provide additional context in your documentation:

- **`\author`**: Specifies the author of the file or function.
- **`\version`**: Documents the version of the project or specific components.
- **`\date`**: Indicates the creation or modification date.
- **`\warning`, `\note`, `\bug`**: Highlights important information or known issues.

Example:

```c
/**
 * @file    example.c
 * @author  John Doe
 * @version 1.0
 * @date    01 Jan 2024
 * @brief   This file contains the main function for the project.
 *
 * @warning This is a simple example and may not be production-ready.
 */
```

## **Dependency Management**

To ensure that Doxygen and its related features work seamlessly, ensure the following dependencies are installed:

### **Essential Dependencies**

- **Doxygen**:
  ```bash
  sudo apt-get install -y doxygen
  ```

- **Graphviz** (for generating diagrams):
  ```bash
  sudo apt-get install -y graphviz
  ```

### **Optional Dependencies**

- **LaTeX** (for PDF generation):
  ```bash
  sudo apt-get install texlive-full
  ```

- **MathJax** (for rendering LaTeX equations in HTML):
  ```bash
  # No installation required; configure in Doxyfile
  USE_MATHJAX = YES
  MATHJAX_RELPATH = https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/
  ```

- **Python** (for additional scripting or extensions):
  ```bash
  sudo apt-get install python3
  ```

## **Conclusion**

This guide provides a comprehensive overview of setting up and using Doxygen to create professional documentation. By following the steps outlined above, you can generate detailed, visually appealing, and highly informative documentation for your project. For more advanced configurations and features, consult the official [Doxygen documentation](http://www.doxygen.nl/manual/index.html).
