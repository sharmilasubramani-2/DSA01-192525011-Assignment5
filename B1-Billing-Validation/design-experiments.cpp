#include <iostream>
#include <memory>
#include <stdexcept>
#include <type_traits>
using namespace std;

class Base {
public:
    double total() const {
        return 100.0;
    }
    ~Base() = default;
};

class Derived : public Base {
public:
    double total() const {
        return 250.0;
    }
};

class SafeBase {
public:
    virtual ~SafeBase() = default;
};

class SafeDerived : public SafeBase {};

class BillingError : public runtime_error {
public:
    using runtime_error::runtime_error;
};

class SpecificBillingError : public BillingError {
public:
    using BillingError::BillingError;
};

void rethrowWithOriginalType() {
    try {
        throw SpecificBillingError("Specific billing failure");
    }
    catch (const BillingError&) {
        cout << "Caught billing error and rethrowing original exception" << endl;
        throw;
    }
}

void rethrowByValue() {
    try {
        throw SpecificBillingError("Specific billing failure");
    }
    catch (BillingError& error) {
        cout << "Caught billing error and throwing by value" << endl;
        throw error;
    }
}

int main() {
    cout << "VIRTUAL FUNCTION REMOVAL EXPERIMENT" << endl;
    Derived derived;
    Base* pointer = &derived;
    cout << "Derived object through base pointer: " << pointer->total() << endl;
    cout << "Direct derived object call: " << derived.total() << endl;

    cout << "\nVIRTUAL DESTRUCTOR CHECK" << endl;
    cout << "Base has virtual destructor: " << boolalpha
         << has_virtual_destructor<Base>::value << endl;
    cout << "SafeBase has virtual destructor: "
         << has_virtual_destructor<SafeBase>::value << endl;

    cout << "\nEXCEPTION RETHROW USING throw;" << endl;
    try {
        rethrowWithOriginalType();
    }
    catch (const SpecificBillingError& error) {
        cout << "Original derived exception preserved: " << error.what() << endl;
    }

    cout << "\nEXCEPTION RETHROW USING throw error;" << endl;
    try {
        rethrowByValue();
    }
    catch (const BillingError& error) {
        cout << "Caught exception: " << error.what() << endl;
        cout << "Derived exception type may be sliced" << endl;
    }
}
