# Holyc Language Keywords

## **Types**

This language is semi-interoperable and supports the following types:

| Keyword  | Equivalent |
|----------|-----------|
| `U0`     | `void`    |
| `Bool`   | `bool`    |
| `I8`     | `sbyte`   |
| `U8`     | `byte`    |
| `I16`    | `short`   |
| `U16`    | `ushort`  |
| `I32`    | `int`     |
| `U32`    | `uint`    |
| `I64`    | `long`    |
| `U64`    | `ulong`   |
| `F64`    | `double`  |

## **Control Flow Keywords**

| Keyword  | Equivalent |
|----------|-----------|
| `switch` | `match`   |
| `case`   | `case`    |
| `break`  | `break`   |
| `continue` | `continue` |
| `while`  | `while`   |
| `do`     | `do`      |
| `for`    | `for`     |
| `goto`   | `goto`    |
| `default` | `default` |
| `return` | `ret`     |

## **Preprocessor Directives**

| Keyword  | Equivalent |
|----------|-----------|
| `define`  | `#define`  |
| `ifndef`  | `#ifndef`  |
| `ifdef`   | `#ifdef`   |
| `elifdef` | `#elifdef` |
| `endif`   | `#endif`   |
| `elif`    | `#elif`    |
| `defined` | `#defined` |
| `undef`   | `#undef`   |
| `error`   | `#error`   |
| `include` | `#include` or `use` |

## **Modifiers & Storage Specifiers**

| Keyword  | Equivalent |
|----------|-----------|
| `cast`   | `(type)`  |
| `sizeof` | `sizeof`  |
| `inline` | `method`  |
| `atomic` | `lock`    |
| `volatile` | `volatile` |
| `public`  | `pub`     |
| `private` | `priv`    |
| `class`   | `class`   |
| `union`   | `struct`  |
| `static`  | `static`  |

## **External & Assembly Keywords**

| Keyword  | Equivalent |
|----------|-----------|
| `_extern` | `extern`  |
| `extern`  | `extern`  |
| `asm`     | `asm`     |

---

### **Notes:**
- **`match` replaces `switch`**, similar to Rust's match.
- **`ret` replaces `return`** for a more concise syntax.
- **`use` is an alternative to `#include`**, inspired by modern languages.
- **`lock` is used for atomic operations** instead of `atomic` in C#.
- **C#-like struct is used instead of `union`** for safety.

This document provides an overview of the core keywords and their equivalents in Holyc Language, making it more readable and C#-like while maintaining interoperability.

