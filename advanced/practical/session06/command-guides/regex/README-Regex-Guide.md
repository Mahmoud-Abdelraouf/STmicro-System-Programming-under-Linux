# Regular Expressions (Regex) in Linux: A Comprehensive Guide

## Table of Contents
1. [Introduction to Regular Expressions](#1-introduction-to-regular-expressions)
2. [Basic Syntax and Meta-Characters](#2-basic-syntax-and-meta-characters)
   - 2.1 [Anchors](#21-anchors)
   - 2.2 [Character Classes](#22-character-classes)
   - 2.3 [Quantifiers](#23-quantifiers)
   - 2.4 [Groups and Alternation](#24-groups-and-alternation)
3. [Advanced Features](#3-advanced-features)
   - 3.1 [Lookahead and Lookbehind](#31-lookahead-and-lookbehind)
   - 3.2 [Non-Greedy Matching](#32-non-greedy-matching)
   - 3.3 [Backreferences](#33-backreferences)
4. [Practical Examples](#4-practical-examples)
   - 4.1 [Validating an Email Address](#41-validating-an-email-address)
   - 4.2 [Finding a Specific Word in a Text](#42-finding-a-specific-word-in-a-text)
   - 4.3 [Matching Phone Numbers](#43-matching-phone-numbers)
   - 4.4 [Extracting Data from a Log File](#44-extracting-data-from-a-log-file)
   - 4.5 [Replacing Text Patterns in Files](#45-replacing-text-patterns-in-files)
   - 4.6 [Matching HTML Tags](#46-matching-html-tags)
   - 4.7 [Splitting a CSV File](#47-splitting-a-csv-file)
   - 4.8 [Password Validation](#48-password-validation)
   - 4.9 [Matching Dates](#49-matching-dates)
   - 4.10 [Removing Duplicates](#410-removing-duplicates)
   - 4.11 [Extracting URLs from Text](#411-extracting-urls-from-text)
   - 4.12 [Matching IP Addresses](#412-matching-ip-addresses)
5. [Regular Expressions in Different Tools](#5-regular-expressions-in-different-tools)
   - 5.1 [Using Regex with `grep`](#51-using-regex-with-grep)
   - 5.2 [Using Regex with `sed`](#52-using-regex-with-sed)
   - 5.3 [Using Regex with `awk`](#53-using-regex-with-awk)
   - 5.4 [Using Regex in Programming Languages](#54-using-regex-in-programming-languages)
6. [Testing Your Regular Expressions](#6-testing-your-regular-expressions)
   - 6.1 [Using `echo` with `grep`](#61-using-echo-with-grep)
   - 6.2 [Using `pcregrep` for Advanced Patterns](#62-using-pcregrep-for-advanced-patterns)
7. [Conclusion](#7-conclusion)

---

## 1. Introduction to Regular Expressions

Regular expressions (regex) are sequences of characters that define search patterns, primarily used for string matching and manipulation. They are widely used in text processing tools, programming languages, and command-line utilities like `grep`, `sed`, and `awk`. Mastering regex allows for powerful text searching, filtering, and replacing capabilities.

## 2. Basic Syntax and Meta-Characters

### 2.1 Anchors

- **`^`**: Matches the start of a line.
  - **Examples**:
    - `^Hello` matches any line that starts with "Hello".
    - `^A` matches any line that starts with the letter "A".
    - `^[0-9]` matches any line that starts with a digit.

- **`$`**: Matches the end of a line.
  - **Examples**:
    - `world$` matches any line that ends with "world".
    - `!$` matches any line that ends with an exclamation mark.
    - `\.$` matches any line that ends with a period.

### 2.2 Character Classes

- **`[abc]`**: Matches any one of the characters `a`, `b`, or `c`.
  - **Examples**:
    - `gr[aeiou]p` matches "grape", "gripe", etc.
    - `[aeiou]` matches any vowel.
    - `t[aeiou]p` matches "tap", "tip", "top", etc.

- **`[^abc]`**: Matches any character except `a`, `b`, or `c`.
  - **Examples**:
    - `[^0-9]` matches any non-digit character.
    - `[^aeiou]` matches any non-vowel character.
    - `[^a-zA-Z]` matches any non-alphabetic character.

- **`[a-z]`**: Matches any character in the specified range.
  - **Examples**:
    - `[a-z]` matches any lowercase letter.
    - `[A-Z]` matches any uppercase letter.
    - `[0-9]` matches any digit.

### 2.3 Quantifiers

- **`*`**: Matches 0 or more occurrences of the preceding element.
  - **Examples**:
    - `a*` matches "a", "aa", and "" (empty string).
    - `ba*` matches "b", "ba", "baa", etc.
    - `.*` matches any string of characters.

- **`+`**: Matches 1 or more occurrences of the preceding element.
  - **Examples**:
    - `a+` matches "a", "aa", but not "".
    - `ba+` matches "ba", "baa", but not "b".
    - `[a-z]+` matches any string of lowercase letters.

- **`?`**: Matches 0 or 1 occurrence of the preceding element.
  - **Examples**:
    - `a?` matches "a" and "".
    - `colou?r` matches "color" and "colour".
    - `[0-9]?` matches any single digit or nothing.

- **`{n}`**: Matches exactly `n` occurrences.
  - **Examples**:
    - `a{3}` matches "aaa".
    - `[0-9]{2}` matches any two-digit number.
    - `a{2,3}` matches "aa" or "aaa".

- **`{n,}`**: Matches `n` or more occurrences.
  - **Examples**:
    - `a{2,}` matches "aa", "aaa", etc.
    - `\d{3,}` matches any number with at least three digits.
    - `[a-z]{5,}` matches any word with at least five letters.

- **`{n,m}`**: Matches between `n` and `m` occurrences.
  - **Examples**:
    - `a{2,4}` matches "aa", "aaa", and "aaaa".
    - `[0-9]{2,4}` matches any two to four-digit number.
    - `[a-z]{3,5}` matches any word with three to five letters.

### 2.4 Groups and Alternation

- **`()`**: Groups multiple tokens together.
  - **Examples**:
    - `(abc)+` matches "abc", "abcabc", etc.
    - `(go|went|gone)` matches "go", "went", or "gone".
    - `([A-Z][a-z]+)` matches capitalized words.

- **`|`**: Acts as a logical OR between expressions.
  - **Examples**:
    - `cat|dog` matches "cat" or "dog".
    - `red|blue|green` matches "red", "blue", or "green".
    - `one|two|three` matches "one", "two", or "three".

## 3. Advanced Features

### 3.1 Lookahead and Lookbehind

- **Positive Lookahead `(?=...)`**: Asserts that a certain pattern must follow.
  - **Examples**:
    - `foo(?=bar)` matches "foo" only if it is followed by "bar".
    - `\d(?=\.\d{2})` matches a digit only if it is followed by a period and two more digits (like a decimal number).
    - `[A-Z](?=[a-z])` matches an uppercase letter only if it is followed by a lowercase letter.

- **Negative Lookahead `(?!...)`**: Asserts that a certain pattern must not follow.
  - **Examples**:
    - `foo(?!bar)` matches "foo" only if it is NOT followed by "bar".
    - `\d(?!\.\d{2})` matches a digit only if it is NOT followed by a period and two more digits.
    - `[A-Z](?![a-z])` matches an uppercase letter only if it is NOT followed by a lowercase letter.

- **Positive Lookbehind `(?<=...)`**: Asserts that a certain pattern must precede.
  - **Examples**:
    - `(?<=foo)bar` matches "bar" only if it is preceded by "foo".
    - `(?<=\d{3})\d{4}` matches the last four digits of a phone number that is preceded by exactly three digits.
    - `(?<=@)[a-zA-Z]+` matches the domain part of an email address.

- **Negative Lookbehind `(?<!...)`**: Asserts that a certain pattern must not precede.
  - **Examples**:
    - `(?<!foo)bar` matches "bar" only if it is NOT preceded by "foo".
    - `(?<!\d{3})\d{4}` matches the last four digits of a phone number that is NOT preceded by exactly three digits.
    - `(?<!@)[a-zA-Z]+` matches text that is NOT the domain part of an email address.

### 3.2 Non-Greedy Matching

- **`*?`**: Matches as few characters as possible.
  - **Examples**:
    - `<.*?>` matches the smallest HTML tags.
    - `".*?"` matches the shortest quoted string.
    - `\b\w+?\b` matches the shortest possible word.

- **`+?`**: Matches 1 or more occurrences, but as few as possible.
  - **Examples**:
    - `a+?` matches "a" in "aaa" as few times as possible.
    - `".+?"` matches the shortest quoted string within quotes.
    - `\d+?` matches the smallest possible number.

### 3.3 Backreferences

- **`\1, \2, ...`**: Refers to previously captured groups.
  - **Examples**:
    - `(\b\w+\b) \1` matches repeated words like "hello hello".
    - `(\d{3})-\1` matches repeated three-digit sequences like "123-123".
    - `"(.)\1"` matches a character followed by itself, like "aa" or "bb".

## 4. Practical Examples

### 4.1 Validating an Email Address

```regex
^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}$
```
- **Examples**:
  - Matches: `"user@example.com"`
  - Matches: `"user.name@sub.domain.com"`
  - Does NOT match: `"user@domain"` (no top-level domain)

### 4.2 Finding a Specific Word in a Text

```regex
\bword\b
```
- **Examples**:
  - Matches: `"This is a word in a sentence"`
  - Does NOT match: `"sword"` or `"wording"`
  - Matches: `"word!"` if the word is followed by punctuation

### 4.3 Matching Phone Numbers

```regex
\(?\d{3}\)?[-.\s]?\d{3}[-.\s]?\d{4}
```
- **Examples**:
  - Matches: `"(123) 456-7890"`
  - Matches: `"123-456-7890"`
  - Matches: `"123 456 7890"`

### 4.4 Extracting Data from a Log File

```regex
ERROR: (.*)
```
- **Examples**:
  - Captures: `"An error occurred"` from `"ERROR: An error occurred"`
  - Captures: `"File not found"` from `"ERROR: File not found"`
  - Captures: `"Timeout error"` from `"ERROR: Timeout error"`

### 4.5 Replacing Text Patterns in Files

```bash
sed 's/\bfoo\b/bar/g' file.txt
```
- **Examples**:
  - Replaces: `"foo"` with `"bar"` in the text `"foo bar baz"`
  - Does NOT replace: `"food"` or `"fool"`
  - Replaces: `"foo"` in `"foo, bar, and baz"` but not in `"foosball"`

### 4.6 Matching HTML Tags

```regex
<([a-z]+)([^<]+)*(?:>(.*)<\/\1>|\s+\/>)
```
- **Examples**:
  - Matches: `"<div>Content</div>"` and captures `"div"` and `"Content"`
  - Matches: `"<img src='image.jpg' />"` and captures `"img"`
  - Matches: `"<a href='link'>Link</a>"` and captures `"a"` and `"Link"`

### 4.7 Splitting a CSV File

```regex
[^,]+
```
- **Examples**:
  - Matches: `"field1"` in `"field1,field2,field3"`
  - Matches: `"field2"` in `"field1,field2,field3"`
  - Matches: `"field3"` in `"field1,field2,field3"`

### 4.8 Password Validation

```regex
^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$
```
- **Examples**:
  - Matches: `"Password1!"`
  - Does NOT match: `"password"` (no uppercase letter or digit)
  - Matches: `"SecurePass123$"`

### 4.9 Matching Dates

```regex
^(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])/\d{4}$
```
- **Examples**:
  - Matches: `"12/25/2020"`
  - Does NOT match: `"13/25/2020"` (invalid month)
  - Matches: `"01/01/2021"`

### 4.10 Removing Duplicates

```regex
\b(\w+)\b(?:.*\b\1\b)+
```
- **Examples**:
  - Matches: `"hello hello"` in the sentence `"This is hello hello"`
  - Matches: `"world"` in `"hello world world"`
  - Does NOT match: `"hello world"` (no duplicates)

### 4.11 Extracting URLs from Text

```regex
https?:\/\/[^\s]+
```
- **Examples**:
  - Matches: `"https://www.example.com"`
  - Matches: `"http://example.com/page"`
  - Does NOT match: `"www.example.com"` (missing protocol)

### 4.12 Matching IP Addresses

```regex
\b(?:\d{1,3}\.){3}\d{1,3}\b
```
- **Examples**:
  - Matches: `"192.168.1.1"`
  - Matches: `"8.8.8.8"`
  - Does NOT match: `"999.999.999.999"` (out of valid IP range)

## 5. Regular Expressions in Different Tools

### 5.1 Using Regex with `grep`

```bash
grep -E "regex" file.txt
```
- **Examples**:
  - `grep -E "^Hello" file.txt` finds lines starting with `"Hello"`
  - `grep -E "\bword\b" file.txt` finds exact matches of the word `"word"`
  - `grep -E "ERROR:.*" logfile.txt` extracts lines containing `"ERROR:"`

### 5.2 Using Regex with `sed`

```bash
sed -E 's/regex/replacement/g' file.txt
```
- **Examples**:
  - `sed -E 's/\bfoo\b/bar/g' file.txt` replaces `"foo"` with `"bar"`
  - `sed -E 's/[0-9]{3}-[0-9]{4}/****/g' file.txt` masks phone numbers
  - `sed -E '/ERROR:/d' logfile.txt` deletes lines containing `"ERROR:"`

### 5.3 Using Regex with `awk`

```bash
awk '/regex/ { action }' file.txt
```
- **Examples**:
  - `awk '/^Hello/ { print $0 }' file.txt` prints lines starting with `"Hello"`
  - `awk '/[0-9]{4}/ { print $0 }' file.txt` prints lines containing four-digit numbers
  - `awk '/ERROR/ { print $1 }' logfile.txt` prints the first column of lines containing `"ERROR"`
  
## 6. Testing Your Regular Expressions

When working with regular expressions, it's often helpful to test your patterns before applying them to actual files. Here are some methods to quickly test your regex patterns.

### 6.1 Using `echo` with `grep`

You can test your regular expressions by piping a string to `grep` using the `echo` command. This is particularly useful for quick checks.

- **Example: Testing an Email Pattern**

  ```bash
  echo "user@example.com" | grep -E "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}$"
  ```

  If the pattern matches, `grep` will output the string. If it doesn’t match, there will be no output.

- **Example: Testing a Phone Number Pattern**

  ```bash
  echo "(123) 456-7890" | grep -E "\(?[0-9]{3}\)?[-.\s]?[0-9]{3}[-.\s]?[0-9]{4}"
  ```

### 6.2 Using `pcregrep` for Advanced Patterns

For more complex regular expressions, especially those involving Perl-compatible features like lookaheads and lookbehinds, `pcregrep` is a better option.

- **Example 1: Testing Positive Lookahead**

  Use `pcregrep` to find instances where "foo" is followed by "bar" in the string.

  ```bash
  echo "foobar" | pcregrep "foo(?=bar)"
  ```

  This command will print `foobar` because "foo" is followed by "bar".

- **Example 2: Testing Negative Lookahead**

  Use `pcregrep` to find instances where "foo" is not followed by "baz".

  ```bash
  echo "foobar" | pcregrep "foo(?!baz)"
  ```

  This will print `foobar` because "foo" is not followed by "baz".

- **Example 3: Testing Positive Lookbehind**

  Use `pcregrep` to find instances where "bar" is preceded by "foo".

  ```bash
  echo "foobar" | pcregrep "(?<=foo)bar"
  ```

  This will print `bar` because it is preceded by "foo".

- **Example 4: Testing Negative Lookbehind**

  Use `pcregrep` to find instances where "bar" is not preceded by "baz".

  ```bash
  echo "foobar" | pcregrep "(?<!baz)bar"
  ```

  This will print `bar` because it is not preceded by "baz".

- **Example 5: Using Non-Greedy Matching**

  Use `pcregrep` to match the shortest possible sequence between "foo" and "bar".

  ```bash
  echo "foo123barfoo456bar" | pcregrep "foo.*?bar"
  ```

  This will print `foo123bar` because it matches the shortest sequence between "foo" and "bar".

- **Example 6: Matching Multiline Patterns**

  Use `pcregrep` with the `-M` flag to match patterns that span multiple lines.

  ```bash
  echo -e "foo\nbar" | pcregrep -M "foo.*bar"
  ```
  
  This will print the entire string, as the `-M` flag allows matching across newline characters.

### 7. Conclusion

Testing your regular expressions before applying them is a crucial step in ensuring they work as intended. By using tools like `grep` and `pcregrep` with `echo`, you can quickly validate your patterns in a controlled environment.
