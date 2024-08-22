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
7. [Applying `sed` Examples to a Sample File](#7-applying-sed-examples-to-a-sample-file)
8. [Conclusion](#8-conclusion)

---



