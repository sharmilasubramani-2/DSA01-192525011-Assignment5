#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class BillingError : public runtime_error {
public:
    explicit BillingError(const string& message) : runtime_error(message) {}
};

class InvalidChargeError : public BillingError {
public:
    InvalidChargeError() : BillingError("Charges cannot be negative") {}
};

class ClaimLimitError : public BillingError {
public:
    ClaimLimitError() : BillingError("Claim exceeds the permitted coverage limit") {}
};

class UnknownPackageError : public BillingError {
public:
    UnknownPackageError() : BillingError("Unknown medical package") {}
};

class MissingPatientRecordError : public BillingError {
public:
    MissingPatientRecordError() : BillingError("Patient record not found") {}
};

class HospitalBilling {
public:
    void validateCharge(double amount) const {
        if (amount < 0)
            throw InvalidChargeError();
        cout << "Charge validated: " << amount << endl;
    }

    void validateClaim(double claim, double limit) const {
        if (claim > limit)
            throw ClaimLimitError();
        cout << "Insurance claim validated: " << claim << endl;
    }

    void validatePackage(const string& packageName) const {
        if (packageName != "General" && packageName != "Cardiac" &&
            packageName != "Orthopedic")
            throw UnknownPackageError();
        cout << "Package validated: " << packageName << endl;
    }

    void validatePatient(bool exists) const {
        if (!exists)
            throw MissingPatientRecordError();
        cout << "Patient record verified" << endl;
    }
};

int main() {
    HospitalBilling billing;

    try {
        billing.validateCharge(1500);
        billing.validateClaim(25000, 30000);
        billing.validatePackage("Cardiac");
        billing.validatePatient(true);
    }
    catch (const BillingError& error) {
        cout << "Billing Error: " << error.what() << endl;
    }

    cout << "\nTESTING ERROR CONDITIONS" << endl;

    try {
        billing.validateCharge(-500);
    }
    catch (const BillingError& error) {
        cout << error.what() << endl;
    }

    try {
        billing.validateClaim(50000, 30000);
    }
    catch (const BillingError& error) {
        cout << error.what() << endl;
    }

    try {
        billing.validatePackage("Dental");
    }
    catch (const BillingError& error) {
        cout << error.what() << endl;
    }

    try {
        billing.validatePatient(false);
    }
    catch (const BillingError& error) {
        cout << error.what() << endl;
    }

    return 0;
}
