# Regular Expressions and Wildcards Guide

## Introduction

Regular expressions (regex) and wildcards are powerful tools used in text processing, search, and manipulation. While wildcards are typically used in file and command line operations, regular expressions are used for pattern matching within text.

### Table of Contents

1. [Introduction](#introduction)
2. [Regular Expressions](#regular-expressions)
   - [Basic Syntax](#basic-syntax)
   - [Character Classes](#character-classes)
   - [Quantifiers](#quantifiers)
   - [Anchors](#anchors)
   - [Groups and Ranges](#groups-and-ranges)
   - [Escaping Characters](#escaping-characters)
   - [Examples](#examples)
3. [Wildcards](#wildcards)
   - [Basic Wildcards](#basic-wildcards)
   - [Advanced Wildcards](#advanced-wildcards)
   - [Examples](#examples-1)
4. [Resources](#resources)

---

## Regular Expressions

### Basic Syntax

Regular expressions are patterns used to match character combinations in strings. Here are some basic elements:

- `.`: Matches any single character except newline.
- `^`: Matches the start of a string.
- `$`: Matches the end of a string.

### Character Classes

Character classes match any one of a set of characters.

- `[abc]`: Matches any single character 'a', 'b', or 'c'.
- `[^abc]`: Matches any single character except 'a', 'b', or 'c'.
- `[a-z]`: Matches any single lowercase letter.
- `[A-Z]`: Matches any single uppercase letter.
- `[0-9]`: Matches any single digit.

### Quantifiers

Quantifiers specify how many instances of a character, group, or character class must be present in the input for a match to be found.

- `*`: Matches 0 or more occurrences.
- `+`: Matches 1 or more occurrences.
- `?`: Matches 0 or 1 occurrence.
- `{n}`: Matches exactly n occurrences.
- `{n,}`: Matches n or more occurrences.
- `{n,m}`: Matches between n and m occurrences.

### Anchors

Anchors are used to specify the position within a string where a match must occur.

- `^`: Matches the start of a string.
- `$`: Matches the end of a string.
- `\b`: Matches a word boundary.
- `\B`: Matches a non-word boundary.

### Groups and Ranges

- `(abc)`: Matches the exact sequence 'abc'.
- `(a|b|c)`: Matches 'a', 'b', or 'c'.
- `(a|bc)`: Matches 'a' or 'bc'.

### Escaping Characters

Special characters can be escaped to match their literal values.

- `\.`: Matches a literal dot.
- `\*`: Matches a literal asterisk.
- `\\`: Matches a literal backslash.

### Examples

1. Matching an email address:
   ```bash
   echo "example@example.com" | grep -E '^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
   ```

2. Matching a phone number:
   ```bash
   echo "(123) 456-7890" | grep -E '^\(\d{3}\) \d{3}-\d{4}$'
   ```

3. Matching a date (YYYY-MM-DD):
   ```bash
   echo "2024-08-01" | grep -E '^\d{4}-\d{2}-\d{2}$'
   ```

4. Matching a time (HH:MM:SS):
   ```bash
   echo "12:34:56" | grep -E '^[0-2][0-9]:[0-5][0-9]:[0-5][0-9]$'
   ```

5. Matching a URL:
   ```bash
   echo "https://www.example.com" | grep -E '^(http|https)://[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
   ```

6. Matching a hexadecimal color code:
   ```bash
   echo "#a3c113" | grep -E '^#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$'
   ```

7. Matching a username (alphanumeric, 3-16 characters):
   ```bash
   echo "user123" | grep -E '^[a-zA-Z0-9]{3,16}$'
   ```

8. Matching an IP address:
   ```bash
   echo "192.168.1.1" | grep -E '^([0-9]{1,3}\.){3}[0-9]{1,3}$'
   ```

## Wildcards

### Basic Wildcards

Wildcards are symbols that represent one or more characters. They are commonly used in shell commands.

- `*`: Matches any number of characters, including none.
- `?`: Matches exactly one character.

### Advanced Wildcards

Advanced wildcards are used in more specific matching scenarios.

- `[abc]`: Matches any one of the characters 'a', 'b', or 'c'.
- `[!abc]`: Matches any character except 'a', 'b', or 'c'.
- `[a-z]`: Matches any lowercase letter.
- `[A-Z]`: Matches any uppercase letter.
- `[0-9]`: Matches any digit.

### Examples

1. Listing all `.txt` files in a directory:
   ```bash
   ls *.txt
   ```

2. Finding files with a single character extension:
   ```bash
   ls *.
   ```

3. Matching files starting with 'a' and ending with 'z':
   ```bash
   ls a*z
   ```

4. Excluding certain files:
   ```bash
   ls [!abc]*
   ```

5. Listing files that start with 'file' and have a single character extension:
   ```bash
   ls file.?
   ```

6. Listing files that start with 'data' followed by any two characters:
   ```bash
   ls data??
   ```

7. Listing files that start with any letter and end with '.log':
   ```bash
   ls [a-zA-Z]*.log
   ```

8. Listing files with numeric names:
   ```bash
   ls [0-9]*
   ```

9. Listing files with specific extensions:
   ```bash
   ls *.{txt,pdf,doc}
   ```

## Resources

To deepen your understanding, check out these resources:

- **Regular Expressions**
  - [Regular Expressions Tutorial](https://www.regular-expressions.info/)
  - [RegexOne](https://regexone.com/)
  - [Regex101](https://regex101.com/)

- **Wildcards**
  - [Linux Wildcards Tutorial](https://tldp.org/LDP/GNU-Linux-Tools-Summary/html/x11655.htm)
  - [Wildcards in Linux](https://www.cyberciti.biz/faq/using-wildcards-in-unix-or-linux-shell-commands/)

---

By mastering regular expressions and wildcards, you'll be able to perform complex text searches, manipulations, and file operations with ease. Happy learning!
