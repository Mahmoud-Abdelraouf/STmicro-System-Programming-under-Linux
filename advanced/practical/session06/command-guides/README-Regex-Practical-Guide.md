# Sample Text File Analysis Using Regular Expressions

This guide provides examples of using regular expressions (regex) with various command-line tools to analyze and manipulate a text file named `sample_text.txt`.

## Table of Contents

1. [Text Example](#1-text-example)
2. [Understanding Lookahead](#2-understanding-lookahead)
   - 2.1 [Positive Lookahead](#21-positive-lookahead)
   - 2.2 [Negative Lookahead](#22-negative-lookahead)
3. [Escaping Characters with `\`](#3-escaping-characters-with-)
4. [Common Regex Metacharacters](#4-common-regex-metacharacters)
   - 4.1 [Word Boundary `\b`](#41-word-boundary-b)
   - 4.2 [Word Character `\w`](#42-word-character-w)
   - 4.3 [Digit Character `\d`](#43-digit-character-d)
5. [Practical Examples Using `grep`, `sed`, and `awk`](#5-practical-examples-using-grep-sed-and-awk)
   - 5.1 [Finding Lines That Start with "Error" or "Warning"](#51-finding-lines-that-start-with-error-or-warning)
   - 5.2 [Finding Lines That Contain a Valid Email Address](#52-finding-lines-that-contain-a-valid-email-address)
   - 5.3 [Finding Lines with Three or More Consecutive Vowels](#53-finding-lines-with-three-or-more-consecutive-vowels)
   - 5.4 [Excluding Lines That Start with a Comment](#54-excluding-lines-that-start-with-a-comment)
   - 5.5 [Replacing `"foo"` with `"bar"`](#55-replacing-foo-with-bar)
   - 5.6 [Replacing Phone Numbers with Asterisks](#56-replacing-phone-numbers-with-asterisks)
   - 5.7 [Printing Lines That Start with "Hello"](#57-printing-lines-that-start-with-hello)
   - 5.8 [Printing the First Column of Lines That Contain the Word "ERROR"](#58-printing-the-first-column-of-lines-that-contain-the-word-error)

---

## 1. Text Example

Here is the text from `sample_text.txt` that you can use with the commands in this guide:

```text
Hello, world!
The quick brown fox jumps over the lazy dog.
user@example.com
user.name@sub.domain.com
(123) 456-7890
ERROR: An error occurred
ERROR: File not found
ERROR: Timeout error
My phone number is 123-456-7890.
This is a word in a sentence, but not sword or wording.
The rain in Spain stays mainly in the plain.
foo, bar, and baz
This is hello hello world.
https://www.example.com
http://example.com/page
192.168.1.1
999.999.999.999
12/25/2020
13/25/2020
01/01/2021
Total 123
Total 456
User John Doe
apple orange banana
ERROR: Something went wrong!
```

## 2. Understanding Lookahead

Lookahead is a feature in regular expressions that allows you to assert the existence or non-existence of a pattern following the current position in the string, without including it in the match.

### 2.1 Positive Lookahead

A positive lookahead asserts that a specific pattern **must** follow the current position.

**Syntax:** `X(?=Y)`

- `X`: The pattern to match.
- `Y`: The pattern that must follow `X`.

**Example:**

```regex
\w+(?=\d)
```

- **Explanation:** Matches any word that is immediately followed by a digit.
- **Text:** `"abc123 def456"`
- **Matches:** `"abc"`, `"def"`

### 2.2 Negative Lookahead

A negative lookahead asserts that a specific pattern **must not** follow the current position.

**Syntax:** `X(?!Y)`

- `X`: The pattern to match.
- `Y`: The pattern that must **not** follow `X`.

**Example:**

```regex
\w+(?!\d)
```

- **Explanation:** Matches any word that is **not** immediately followed by a digit.
- **Text:** `"abc123 def456 ghi"`
- **Matches:** `"ghi"`

## 3. Escaping Characters with `\`

In regular expressions, certain characters have special meanings. To use these characters literally (as they are), you need to "escape" them by preceding them with a backslash (`\`).

### Examples:

- **Period (`.`)**: Normally matches any character. To match a literal period, use `\.`.

  ```regex
  \.
  ```

  - **Matches:** `"file.txt"` in `"file.txt"`, but not `"filetxt"`.

- **Asterisk (`*`)**: Normally matches zero or more occurrences of the preceding element. To match a literal asterisk, use `\*`.

  ```regex
  \*
  ```

  - **Matches:** `"2 * 3"` in `"2 * 3 = 6"`.

## 4. Common Regex Metacharacters

### 4.1 Word Boundary `\b`

The `\b` metacharacter matches a word boundary, which is the position between a word character (typically letters, digits, or underscores) and a non-word character (such as spaces or punctuation) or the start/end of a string.

**Examples:**

- **`\bword\b`**: Matches the word "word" as a standalone word.

  ```regex
  \bword\b
  ```

  - **Matches:** `"word"` in `"This is a word in a sentence"`.
  - **Does NOT match:** `"sword"` or `"wording"`.

### 4.2 Word Character `\w`

The `\w` metacharacter matches any word character, which includes letters (a-z, A-Z), digits (0-9), and underscores (`_`).

**Examples:**

- **`\w+`**: Matches one or more word characters.

  ```regex
  \w+
  ```

  - **Matches:** `"Hello"`, `"123"`, and `"user_name"`.

### 4.3 Digit Character `\d`

The `\d` metacharacter matches any digit character (0-9).

**Examples:**

- **`\d{3}`**: Matches exactly three digits.

  ```regex
  \d{3}
  ```

  - **Matches:** `"123"` in `"My phone number is 123-456-7890"`.
  - **Does NOT match:** `"12"` or `"1234"`.

## 5. Practical Examples Using `grep`, `sed`, and `awk`

### 5.1 Finding Lines That Start with "Error" or "Warning"

```bash
grep -E "^(Error|Warning)" sample_text.txt
```

- **Explanation:** This command finds lines that start with either "Error" or "Warning".

### 5.2 Finding Lines That Contain a Valid Email Address

```bash
grep -E "[\w\.-]+@[a-zA-Z\d\.-]+\.[a-zA-Z]{2,6}" sample_text.txt
```

- **Explanation:** This command finds lines in the file that contain valid email addresses.

### 5.3 Finding Lines with Three or More Consecutive Vowels

```bash
grep -E "[aeiou]{3,}" sample_text.txt
```

- **Explanation:** This command finds lines that contain three or more consecutive vowels.

### 5.4 Excluding Lines That Start with a Comment

```bash
grep -vE "^#" sample_text.txt
```

- **Explanation:** This command excludes lines that start with a comment character (`#`).

### 5.5 Replacing `"foo"` with `"bar"`

```bash
sed -E 's/\bfoo\b/bar/g' sample_text.txt
```

- **Explanation:** This command replaces occurrences of `"foo"` with `"bar"` in the file.

### 5.6 Replacing Phone Numbers with Asterisks

```bash
sed -E 's/[0-9]{3}-[0-9]{4}/****/g' sample_text.txt
```

- **Explanation:** This command masks phone numbers in the file by replacing them with asterisks.

### 5.7 Printing Lines That Start with "Hello"

```bash
awk '/^Hello/ { print $0 }' sample_text.txt
```

- **Explanation:** This command prints lines that start with the word "Hello".

### 5.8 Printing the First Column of Lines That Contain the Word "ERROR"

```bash
awk '/ERROR/ { print $1 }' sample_text.txt
```

- **Explanation:** This command prints the first column of lines that contain the word "ERROR".
