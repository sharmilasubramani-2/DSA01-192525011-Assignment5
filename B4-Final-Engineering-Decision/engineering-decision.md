# B4 - Final Engineering Decision

## 1. Implementation Summary

The billing system was extended with a new EmergencyBill class and a new CorporatePayer class.

Both extensions were implemented without modifying the existing OPBill, IPBill, SelfPay, Insurance, and GovernmentScheme classes.

The implementation uses abstract base classes, inheritance, virtual functions, and runtime polymorphism.

## 2. Extension Verification

### New Bill Type

| Bill Type | Patient | Amount |
|---|---|---:|
| Outpatient | Ravi | 1700.00 |
| Inpatient | Meena | 47500.00 |
| Emergency | Arun | 20000.00 |
| Grand Total | | 69200.00 |

### New Payer Type

| Payer | Coverage Amount | Patient Payment |
|---|---:|---:|
| Self Pay | 0.00 | 20000.00 |
| Insurance | 16000.00 | 4000.00 |
| Government Scheme | 15000.00 | 5000.00 |
| Corporate Health Plan | 18000.00 | 2000.00 |

All four payer implementations successfully processed the new EmergencyBill type.

## 3. Exception Safety

The emergency claim processing function uses an automatic resource-management object.

A simulated exception was thrown during claim processing. The resource destructor executed during stack unwinding, releasing the database resource before the exception was handled.

Observed output:

- Emergency Claim Database acquired.
- Claim processing started.
- Emergency Claim Database released.
- Exception handled successfully.

This demonstrates RAII-based resource management and exception safety.

## 4. Production Scenario

Assumptions:

- 15 hospitals.
- 200,000 bills per hospital per day.
- New bill types and payer categories introduced annually.

Total daily billing volume:

15 x 200,000 = 3,000,000 bills per day.

The system must support high transaction volume, maintainability, reliable exception handling, and future extensions.

## 5. Recommended Architecture

A modular object-oriented architecture using abstract Bill and Payer interfaces is recommended.

Reasons:

1. New bill types can be introduced through derived classes.
2. New payer policies can be added through implementations of the Payer interface.
3. Runtime polymorphism allows common billing operations without extensive conditional statements.
4. Smart pointers and RAII support automatic resource management.
5. Independent modules make testing and maintenance easier.

For production deployment, the system should additionally use database transactions, input validation, structured logging, concurrency control, monitoring, authentication, authorization, and automated testing.

## 6. Class-Based Extensions vs Plugins

### Class-Based Architecture

Advantages:
- Simple integration with the existing application.
- Strong compile-time type checking.
- Easier debugging and testing.
- Suitable when extensions are developed and deployed together.

Limitations:
- New classes generally require rebuilding and redeploying the application.
- Independent third-party extensions are harder to deploy.

### Plugin-Based Architecture

Advantages:
- Extensions can be deployed independently.
- External payer integrations can be isolated.
- Suitable when multiple organizations develop separate integrations.

Limitations:
- More complex version management.
- Requires a stable plugin interface.
- Additional security and compatibility testing is necessary.

### Final Decision

Use a modular class-based architecture as the core billing system.

Introduce a controlled plugin interface for external payer integrations only when independent deployment becomes a genuine requirement.

This hybrid approach balances maintainability, extensibility, reliability, and operational complexity.

## 7. Final Conclusion

The B4 implementation demonstrates that new bill and payer types can be added without modifying existing implementations.

The architecture supports extension through interfaces and runtime polymorphism. RAII ensures automatic resource cleanup when exceptions occur.

For a production environment processing three million bills daily, the design should be supported by performance testing, secure database transactions, monitoring, and automated regression testing.

## 8. AddressSanitizer Verification

AddressSanitizer compilation was attempted using:

g++ -std=c++17 -g -O1 -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer main.cpp -o main_asan.exe

The linker reported that the AddressSanitizer runtime library (-lasan) could not be found.

Therefore, AddressSanitizer execution could not be completed with the currently installed toolchain.

This is recorded as an environment limitation, not as a successful sanitizer test. The normal compilation and exception-cleanup execution completed successfully.

A complete sanitizer verification requires installing a compatible AddressSanitizer runtime or using a supported compiler environment.
