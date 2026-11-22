# DSA0111 OOPS - Assignment 5

## Reliable Software with Runtime Polymorphism and Exceptions

### Student Details
- Register Number: 192525011
- Course Code: DSA0111
- Language: C++
- Standard: C++17
- Compiler: GCC MSYS2 UCRT64

## Assignment Overview

Implementation of a hospital billing and insurance claim management system using object-oriented programming, runtime polymorphism and exception handling.

## Part A - Design and Theoretical Analysis

| Section | Topic |
|---|---|
| A1 | Bill Hierarchy and Object-Oriented Design |
| A2 | Runtime Polymorphism |
| A3 | Payer Polymorphism |
| A4 | Exception Handling |
| A5 | Exception Recovery and RAII |

Report: [Part A Design and Analysis](Report/Part-A-Design-Analysis.md)

## Part B - Implementation and Testing

| Section | Topic |
|---|---|
| B1 | Billing Validation |
| B2 | Error Conditions |
| B3 | Performance Comparison |
| B4 | Final Engineering Decision |

Report: [Part B Implementation and Analysis](Report/Part-B-Implementation-Analysis.md)

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
- Report

Each task folder contains its implementation source and execution screenshot. B3 also includes benchmark results and correctness comparison. B4 includes the engineering decision document.

## Compilation

Run commands from the relevant task directory:

```powershell
g++ -std=c++17 -Wall -Wextra main.cpp -o main.exe
.\main.exe
```

For B3 performance benchmarking:

```powershell
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o main.exe
.\main.exe
```

## Performance Results

See [B3 Benchmark Results](B3-Performance-Comparison/benchmark-results.md).

## Engineering Decision

See [B4 Engineering Decision](B4-Final-Engineering-Decision/engineering-decision.md).

## Verification Limitations

AddressSanitizer compilation was attempted, but the installed toolchain could not locate the required libasan runtime. Sanitizer execution remains unverified. The virtual-function removal experiment, virtual-destructor sanitizer experiment and separate optional-versus-exception benchmark remain pending.

## GitHub Repository

https://github.com/sharmilasubramani-2/DSA01-192525011-Assignment5

## Additional Experiments

- B1: design-experiments.cpp compares non-virtual dispatch, virtual destructor properties and exception rethrowing.
- B2: optional-vs-exception.cpp benchmarks validation strategies at different invalid-input rates.
