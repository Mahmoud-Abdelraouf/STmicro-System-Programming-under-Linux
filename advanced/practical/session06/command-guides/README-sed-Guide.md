# `sed` Command in Linux: A Comprehensive Guide

## Table of Contents
1. [Introduction to the `sed` Command](#1-introduction-to-the-sed-command)
2. [Basic Syntax](#2-basic-syntax)
3. [Commonly Used Options](#3-commonly-used-options)
   - 3.1 [Substitute Command (`s`)](#31-substitute-command-s)
   - 3.2 [Global Replacement (`g`)](#32-global-replacement-g)
   - 3.3 [In-Place Editing (`-i`)](#33-in-place-editing--i)
   - 3.4 [Printing Lines (`p`)](#34-printing-lines-p)
   - 3.5 [Deleting Lines (`d`)](#35-deleting-lines-d)
   - 3.6 [Address Ranges](#36-address-ranges)
4. [Regular Expressions in `sed`](#4-regular-expressions-in-sed)
5. [Advanced Usage](#5-advanced-usage)
   - 5.1 [Multiple Commands](#51-multiple-commands)
   - 5.2 [Using `sed` with Files](#52-using-sed-with-files)
   - 5.3 [Transforming Text](#53-transforming-text)
   - 5.4 [Inserting and Appending Text](#54-inserting-and-appending-text)
   - 5.5 [Replacing Text with Variables](#55-replacing-text-with-variables)
   - 5.6 [Using `sed` in Scripts](#56-using-sed-in-scripts)
   - 5.7 [Advanced Pattern Matching](#57-advanced-pattern-matching)
6. [Practical Examples](#6-practical-examples)
   - 6.1 [Replace All Occurrences of a Word](#61-replace-all-occurrences-of-a-word)
   - 6.2 [Delete All Empty Lines](#62-delete-all-empty-lines)
   - 6.3 [Insert Text After a Specific Line](#63-insert-text-after-a-specific-line)
   - 6.4 [Replace Text Between Two Patterns](#64-replace-text-between-two-patterns)
   - 6.5 [Remove HTML Tags](#65-remove-html-tags)
   - 6.6 [Capitalize the First Letter of Each Word](#66-capitalize-the-first-letter-of-each-word)
   - 6.7 [Convert Tabs to Spaces](#67-convert-tabs-to-spaces)
   - 6.8 [Replace Multiple Patterns](#68-replace-multiple-patterns)
   - 6.9 [Replace Using Shell Variables](#69-replace-using-shell-variables)
   - 6.10 [Process a Log File and Extract Data](#610-process-a-log-file-and-extract-data)
   - 6.11 [Add Line Numbers to Non-Empty Lines](#611-add-line-numbers-to-non-empty-lines)
   - 6.12 [Swap the First Two Words on Each Line](#612-swap-the-first-two-words-on-each-line)
   - 6.13 [Find and Replace Using Multiple Patterns](#613-find-and-replace-using-multiple-patterns)
   - 6.14 [Comment Out Specific Lines in a Configuration File](#614-comment-out-specific-lines-in-a-configuration-file)
   - 6.15 [Modify a Specific Column in a CSV File](#615-modify-a-specific-column-in-a-csv-file)
7. [Conclusion](#7-conclusion)

---

## 1. Introduction to the `sed` Command

The `sed` command in Linux stands for **Stream Editor**. It is a powerful utility for parsing and transforming text in a data stream or file. `sed` allows you to perform complex text manipulations directly from the command line or within shell scripts, making it an essential tool for text processing tasks.

## 2. Basic Syntax

The basic syntax of the `sed` command is:

```bash
sed [options] 'command' file
```

- **`[options]`**: Various flags that control the behavior of `sed`.
- **`'command'`**: The command(s) that `sed` will apply to the input.
- **`file`**: The input file to be processed (can also be input from standard input).

## 3. Commonly Used Options

### 3.1 Substitute Command (`s`)

The substitute command `s` is used to search for a pattern and replace it with another.

```bash
sed 's/pattern/replacement/' file
```

- **Example**: Replace "foo" with "bar":
  ```bash
  sed 's/foo/bar/' file.txt
  ```

### 3.2 Global Replacement (`g`)

The `g` flag is used with the `s` command to replace all occurrences of the pattern in each line.

```bash
sed 's/pattern/replacement/g' file
```

- **Example**: Replace all occurrences of "foo" with "bar" in each line:
  ```bash
  sed 's/foo/bar/g' file.txt
  ```

### 3.3 In-Place Editing (`-i`)

The `-i` option allows you to edit files in place, saving the changes directly to the file.

```bash
sed -i 's/pattern/replacement/' file
```

- **Example**: Replace "foo" with "bar" in place:
  ```bash
  sed -i 's/foo/bar/' file.txt
  ```

### 3.4 Printing Lines (`p`)

The `p` command is used to print lines that match a pattern. When combined with the `-n` option, it only prints the lines that match.

```bash
sed -n '/pattern/p' file
```

- **Example**: Print lines containing "foo":
  ```bash
  sed -n '/foo/p' file.txt
  ```

### 3.5 Deleting Lines (`d`)

The `d` command deletes lines that match a pattern.

```bash
sed '/pattern/d' file
```

- **Example**: Delete lines containing "foo":
  ```bash
  sed '/foo/d' file.txt
  ```

### 3.6 Address Ranges

You can apply commands to specific lines or ranges of lines by specifying addresses.

```bash
sed '1,3d' file   # Deletes lines 1 to 3
sed '4,$d' file   # Deletes lines 4 to the end of the file
sed '/start/,/end/d' file   # Deletes from "start" to "end"
```

- **Example**: Delete lines from 5 to 10:
  ```bash
  sed '5,10d' file.txt
  ```

## 4. Regular Expressions in `sed`

`sed` supports regular expressions for matching patterns, providing powerful text manipulation capabilities.

- **`^`**: Matches the start of a line.
- **`$`**: Matches the end of a line.
- **`.`**: Matches any single character.
- **`*`**: Matches zero or more occurrences of the preceding character.
- **`[abc]`**: Matches any one of the characters `a`, `b`, or `c`.
- **`[a-z]`**: Matches any character in the range `a` to `z`.
- **`\(` and `\)`**: Grouping.
- **`\|`**: OR operator.

- **Example**: Replace "foo" or "bar" with "baz":
  ```bash
  sed 's/\(foo\|bar\)/baz/g' file.txt
  ```

## 5. Advanced Usage

### 5.1 Multiple Commands

You can apply multiple commands in a single `sed` invocation by separating them with semicolons or using the `-e` option.

```bash
sed 's/foo/bar/; s/baz/qux/' file
```

- **Example**: Replace "foo" with "bar" and "baz" with "qux":
  ```bash
  sed 's/foo/bar/; s/baz/qux/' file.txt
  ```

### 5.2 Using `sed` with Files

You can use `sed` to read and modify files directly.

```bash
sed 'commands' input_file > output_file
```

- **Example**: Replace "foo" with "bar" and save the result to a new file:
  ```bash
  sed 's/foo/bar/' file.txt > newfile.txt
  ```

### 5.3 Transforming Text

`sed` can transform text, such as converting lowercase letters to uppercase.

```bash
sed 'y/abc/ABC/' file
```

- **Example**: Convert all `a`, `b`, `c` to `A`, `B`, `C`:
  ```bash
  sed 'y/abc/ABC/' file.txt
  ```

### 5.4 Inserting and Appending Text

You can insert or append text to lines that match a pattern.

- **Insert**:
  ```bash
  sed '/pattern/i\new text' file
  ```

- **Append**:
  ```bash
  sed '/pattern/a\new text' file
  ```

- **Example**: Insert "Hello" before lines

 containing "foo":
  ```bash
  sed '/foo/i\Hello' file.txt
  ```

- **Example**: Append "Goodbye" after lines containing "foo":
  ```bash
  sed '/foo/a\Goodbye' file.txt
  ```

### 5.5 Replacing Text with Variables

You can use shell variables within `sed` commands by using double quotes instead of single quotes.

```bash
sed "s/$old/$new/g" file
```

- **Example**: Replace `$old` with `$new`:
  ```bash
  old="foo"
  new="bar"
  sed "s/$old/$new/g" file.txt
  ```

### 5.6 Using `sed` in Scripts

`sed` is commonly used in shell scripts for batch processing of text files.

```bash
#!/bin/bash
sed 's/foo/bar/g' file.txt
```

- **Example**: A script to replace "foo" with "bar" in multiple files:
  ```bash
  #!/bin/bash
  for file in *.txt; do
    sed -i 's/foo/bar/g' "$file"
  done
  ```

### 5.7 Advanced Pattern Matching

#### Using Multiple Patterns

You can combine multiple patterns to perform more complex text processing tasks.

- **Match multiple patterns on different lines**:
  ```bash
  sed '/pattern1/ { N; /pattern2/ s/foo/bar/; }' file
  ```

  - **Example**: Replace "foo" with "bar" only if "pattern1" is followed by "pattern2" on the next line:
    ```bash
    sed '/pattern1/ { N; /pattern2/ s/foo/bar/; }' file.txt
    ```

- **Match and replace patterns across multiple lines**:
  ```bash
  sed -z 's/pattern1.*pattern2/replacement/' file
  ```

  - **Example**: Replace text between "start" and "end" with "replacement":
    ```bash
    sed -z 's/start.*end/replacement/' file.txt
    ```

#### Conditional Substitutions

You can use conditional expressions within `sed` to apply different substitutions based on the content of the line.

- **Example**: Replace "foo" with "bar" only if the line also contains "baz":
  ```bash
  sed '/baz/ s/foo/bar/' file.txt
  ```

- **Example**: Replace "foo" with "bar" on lines where "baz" is not present:
  ```bash
  sed '/baz/! s/foo/bar/' file.txt
  ```

#### Using Hold and Pattern Space

`sed` provides a hold space (a temporary buffer) that can be used for more advanced text processing.

- **Example**: Swap two lines:
  ```bash
  sed 'N; s/\(.*\)\n\(.*\)/\2\n\1/' file.txt
  ```

- **Explanation**: The `N` command reads the next line into the pattern space, and the `s` command swaps the two lines.

## 6. Practical Examples

### 6.1 Replace All Occurrences of a Word

```bash
sed 's/oldword/newword/g' file.txt
```

- **Example**: Replace all instances of "apple" with "orange":
  ```bash
  sed 's/apple/orange/g' file.txt
  ```

### 6.2 Delete All Empty Lines

```bash
sed '/^$/d' file.txt
```

- **Explanation**: This deletes all lines that are empty (i.e., lines with nothing between the start `^` and end `$` of the line).

### 6.3 Insert Text After a Specific Line

```bash
sed '/pattern/a\new text' file.txt
```

- **Example**: Insert "New Line" after every line containing "Header":
  ```bash
  sed '/Header/a\New Line' file.txt
  ```

### 6.4 Replace Text Between Two Patterns

```bash
sed '/start/,/end/s/foo/bar/g' file.txt
```

- **Example**: Replace "foo" with "bar" only between "START" and "END":
  ```bash
  sed '/START/,/END/s/foo/bar/g' file.txt
  ```

### 6.5 Remove HTML Tags

```bash
sed 's/<[^>]*>//g' file.txt
```

- **Explanation**: This removes all HTML tags (anything within `< >` brackets).

### 6.6 Capitalize the First Letter of Each Word

```bash
sed 's/\b\(.\)/\u\1/g' file.txt
```

- **Explanation**: This capitalizes the first letter of every word.

### 6.7 Convert Tabs to Spaces

```bash
sed 's/\t/    /g' file.txt
```

- **Explanation**: This replaces each tab character with four spaces.

### 6.8 Replace Multiple Patterns

```bash
sed -e 's/foo/bar/g' -e 's/baz/qux/g' file.txt
```

- **Explanation**: This replaces "foo" with "bar" and "baz" with "qux" in a single pass.

### 6.9 Replace Using Shell Variables

```bash
old="foo"
new="bar"
sed "s/$old/$new/g" file.txt
```

- **Explanation**: This replaces the value of the variable `$old` with `$new`.

### 6.10 Process a Log File and Extract Data

```bash
sed -n '/ERROR/{s/.*ERROR: //;p;}' logfile.txt
```

- **Explanation**: This extracts lines that contain "ERROR" and prints only the error message.

### 6.11 Add Line Numbers to Non-Empty Lines

```bash
sed '/./=' file.txt | sed 'N; s/\n/ /'
```

- **Explanation**: This adds line numbers to non-empty lines.

### 6.12 Swap the First Two Words on Each Line

```bash
sed 's/^\([[:alpha:]]\+\) \([[:alpha:]]\+\)/\2 \1/' file.txt
```

- **Explanation**: This swaps the first two words on each line.

### 6.13 Find and Replace Using Multiple Patterns

```bash
sed '/pattern1/s/foo/bar/g; /pattern2/s/baz/qux/g' file.txt
```

- **Example**: Replace "foo" with "bar" on lines matching "pattern1" and "baz" with "qux" on lines matching "pattern2":
  ```bash
  sed '/header/s/foo/bar/g; /footer/s/baz/qux/g' file.txt
  ```

### 6.14 Comment Out Specific Lines in a Configuration File

```bash
sed '/pattern/s/^/# /' config.conf
```

- **Example**: Comment out lines containing "option":
  ```bash
  sed '/option/s/^/# /' config.conf
  ```

### 6.15 Modify a Specific Column in a CSV File

```bash
sed 's/\([^,]*,\)\{2\}oldvalue/newvalue/' file.csv
```

- **Explanation**: This replaces "oldvalue" with "newvalue" in the third column of a CSV file.

## 7. Applying `sed` Examples to a Sample File

To demonstrate the `sed` command in action, we will create a sample text file and apply each of the practical examples discussed above.

### 7.1 Generate a Sample Text File

```bash
cat << EOF > sample.txt
This is a test file.
It contains multiple lines,
including empty lines,
and lines with different patterns.
Header: This line contains the word 'foo' and some HTML tags <b>bold</b>.
Here is another line with 'foo' and 'baz'.
START: This block contains 'foo' that needs to be replaced.
This line does not have the pattern.
END: The block ends here.
apple orange banana
Tabs	are	used	in	this	line.
Error: An ERROR occurred while processing.
Options: Use option1 or option2.
This line contains the third, fourth, and fifth columns.
EOF
```

### 7.2 Apply the `sed` Commands

#### 6.1 Replace All Occurrences of a Word

```bash
sed 's/apple/orange/g' sample.txt
```

#### 6.2 Delete All Empty Lines

```bash
sed '/^$/d' sample.txt
```

#### 6.3 Insert Text After a Specific Line

```bash
sed '/Header/a\This line was inserted after "Header:"' sample.txt
```

#### 6.4 Replace Text Between Two Patterns

```bash
sed '/START/,/END/s/foo/bar/g' sample.txt
```

#### 6.5 Remove HTML Tags

```bash
sed 's/<[^>]*>//g' sample.txt
```

#### 6.6 Capitalize the First Letter of Each Word

```bash
sed 's/\b\(.\)/\u\1/g' sample.txt
```

#### 6.7 Convert Tabs to Spaces

```bash
sed 's/\t/    /g' sample.txt
```

#### 6.8 Replace Multiple Patterns

```bash
sed -e 's/foo/bar/g' -e 's/baz/qux/g' sample.txt
```

#### 6.9 Replace Using Shell Variables

```bash
old="foo"
new="bar"
sed "s/$old/$new/g" sample.txt
```

#### 6.10 Process a Log File and Extract Data

```bash
sed -n '/ERROR/{s/.*ERROR: //;p;}' sample.txt
```

#### 6.11 Add Line Numbers to Non-Empty Lines

```bash
sed '/./=' sample.txt | sed 'N; s/\n/ /'
```

#### 6.12 Swap the First Two Words on Each Line

```bash
sed 's/^\([[:alpha:]]\+\) \([[:alpha:]]\+\)/\2 \1/' sample.txt
```

#### 6.13 Find and Replace Using Multiple Patterns

```bash
sed '/Header/s/foo/bar/g; /Options/s/option1/optionA/g' sample.txt
```

#### 6.14 Comment Out Specific Lines in a Configuration File

```bash
sed '/Options/s/^/# /' sample.txt
```

#### 6.15 Modify a Specific Column in a CSV File

Let's simulate a CSV structure in our text file:

```bash
echo "col1,col2,col3,col4,col5" > sample.csv
echo "a,b,c,d,e" >> sample.csv
echo "f,g,h,i,j" >> sample.csv
echo "k,l,m,n,o" >> sample.csv

sed 's/\([^,]*,\)\{2\}c/newvalue/' sample.csv
```

### 7.3 Verify Changes

After applying each command, you can view the contents of `sample.txt` and `sample.csv` to verify the changes:

```bash
cat sample.txt
cat sample.csv
```

---

## 8. Conclusion

The `sed` command is a powerful tool for text processing in Linux, offering a wide range of features from simple text replacement to complex text transformations. Whether you're editing files on the fly, processing logs, or automating tasks in scripts, `sed` provides the flexibility and control needed for efficient text manipulation.
