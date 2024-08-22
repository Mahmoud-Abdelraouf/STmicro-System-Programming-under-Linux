# Wildcards in Linux: A Comprehensive Guide

## Table of Contents
1. [Introduction to Wildcards](#1-introduction-to-wildcards)
2. [Basic Wildcards](#2-basic-wildcards)
   - 2.1 [Asterisk `*`](#21-asterisk-)
   - 2.2 [Question Mark `?`](#22-question-mark-)
   - 2.3 [Square Brackets `[]`](#23-square-brackets-)
3. [Advanced Wildcards and Shell Globbing](#3-advanced-wildcards-and-shell-globbing)
   - 3.1 [Character Ranges](#31-character-ranges)
   - 3.2 [Negation in Square Brackets](#32-negation-in-square-brackets)
   - 3.3 [Brace Expansion `{}`](#33-brace-expansion-)
   - 3.4 [Extglob (Extended Globbing)](#34-extglob-extended-globbing)
4. [Special Characters and Wildcards](#4-special-characters-and-wildcards)
   - 4.1 [Dealing with Special Characters](#41-dealing-with-special-characters)
   - 4.2 [Escaping Wildcards](#42-escaping-wildcards)
5. [Differences Between `{}` and `[]`](#5-differences-between--and-)
6. [Using Wildcards with Other Commands](#6-using-wildcards-with-other-commands)
   - 6.1 [Using `touch` with Numeric Sequences](#61-using-touch-with-numeric-sequences)
   - 6.2 [Using `touch` with Alphabetic Sequences](#62-using-touch-with-alphabetic-sequences)
   - 6.3 [Combining Numeric and Alphabetic Sequences](#63-combining-numeric-and-alphabetic-sequences)
   - 6.4 [Mixing Letters and Numbers in File Names](#64-mixing-letters-and-numbers-in-file-names)
   - 6.5 [Using `mkdir` with Wildcards](#65-using-mkdir-with-wildcards)
   - 6.6 [Using `cp` and `mv` with Wildcards](#66-using-cp-and-mv-with-wildcards)
   - 6.7 [Extglob Pattern Examples](#67-extglob-pattern-examples)
7. [Conclusion](#7-conclusion)

---

## 1. Introduction to Wildcards

Wildcards are special characters used in the command line to represent one or more characters. They are used to perform operations on multiple files or directories based on pattern matching, allowing you to execute commands on a group of files without typing each name individually.

## 2. Basic Wildcards

### 2.1 Asterisk `*`

- **Usage**: Matches zero or more characters in a file or directory name.
- **Example**:
  ```bash
  ls *.txt
  ```
  This command lists all files ending in `.txt`.

### 2.2 Question Mark `?`

- **Usage**: Matches exactly one character in a file or directory name.
- **Example**:
  ```bash
  ls file?.txt
  ```
  This command lists files like `file1.txt`, `file2.txt`, but not `file10.txt`.

### 2.3 Square Brackets `[]`

- **Usage**: Matches any one of the characters enclosed within the square brackets.
- **Example**:
  ```bash
  ls file[12].txt
  ```
  This command lists files `file1.txt` and `file2.txt`.

## 3. Advanced Wildcards and Shell Globbing

### 3.1 Character Ranges

- **Usage**: Matches any character within a specified range.
- **Example**:
  ```bash
  ls file[1-5].txt
  ```
  This command lists files `file1.txt`, `file2.txt`, `file3.txt`, `file4.txt`, and `file5.txt`.

### 3.2 Negation in Square Brackets

- **Usage**: Matches any character **not** in the brackets by using `!` or `^` inside the brackets.
- **Example**:
  ```bash
  ls file[!1-3].txt
  ```
  This command lists files that do not start with `file1`, `file2`, or `file3`.

### 3.3 Brace Expansion `{}`

- **Usage**: Allows for the generation of arbitrary strings.
- **Example**:
  ```bash
  ls file{1,3,5}.txt
  ```
  This command lists `file1.txt`, `file3.txt`, and `file5.txt`.

### 3.4 Extglob (Extended Globbing)

- **Usage**: Provides advanced pattern matching capabilities. Requires enabling with `shopt -s extglob`.
- **Patterns**:
  - `?(pattern)`: Matches zero or one occurrence of the pattern.
  - `*(pattern)`: Matches zero or more occurrences of the pattern.
  - `+(pattern)`: Matches one or more occurrences of the pattern.
  - `@(pattern)`: Matches exactly one occurrence of the pattern.
  - `!(pattern)`: Matches anything except the pattern.
- **Example**:
  ```bash
  ls !(file[1-8]*)
  ```
  This command lists all files except those starting with `file1` to `file8`.

## 4. Special Characters and Wildcards

### 4.1 Dealing with Special Characters

Special characters like spaces, hyphens, and others can interfere with wildcard matching. To handle these, you might need to use escape sequences or quotes.

### 4.2 Escaping Wildcards

- **Usage**: Prevents the shell from interpreting a character as a wildcard.
- **Example**:
  ```bash
  ls file\*
  ```
  This command looks for a file literally named `file*`.

## 5. Differences Between `{}` and `[]`

### 5.1 Brace Expansion `{}`

- **Usage**: Brace expansion generates arbitrary strings based on patterns inside the braces.
- **Example**:
  ```bash
  touch file{1,2,3}.txt
  ```
  This creates `file1.txt`, `file2.txt`, and `file3.txt`.

- **Key Point**: `{}` is used to create specific strings or sequences that are manually defined inside the braces. It can also generate combinations of strings when multiple sets of braces are used.

### 5.2 Square Brackets `[]`

- **Usage**: Square brackets match any single character from the set of characters inside the brackets.
- **Example**:
  ```bash
  touch file[123].txt
  ```
  This creates `file1.txt`, `file2.txt`, and `file3.txt`.

- **Key Point**: `[]` is used to match a single character from a set of characters, allowing for more concise pattern matching when the character variations are limited to a single character position.

## 6. Using Wildcards with Other Commands

### 6.1 Using `touch` with Numeric Sequences

#### Example 1: Creating Files with a Simple Numeric Sequence

```bash
touch file{1..10}.txt
```

- **Result**: Creates `file1.txt`, `file2.txt`, ..., `file10.txt`.

#### Example 2: Creating Files with a Padded Numeric Sequence

```bash
touch file{01..10}.txt
```

- **Result**: Creates `file01.txt`, `file02.txt`, ..., `file10.txt`.

#### Example 3: Creating Files with Different Extensions Using Numeric Sequences

```bash
touch file{1..5}.{txt,log,md}
```

- **Result**: Creates `file1.txt`, `file1.log`, `file1.md`, ..., `file5.txt`, `file5.log`, `file5.md`.

### 6.2 Using `touch` with Alphabetic Sequences

#### Example 1: Creating Files with a Simple Alphabetic Sequence

```bash
touch file{a..e}.txt
```

- **Result**: Creates `filea.txt`, `fileb.txt`, ..., `filee.txt`.

#### Example 2: Creating Files with Upper and Lowercase Letters

```bash
touch file{A..C}.txt file{a..c}.txt
```

- **Result**: Creates `fileA.txt`, `fileB.txt`, `fileC.txt`, `filea.txt`, `fileb.txt`, `filec.txt`.

### 6.3 Combining Numeric and Alphabetic Sequences

#### Example 1: Creating Files with Combined Numeric and Alphabetic Sequences

```bash
touch file{1..3}_{a..c}.txt
```

- **Result**: Creates `file1_a.txt`, `file1_b.txt`, `file1_c.txt`, `file2_a.txt`, ..., `file3_c.txt`.

#### Example 2: Creating Files with Mixed Extensions and Sequences

```bash
touch report_{Jan,Feb,Mar}_{1..5}.pdf
```

- **Result**: Creates `report_Jan_1.pdf`, `report_Jan_2.pdf`, ..., `report_Mar_5.pdf`.

### 6.4 Mixing Letters and Numbers in File Names

#### Example 1: Creating Files with Letter and Number Combinations

```bash
touch file{A,B,C}{1,2,3}.txt
```

- **Result**

: Creates `fileA1.txt`, `fileA2.txt`, `fileA3.txt`, `fileB1.txt`, `fileB2.txt`, `fileB3.txt`, `fileC1.txt`, `fileC2.txt`, `fileC3.txt`.

#### Example 2: Creating Files with Complex Combinations of Letters, Numbers, and Extensions

```bash
touch {doc,report,summary}_{2021,2022}_v{1..3}.{docx,pdf,txt}
```

- **Result**: Creates files like `doc_2021_v1.docx`, `report_2022_v2.pdf`, `summary_2021_v3.txt`, etc.

#### Example 3: Creating Files with Padded Numbers and Letters

```bash
touch file_{A..C}_{01..05}.log
```

- **Result**: Creates `file_A_01.log`, `file_A_02.log`, ..., `file_C_05.log`.

### 6.5 Using `mkdir` with Wildcards

Wildcards can also be used with the `mkdir` command to create multiple directories at once.

#### Example 1: Creating Multiple Directories with a Numeric Sequence

```bash
mkdir dir{1..5}
```

- **Result**: Creates directories named `dir1`, `dir2`, ..., `dir5`.

#### Example 2: Creating Nested Directories with Brace Expansion

```bash
mkdir -p parent/{child1,child2,child3}
```

- **Result**: Creates a parent directory with three subdirectories `child1`, `child2`, and `child3`.

#### Example 3: Creating Directories with Mixed Letters and Numbers

```bash
mkdir dir{A,B,C}{1,2,3}
```

- **Result**: Creates directories named `dirA1`, `dirA2`, `dirA3`, `dirB1`, `dirB2`, `dirB3`, `dirC1`, `dirC2`, `dirC3`.

### 6.6 Using `cp` and `mv` with Wildcards

Wildcards are useful for copying and moving multiple files at once.

#### Example 1: Copying Files with a Specific Extension

```bash
cp *.txt /destination_directory/
```

- **Result**: Copies all `.txt` files to the specified destination directory.

#### Example 2: Moving Files with a Specific Name Pattern

```bash
mv report_*.pdf /archive_directory/
```

- **Result**: Moves all files starting with `report_` and ending in `.pdf` to the archive directory.

#### Example 3: Copying Multiple Files with Mixed Patterns

```bash
cp {doc,report,summary}_2021_v*.pdf /backup_directory/
```

- **Result**: Copies all PDF files with names starting with `doc_2021_v`, `report_2021_v`, and `summary_2021_v` to the backup directory.

### 6.7 Extglob Pattern Examples

Extglob (Extended Globbing) provides advanced pattern matching in the shell. Below are examples and explanations for each pattern. To use these patterns, you need to enable extglob with the following command:

```bash
shopt -s extglob
```

#### 6.7.1 `?(pattern)`: Matches Zero or One Occurrence of the Pattern

##### Example:

```bash
ls file?(1).txt
```

##### Explanation:

- **Pattern**: `?(1)`
- **Files**: `file.txt`, `file1.txt`
- **Result**: Matches files with zero or one occurrence of `1` after `file`. The command lists `file.txt` and `file1.txt`.

#### 6.7.2 `*(pattern)`: Matches Zero or More Occurrences of the Pattern

##### Example:

```bash
ls file*(1).txt
```

##### Explanation:

- **Pattern**: `*(1)`
- **Files**: `file.txt`, `file1.txt`, `file11.txt`, `file111.txt`
- **Result**: Matches files with zero or more occurrences of `1` after `file`. The command lists `file.txt`, `file1.txt`, `file11.txt`, `file111.txt`.

#### 6.7.3 `+(pattern)`: Matches One or More Occurrences of the Pattern

##### Example:

```bash
ls file+(1).txt
```

##### Explanation:

- **Pattern**: `+(1)`
- **Files**: `file1.txt`, `file11.txt`, `file111.txt`
- **Result**: Matches files with one or more occurrences of `1` after `file`. The command lists `file1.txt`, `file11.txt`, `file111.txt`.

#### 6.7.4 `@(pattern)`: Matches Exactly One Occurrence of the Pattern

##### Example:

```bash
ls file@(1).txt
```

##### Explanation:

- **Pattern**: `@(1)`
- **Files**: `file1.txt`
- **Result**: Matches files with exactly one occurrence of `1` after `file`. The command lists only `file1.txt`.

#### 6.7.5 `!(pattern)`: Matches Anything Except the Pattern

##### Example:

```bash
ls !(file[1-8]*).txt
```

##### Explanation:

- **Pattern**: `!(file[1-8]*)`
- **Files**: `file9.txt`, `file10.txt`, `anotherfile.txt`
- **Result**: Matches files that do not start with `file1` through `file8`. The command lists files like `file9.txt`, `file10.txt`, and any other files that do not match the pattern.

## 7. Conclusion

Wildcards in Linux are powerful tools for efficiently managing files and directories. From basic matching to advanced pattern exclusion, understanding and utilizing these tools can significantly enhance your command-line productivity. Whether you're dealing with large numbers of files or need to perform specific operations based on file patterns, wildcards offer the flexibility to get the job done quickly and effectively.
