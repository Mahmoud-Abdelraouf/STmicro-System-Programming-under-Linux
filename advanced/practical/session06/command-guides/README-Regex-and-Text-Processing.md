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
     - 5.1.1 [Using `grep -E`](#511-using-grep--e)
     - 5.1.2 [Using `grep -vE`](#512-using-grep--ve)
   - 5.2 [Using Regex with `sed`](#52-using-regex-with-sed)
   - 5.3 [Using Regex with `awk`](#53-using-regex-with-awk)
     - 5.3.1 [Introduction to `awk`](#531-introduction-to-awk)
     - 5.3.2 [Using `awk` with Regular Expressions](#532-using-awk-with-regular-expressions)
     - 5.3.3 [Examples of `awk` with Regex](#533-examples-of-awk-with-regex)
   - 5.4 [Using Regex in Programming Languages](#54-using-regex-in-programming-languages)
     - 5.4.1 [Regex in Python](#541-regex-in-python)
     - 5.4.2 [Regex in JavaScript](#542-regex-in-javascript)
     - 5.4.3 [Regex in Java](#543-regex-in-java)
     - 5.4.4 [Regex in C#](#544-regex-in-csharp)
     - 5.4.5 [Regex in PHP](#545-regex-in-php)
     - 5.4.6 [Regex in C and C++](#546-regex-in-c-and-c++)
6. [Conclusion](#6-conclusion)

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

- **Negative Lookahead `(?!...)`**:

Asserts that a certain pattern must not follow.

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
^[\w\.-]+@[a-zA-Z\d\.-]+\.[a-zA-Z]{2,6}$
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

The `grep` command in Linux is used to search for patterns within files. When combined with regular expressions, `grep` becomes a powerful tool for text searching.

#### 5.1.1 Using `grep -E`

The `-E` option in `grep` enables extended regular expressions, allowing for more complex patterns.

- **Examples**:

  - **Example 1**: Finding lines that start with "Error" or "Warning" in a log file:

    ```bash
    grep -E "^(Error|Warning)" logfile.txt
    ```

    - This command finds lines in `logfile.txt` that start with either "Error" or "Warning".

  - **Example 2**: Finding lines that contain a valid email address:

    ```bash
    grep -E "[\w\.-]+@[a-zA-Z\d\.-]+\.[a-zA-Z]{2,6}" emails.txt
    ```

    - This command searches for lines in `emails.txt` that contain a valid email address.

  - **Example 3**: Finding lines with three or more consecutive vowels:
    ```bash
    grep -E "[aeiou]{3,}" text.txt
    ```
    - This command finds lines in `text.txt` that contain three or more consecutive vowels.

#### 5.1.2 Using `grep -vE`

The `-vE` option in `grep` combines `-v` (which inverts the match, showing lines that do not match the pattern) with `-E` for extended regular expressions.

- **Examples**:

  - **Example 1**: Excluding lines that start with a comment (e.g., lines that start with `#`) from a configuration file:

    ```bash
    grep -vE "^#" config.conf
    ```

    - This command displays all lines in `config.conf` that do not start with a `#`.

  - **Example 2**: Excluding lines that contain a specific word, such as "Error":

    ```bash
    grep
    ```

  -vE "Error" logfile.txt

  ````

  - This command displays all lines in `logfile.txt` that do not contain the word "Error".

  - **Example 3**: Excluding lines that contain any numbers:
  ```bash
  grep -vE "[0-9]" data.txt
  ````

  - This command displays all lines in `data.txt` that do not contain any numbers.

### 5.2 Using Regex with `sed`

```bash
sed -E 's/regex/replacement/g' file.txt
```

- **Examples**:
  - `sed -E 's/\bfoo\b/bar/g' file.txt` replaces `"foo"` with `"bar"`
  - `sed -E 's/[0-9]{3}-[0-9]{4}/****/g' file.txt` masks phone numbers
  - `sed -E '/ERROR:/d' logfile.txt` deletes lines containing `"ERROR:"`

### 5.3 Using Regex with `awk`

#### 5.3.1 Introduction to `awk`

`awk` is a powerful text processing language that is used to manipulate data and generate reports. It scans each line of a file, checks if it matches a pattern, and then performs a specified action on the matched lines.

- **Basic Syntax**:
  ```bash
  awk '/pattern/ { action }' file.txt
  ```
  - `/pattern/` is the regular expression that `awk` matches against each line.
  - `{ action }` is the command that `awk` executes for each line that matches the pattern.

#### 5.3.2 Using `awk` with Regular Expressions

Regular expressions in `awk` can be used to search for patterns within text files. This can be combined with `awk`'s ability to manipulate and format data, making it a versatile tool for text processing.

#### 5.3.3 Examples of `awk` with Regex

- **Example 1: Printing lines that start with a specific word**

  ```bash
  awk '/^Hello/ { print $0 }' file.txt
  ```

  - **Explanation**: This command prints lines from `file.txt` that start with the word "Hello". The `^` anchor ensures that only lines starting with "Hello" are matched.

- **Example 2: Printing lines that contain four-digit numbers**

  ```bash
  awk '/[0-9]{4}/ { print $0 }' file.txt
  ```

  - **Explanation**: This command prints lines from `file.txt` that contain any four-digit number. The regex `[0-9]{4}` matches any sequence of four consecutive digits.

- **Example 3: Printing the first column of lines that contain the word "ERROR"**

  ```bash
  awk '/ERROR/ { print $1 }' logfile.txt
  ```

  - **Explanation**: This command searches for lines containing the word "ERROR" in `logfile.txt` and prints the first field (column) of each matching line. By default, `awk` splits lines into fields based on whitespace.

- **Example 4: Summing numbers in lines that match a pattern**

  ```bash
  awk '/^Total/ { sum += $2 } END { print sum }' file.txt
  ```

  - **Explanation**: This command sums the values in the second field (`$2`) of lines that start with "Total" and prints the total sum at the end. The `END` block is executed after all lines have been processed.

- **Example 5: Filtering and formatting output**

  ```bash
  awk '/^[A-Z]/ { printf "Name: %s\n", $1 }' names.txt
  ```

  - **Explanation**: This command finds lines in `names.txt` that start with an uppercase letter and prints them with the prefix "Name: ". The `printf` function is used to format the output.

- **Example 6: Replacing text in lines that match a pattern**

  ```bash
  awk '/apple/ { gsub("apple", "orange"); print }' fruits.txt
  ```

  - **Explanation**: This command replaces all instances of "apple" with "orange" in lines that contain "apple" and prints the modified lines. The `gsub` function performs a global substitution.

- **Example 7: Counting lines that match a pattern**

  ```bash
  awk '/^Error/ { count++ } END { print count }' logfile.txt
  ```

  - **Explanation**: This command counts the number of lines in `logfile.txt` that start with "Error" and prints the count at the end.

- **Example 8: Extracting specific fields based on a pattern**
  ```bash
  awk '/^User/ { print $2, $3 }' users.txt
  ```
  - **Explanation**: This command extracts and prints the second and third fields from lines in `users.txt` that start with "User".

---

### 5.4 Using Regex in Programming Languages

Regular expressions are widely used in various programming languages for string matching and manipulation. Below are examples of how to use regex in some of the most popular languages.

#### 5.4.1 Regex in Python

Python provides the `re` module to work with regular expressions.

- **Example 1: Finding all matches in a string**

  ```python
  import re

  text = "The rain in Spain stays mainly in the plain."
  matches = re.findall(r'\bin\b', text)
  print(matches)
  ```

  - **Explanation**: This script finds all occurrences of the word "in" in the `text` variable.

- **Example 2: Replacing text using regex**

  ```python
  import re

  text = "The rain in Spain."
  new_text = re.sub(r'Spain', 'France', text)
  print(new_text)
  ```

  - **Explanation**: This script replaces "Spain" with "France" in the `text` variable.

- **Example 3: Validating an email address**

  ```python
  import re

  email = "user@example.com"
  if re.match(r'^[\w\.-]+@[a-zA-Z\d\.-]+\.[a-zA-Z]{2,6}$', email):
      print("Valid email")
  else:
      print("Invalid email")
  ```

  - **Explanation**: This script checks if the `email` variable is a valid email address.

#### 5.4.2 Regex in JavaScript

In JavaScript, regex is implemented using the `RegExp` object or the shorthand `/pattern/` syntax.

- **Example 1: Testing if a string contains a pattern**

  ```javascript
  let text = "Hello, world!";
  let regex = /world/;
  console.log(regex.test(text)); // Output: true
  ```

  - **Explanation**: This script tests if the string `text` contains the word "world".

- **Example 2: Replacing text using regex**

  ```javascript
  let text = "Hello, world!";
  let newText = text.replace(/world/, "JavaScript");
  console.log(newText); // Output: Hello, JavaScript!
  ```

  - **Explanation**: This script replaces "world" with "JavaScript" in the `text` string.

- **Example 3: Extracting all numbers from a string**
  ```javascript
  let text = "My phone number is 123-456-7890.";
  let numbers = text.match(/\d+/g);
  console.log(numbers); // Output: ["123", "456", "7890"]
  ```
  - **Explanation**: This script extracts all sequences of digits from the `text` string.

#### 5.4.3 Regex in Java

Java provides the `Pattern` and `Matcher` classes for working with regular expressions.

- **Example 1: Finding all matches in a string**

  ```java
  import java.util.regex.*;

  public class Main {
      public static void main(String[] args) {
          String text = "The rain in Spain stays mainly in the plain.";
          Pattern pattern = Pattern.compile("\\bin\\b");
          Matcher matcher = pattern.matcher(text);
          while (matcher.find()) {
              System.out.println("Found: " + matcher.group());
          }
      }
  }
  ```

  - **Explanation**: This script finds all occurrences of the word "in" in the `text` variable.

- **Example 2: Replacing text using regex**

  ```java
  import java.util.regex.*;

  public class Main {
      public static void main(String[] args) {
          String text = "The rain in Spain.";
          String newText = text.replaceAll("Spain", "France");
          System.out.println(newText);  // Output: The rain in France.
      }
  }
  ```

  - **Explanation**: This script replaces "Spain" with "France" in the `text` variable.

- **Example 3: Validating an email address**

  ```java
  import java.util.regex.*;

  public class Main {
      public static void main(String[] args) {
          String email = "user@example.com";
          if (email.matches("^[\\w\\.-]+@[a-zA-Z\\d\\.-]+\\.[a-zA-Z]{2,6}$")) {
              System.out.println("Valid email");
          } else {
              System.out.println("Invalid email");
          }
      }
  }
  ```

  - **Explanation**: This script checks if the `email` variable is a valid email address.

#### 5.4

.4 Regex in C#

In C#, regular expressions are handled by the `System.Text.RegularExpressions` namespace.

- **Example 1: Finding all matches in a string**

  ```csharp
  using System;
  using System.Text.RegularExpressions;

  class Program {
      static void Main() {
          string text = "The rain in Spain stays mainly in the plain.";
          MatchCollection matches = Regex.Matches(text, @"\bin\b");
          foreach (Match match in matches) {
              Console.WriteLine("Found: " + match.Value);
          }
      }
  }
  ```

  - **Explanation**: This script finds all occurrences of the word "in" in the `text` variable.

- **Example 2: Replacing text using regex**

  ```csharp
  using System;
  using System.Text.RegularExpressions;

  class Program {
      static void Main() {
          string text = "The rain in Spain.";
          string newText = Regex.Replace(text, "Spain", "France");
          Console.WriteLine(newText);  // Output: The rain in France.
      }
  }
  ```

  - **Explanation**: This script replaces "Spain" with "France" in the `text` variable.

- **Example 3: Validating an email address**

  ```csharp
  using System;
  using System.Text.RegularExpressions;

  class Program {
      static void Main() {
          string email = "user@example.com";
          if (Regex.IsMatch(email, @"^[\w\.-]+@[a-zA-Z\d\.-]+\.[a-zA-Z]{2,6}$")) {
              Console.WriteLine("Valid email");
          } else {
              Console.WriteLine("Invalid email");
          }
      }
  }
  ```

  - **Explanation**: This script checks if the `email` variable is a valid email address.

#### 5.4.5 Regex in PHP

In PHP, regular expressions can be used with functions like `preg_match`, `preg_replace`, and `preg_match_all`.

- **Example 1: Finding all matches in a string**

  ```php
  <?php
  $text = "The rain in Spain stays mainly in the plain.";
  preg_match_all('/\bin\b/', $text, $matches);
  print_r($matches);
  ?>
  ```

  - **Explanation**: This script finds all occurrences of the word "in" in the `$text` variable.

- **Example 2: Replacing text using regex**

  ```php
  <?php
  $text = "The rain in Spain.";
  $newText = preg_replace('/Spain/', 'France', $text);
  echo $newText;  // Output: The rain in France.
  ?>
  ```

  - **Explanation**: This script replaces "Spain" with "France" in the `$text` variable.

- **Example 3: Validating an email address**

  ```php
  <?php
  $email = "user@example.com";
  if (preg_match('/^[\w\.-]+@[a-zA-Z\d\.-]+\.[a-zA-Z]{2,6}$/', $email)) {
      echo "Valid email";
  } else {
      echo "Invalid email";
  }
  ?>
  ```

  - **Explanation**: This script checks if the `$email` variable is a valid email address.

#### 5.4.6 Regex in C and C++

In C and C++, regular expressions are supported through libraries like `<regex.h>` in C and `<regex>` in C++.

##### C: Using `<regex.h>`

In C, regular expressions are typically used with the `<regex.h>` library.

- **Example 1: Matching a pattern in a string**

  ```c
  #include <stdio.h>
  #include <regex.h>

  int main() {
      regex_t regex;
      int result;
      char *pattern = "^[a-z]+@[a-z]+\\.[a-z]{2,3}$";
      char *text = "user@example.com";

      // Compile the regular expression
      result = regcomp(&regex, pattern, REG_EXTENDED);
      if (result) {
          printf("Could not compile regex\n");
          return 1;
      }

      // Execute regular expression
      result = regexec(&regex, text, 0, NULL, 0);
      if (!result) {
          printf("Match\n");
      } else if (result == REG_NOMATCH) {
          printf("No match\n");
      } else {
          printf("Regex match failed\n");
      }

      // Free compiled regular expression
      regfree(&regex);
      return 0;
  }
  ```

  - **Explanation**: This C program checks if the `text` matches the email pattern. It prints "Match" if the pattern is found.

##### C++: Using `<regex>`

C++ provides a more modern and easier-to-use regular expression library through `<regex>`.

- **Example 1: Matching a pattern in a string**

  ```cpp
  #include <iostream>
  #include <regex>

  int main() {
      std::string text = "user@example.com";
      std::regex pattern(R"(^[a-z]+@[a-z]+\.[a-z]{2,3}$)");

      if (std::regex_match(text, pattern)) {
          std::cout << "Match" << std::endl;
      } else {
          std::cout << "No match" << std::endl;
      }

      return 0;
  }
  ```

  - **Explanation**: This C++ program checks if the `text` matches the email pattern. It prints "Match" if the pattern is found.

- **Example 2: Finding and replacing text**

  ```cpp
  #include <iostream>
  #include <regex>

  int main() {
      std::string text = "The rain in Spain.";
      std::regex pattern("Spain");
      std::string replaced = std::regex_replace(text, pattern, "France");

      std::cout << replaced << std::endl;  // Output: The rain in France.

      return 0;
  }
  ```

  - **Explanation**: This C++ program replaces "Spain" with "France" in the `text` string.

- **Example 3: Finding all matches of a pattern**

  ```cpp
  #include <iostream>
  #include <regex>

  int main() {
      std::string text = "The rain in Spain stays mainly in the plain.";
      std::regex pattern(R"(\bin\b)");
      std::smatch matches;

      if (std::regex_search(text, matches, pattern)) {
          for (auto match : matches) {
              std::cout << "Found: " << match << std::endl;
          }
      }

      return 0;
  }
  ```

  - **Explanation**: This C++ program finds and prints all occurrences of the word "in" in the `text` string.

---

## 6. Conclusion

This comprehensive guide provides an in-depth look at how to use regular expressions (regex) in Linux, covering basic syntax, advanced features, and practical examples in different tools and programming languages, including C and C++. Mastering regex will significantly enhance your ability to work with text and data across various environments, making it an indispensable tool in your toolkit.
