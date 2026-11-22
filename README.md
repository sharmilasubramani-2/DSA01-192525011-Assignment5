# DSA0111 OOPS - Assignment 5

## Reliable Software with Runtime Polymorphism and Exceptions

### Student Details
- Register Number: 192525011
- Course Code: DSA0111
- Language: C++
- Standard: C++17
- Compiler: GCC MSYS2 UCRT64

## Assignment Overview

This assignment implements a hospital billing and insurance claim management system using object-oriented programming.

## Part A - Design and Implementation

| Section | Topic |
|---|---|
| A1 | Bill Hierarchy |
| A2 | Runtime Polymorphism |
| A3 | Payer Polymorphism |
| A4 | Exception Handling |
| A5 | Exception Recovery and RAII |

## Part B - Practical Implementation

| Section | Topic |
|---|---|
| B1 | Billing Validation |
| B2 | Error Conditions |
| B3 | Performance Comparison |
| B4 | Final Engineering Decision |

## Repository Structure

- A1-Bill-Hierarchy
- A2-Runtime-Polymorphism
- A3-Payer-Polymorphism
- A4-Exception-Handling
- A5-Exception-Recovery
- B1-Billing-Validation
- B2-Error-Conditions
- B3-Performance-Comparison
- B4-Final-Engineering-Decision

## Compilation

Run the following commands from the relevant task directory:

    g++ -std=c++17 -Wall -Wextra main.cpp -o main.exe

    .\main.exe

For B3 performance benchmarking, compile with -O2.

## Performance Results

Refer to B3-Performance-Comparison/benchmark-results.md.

## Engineering Decision

Refer to B4-Final-Engineering-Decision/engineering-decision.md.

## Testing Limitation

AddressSanitizer compilation was attempted, but the installed toolchain could not locate the required libasan runtime. Sanitizer execution remains pending.

## GitHub Repository

https://github.com/sharmilasubramani-2/DSA01-192525011-Assignment5
