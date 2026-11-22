# Part B – Implementation, Testing and Performance Analysis

## Assignment 5 – DSA0111 OOPS
Register Number: 192525011

# B1 – Billing Validation

## Implementation

The billing system uses an abstract Bill class with OPBill and IPBill implementations. An abstract Payer class supports SelfPay, Insurance and GovernmentScheme.

## Test Results

OP Ravi: 1700.00
IP Meena: 47500.00
Total Bill Amount: 49200.00

Insurance coverage: OP 1360.00; IP 24000.00.
Government coverage: OP 1275.00; IP 35625.00.
All implemented billing validation tests passed.

The implementation demonstrates runtime polymorphism and separates bill calculation from payer coverage policies.

# B2 – Error Conditions

## Implemented Error Tests

- Negative billing charges.
- Insurance claim exceeding the coverage limit.
- Unknown medical package.
- Invalid numeric input.
- Simulated memory allocation failure using std::bad_alloc.
- Exception propagation, logging and resource cleanup.

## Observed Results

All implemented error validation tests completed successfully. The simulated bad_alloc demonstrates exception handling; it does not represent actual system memory exhaustion.

The implementation demonstrates custom exceptions and resource cleanup during exception propagation.

## Exception Handling Analysis

Using throw; preserves the currently handled exception when rethrowing. Using throw e can copy or move the exception and may cause slicing when the caught object is referenced through a base class.

Return codes are generally more suitable for frequent expected validation failures. Exceptions are useful for exceptional error conditions.

# B3 – Performance Comparison

## Correctness Comparison

Ten bills were evaluated using runtime polymorphism and std::variant with std::visit. Both approaches produced matching totals.

Polymorphic Grand Total: 291500.00
Variant Grand Total: 291500.00

All ten correctness comparisons passed.

## Runtime Polymorphism Benchmark

| Operations | Measured Time |
|---|---:|
| 1,000 | 0.002 ms |
| 1,000,000 | 1.582 ms |
| 10,000,000 | 15.743 ms |

## Variant Benchmark

10,000,000 operations: 15.486 ms.

The measured difference between the two approaches was small in this run. Repeated trials and controlled benchmarking would be required before making a general performance conclusion.

## Return Codes vs Exceptions

| Invalid Input Rate | Return Codes | Exceptions |
|---|---:|---:|
| 0% | 1.540 ms | 1.509 ms |
| 1% | 1.746 ms | 32.390 ms |
| 50% | 1.018 ms | 1385.375 ms |

The results show that exception-based validation becomes significantly more expensive when invalid inputs are frequent. Return-code validation is preferable for routine validation failures in this benchmark.

# B4 – Final Engineering Decision

## System Extension

An EmergencyBill class was added without modifying the existing OPBill and IPBill classes. A CorporatePayer class was added without modifying the existing payer implementations.

## Extension Test Results

Emergency Bill: 20000.00
Insurance coverage: 16000.00
Government coverage: 15000.00
Corporate coverage: 18000.00

The emergency claim test also demonstrated exception handling and automatic resource cleanup.

## Production Design Decision

For a system serving 15 hospitals and processing 200000 bills per hospital per day, the estimated total is 3000000 bills per day.

An inheritance-based design provides clear interfaces for bill and payer types. RAII and smart pointers support safe resource management. A hybrid plugin architecture may be considered if payer rules need independent deployment or frequent updates.

## Verification Limitations

AddressSanitizer execution could not be completed because the installed MinGW toolchain could not find the libasan library. Therefore, sanitizer-clean execution has not been verified.

The virtual-function removal experiment, virtual-destructor sanitizer experiment, and separate optional-versus-exception benchmark have not been documented as completed. These must not be treated as passed tests.

# Overall Conclusion

The implemented billing system demonstrates inheritance, runtime polymorphism, payer abstraction, custom exception handling, RAII, correctness comparison and performance measurement. The recorded results support the use of polymorphism for extensible billing and return-code validation for frequent expected errors.
