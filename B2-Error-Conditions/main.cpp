#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <new>
#include <memory>
using namespace std;

class ClaimError : public runtime_error {
public:
    explicit ClaimError(const string& message) : runtime_error(message) {}
};

class Resource {
private:
    string name;

public:
    explicit Resource(const string& resourceName) : name(resourceName) {
        cout << name << " acquired" << endl;
    }

    ~Resource() {
        cout << name << " released" << endl;
    }
};

class BillingValidator {
public:
    void validateCharge(double amount) const {
        if (amount < 0)
            throw ClaimError("Negative billing charges are not permitted");
        cout << "Charge validated: " << amount << endl;
    }

    void validateClaim(double claim, double coverageLimit) const {
        if (claim > coverageLimit)
            throw ClaimError("Insurance claim exceeds coverage limit");
        cout << "Insurance claim validated: " << claim << endl;
    }

    void validatePackage(const string& packageName) const {
        if (packageName != "Cardiac" &&
            packageName != "General" &&
            packageName != "Orthopedic")
            throw ClaimError("Unknown medical package: " + packageName);

        cout << "Package validated: " << packageName << endl;
    }

    double parseAmount(const string& input) const {
        try {
            size_t position = 0;
            double amount = stod(input, &position);

            if (position != input.length())
                throw invalid_argument("Invalid numeric input");

            return amount;
        }
        catch (const exception&) {
            throw ClaimError("Invalid numeric billing input");
        }
    }
};

void processClaim() {
    Resource database("Database Connection");
    Resource transaction("Claim Transaction");

    cout << "Processing insurance claim" << endl;
    throw ClaimError("Claim processing failed");
}

void demonstrateExceptionRecovery() {
    try {
        processClaim();
    }
    catch (const ClaimError& error) {
        cout << "Claim error logged: " << error.what() << endl;
        cout << "Rethrowing claim error" << endl;
        throw;
    }
}

void demonstrateBadAllocation() {
    try {
        cout << "Simulating memory allocation failure" << endl;
        throw bad_alloc();
    }
    catch (const bad_alloc&) {
        cout << "Memory allocation failure handled" << endl;
    }
}

int main() {
    BillingValidator validator;

    cout << "HOSPITAL BILLING ERROR VALIDATION" << endl;
    cout << "=================================" << endl;

    try {
        validator.validateCharge(1500);
    }
    catch (const ClaimError& error) {
        cout << error.what() << endl;
    }

    try {
        validator.validateCharge(-500);
    }
    catch (const ClaimError& error) {
        cout << "Negative Charge Test: " << error.what() << endl;
    }

    try {
        validator.validateClaim(45000, 30000);
    }
    catch (const ClaimError& error) {
        cout << "Claim Limit Test: " << error.what() << endl;
    }

    try {
        validator.validatePackage("Unknown");
    }
    catch (const ClaimError& error) {
        cout << "Package Test: " << error.what() << endl;
    }

    try {
        double amount = validator.parseAmount("12AB");
        cout << "Parsed amount: " << amount << endl;
    }
    catch (const ClaimError& error) {
        cout << "Numeric Input Test: " << error.what() << endl;
    }

    demonstrateBadAllocation();

    cout << "\nEXCEPTION PROPAGATION AND RESOURCE CLEANUP" << endl;

    try {
        demonstrateExceptionRecovery();
    }
    catch (const ClaimError& error) {
        cout << "Top-Level Handler: " << error.what() << endl;
    }
    catch (...) {
        cout << "Unknown error handled by top-level handler" << endl;
    }

    cout << "\nALL ERROR VALIDATION TESTS COMPLETED" << endl;

    return 0;
}
