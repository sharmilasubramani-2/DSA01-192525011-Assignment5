# Part A – Design and Theoretical Analysis

## Assignment 5 – DSA0111 OOPS
Register Number: 192525011

# A1 – Bill Hierarchy and Object-Oriented Design

## Problem Description

The hospital billing system processes outpatient and inpatient bills. An abstract Bill class provides a common interface.

## UML Representation

Bill (Abstract)
|-- OPBill
|   |-- consultation
|   |-- medicine
|-- IPBill
    |-- roomCharges
    |-- treatmentCharges

## Design Explanation

Bill is an abstract base class. OPBill and IPBill inherit from Bill and implement their own total() functions. Runtime polymorphism allows both bill types to use a common interface.

## Alternative Design

A single Bill class could use a type field and switch statement. Adding a new bill type would require modifying the switch statement. Inheritance separates bill-specific calculations and improves extensibility.

## Complexity Analysis

| Operation | Time Complexity |
|---|---|
| Calculate one bill | O(1) |
| Display one bill | O(1) |
| Process n bills | O(n) |
| Calculate grand total | O(n) |
| Store n bills | O(n) space |

Each bill requires O(1) space. Storing n bills requires O(n) space.

# A2 – Runtime Polymorphism

## Early Binding

Early binding resolves a function call at compile time. Non-virtual functions generally use early binding.

## Late Binding

Late binding resolves a virtual function call at runtime based on the actual object type. A base class pointer can invoke the overridden function of a derived class.

## VTable and Virtual Pointer

A compiler commonly implements runtime polymorphism using a virtual table (vtable). The vtable stores addresses of virtual functions. Objects with virtual functions commonly contain a hidden pointer (vptr) to the relevant vtable. These are common implementation techniques, not requirements of the C++ language standard.

## Virtual Destructor

A base class used polymorphically should have a virtual destructor. Deleting a derived object through a base class pointer without a virtual destructor causes undefined behavior.

## Dynamic Cast Alternative

Dynamic_cast can identify a derived object at runtime, but repeated type checks create additional conditional logic. Virtual functions provide a cleaner interface when behavior belongs to the object itself.

## Conclusion

Late binding supports extensible billing systems by allowing derived bill implementations to be called through base class pointers.

# A3 – Payer Polymorphism

## Abstract Payer Class

The abstract Payer class defines a common amountCovered(const Bill&) interface. Derived payer classes implement their own coverage policies.

## SelfPay

SelfPay provides no insurance coverage. The patient pays the entire bill amount.

## Insurance

Insurance applies a coverage limit and co-payment percentage. The covered amount is the smaller of the bill amount after co-payment and the remaining coverage limit.

## Government Scheme

GovernmentScheme covers a fixed percentage of the bill. The patient pays the remaining amount.

## Extensibility

A new payer such as CorporatePayer can be introduced by deriving it from Payer without changing existing payer classes.

## Alternative Design

Function pointers or std::function can represent payer calculation policies. However, an abstract class provides a structured interface and supports related payer data and behaviour.

## Conclusion

Payer polymorphism separates payment policies from bill calculation and supports adding new payer types.

# A4 – Exception Handling

## Custom Exception Hierarchy

A custom BillingError class can derive from std::runtime_error. Specific exceptions represent negative charges, claim limit violations, unknown medical packages and missing patient records.

## Error Handling

Invalid billing charges and claims are rejected before processing. Unknown packages and missing patient records generate meaningful exceptions. std::bad_alloc represents memory allocation failure.

## Throw and Catch

The throw statement signals an error. A matching catch block handles the exception. Multiple catch blocks can handle different exception types.

## Noexcept

The noexcept specifier indicates that a function is not expected to throw exceptions. If an exception escapes a noexcept function, the program terminates.

## Destructors

Destructors should not allow exceptions to escape, especially during stack unwinding. Throwing from a destructor during active exception handling can cause program termination.

## Exception Handling vs Return Codes

Return codes make error handling explicit but require callers to check results. Exceptions separate error handling from normal execution and are suitable for exceptional failures.

## Conclusion

Custom exceptions improve error identification and allow billing failures to be handled consistently.

# A5 – Exception Recovery and RAII

## Catch, Log and Rethrow

An exception can be caught in an intermediate function, logged and rethrown using throw;. A higher-level handler can then decide how to recover.

## throw; vs throw e

throw; rethrows the currently handled exception while preserving its original exception information. throw e may copy or move the exception object and can cause exception slicing.

## Stack Unwinding

When an exception leaves a scope, local objects are destroyed in reverse order of construction. This is called stack unwinding.

## RAII

Resource Acquisition Is Initialization binds resource ownership to object lifetime. Resources are released automatically when their owning objects are destroyed, including during exception handling.

## Manual Memory Management vs Smart Pointers

Manual new and delete require careful cleanup. Smart pointers such as std::unique_ptr manage ownership automatically and reduce memory leaks.

## Conclusion

RAII and smart pointers provide reliable resource cleanup during normal execution and exception propagation. Logging and rethrowing allow errors to be recorded without hiding them from higher-level handlers.
