# B3 - Performance Comparison

## Benchmark Configuration

- Language: C++
- Standard: C++17
- Optimization: -O2
- Compiler flags: -Wall -Wextra
- Validation operations: 1,000,000
- Variant benchmark operations: 10,000,000

## 1. Runtime Polymorphism

| Operations | Execution Time |
|---:|---:|
| 1,000 | 0.002 ms |
| 1,000,000 | 1.582 ms |
| 10,000,000 | 15.743 ms |

## 2. Runtime Polymorphism vs Variant

| Approach | Operations | Execution Time |
|---|---:|---:|
| Virtual dispatch | 10,000,000 | 15.743 ms |
| std::variant and std::visit | 10,000,000 | 15.486 ms |

## 3. Return Codes vs Exceptions

| Invalid Input Rate | Return Code (ms) | Exceptions (ms) |
|---:|---:|---:|
| 0% | 1.540 | 1.509 |
| 1% | 1.746 | 32.390 |
| 50% | 1.018 | 1385.375 |

## 4. Analysis

The runtime polymorphism benchmark shows increasing execution time as the number of operations increases.

The measured execution times of virtual dispatch and std::variant visitation are close. The difference in this single run is too small to establish a universal performance advantage.

At a 0% invalid input rate, both validation approaches have similar execution times.

At a 1% invalid input rate, exception-based validation takes considerably longer than return-code validation.

At a 50% invalid input rate, exception-based validation becomes substantially more expensive because exceptions are repeatedly thrown and caught.

Return-code validation is therefore preferable for frequent and expected validation failures. Exceptions remain useful for exceptional conditions that should interrupt normal program execution.

## 5. Benchmark Limitations

These measurements represent one execution on the local computer.

They are microbenchmark results and may vary with processor load, compiler optimizations, hardware, and runtime conditions.

The polymorphism benchmark reuses two bill objects to focus on dispatch overhead rather than repeated memory allocation.

Additional repeated runs and warm-up measurements would improve statistical reliability.

