#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
using namespace std;

class Bill {
protected:
    string patientName;

public:
    explicit Bill(const string& name) : patientName(name) {}

    virtual double total() const = 0;

    virtual void display() const {
        cout << "Patient: " << patientName
             << " | Bill Amount: " << total() << endl;
    }

    virtual ~Bill() = default;
};

class OPBill : public Bill {
private:
    double consultation;
    double medicine;

public:
    OPBill(const string& name, double c, double m)
        : Bill(name), consultation(c), medicine(m) {}

    double total() const override {
        return consultation + medicine;
    }
};

class IPBill : public Bill {
private:
    double room;
    double treatment;
    double medicine;

public:
    IPBill(const string& name, double r, double t, double m)
        : Bill(name), room(r), treatment(t), medicine(m) {}

    double total() const override {
        return room + treatment + medicine;
    }
};

class EmergencyBill : public Bill {
private:
    double emergencyFee;
    double treatment;
    double medicine;

public:
    EmergencyBill(const string& name, double fee, double t, double m)
        : Bill(name), emergencyFee(fee), treatment(t), medicine(m) {}

    double total() const override {
        return emergencyFee + treatment + medicine;
    }

    void display() const override {
        cout << "NEW EMERGENCY BILL | Patient: " << patientName
             << " | Total: " << total() << endl;
    }
};

class Payer {
public:
    virtual double amountCovered(const Bill& bill) const = 0;
    virtual string name() const = 0;
    virtual ~Payer() = default;
};

class SelfPay : public Payer {
public:
    double amountCovered(const Bill&) const override {
        return 0;
    }

    string name() const override {
        return "Self Pay";
    }
};

class Insurance : public Payer {
private:
    double limit;
    double copay;

public:
    Insurance(double coverageLimit, double coPay)
        : limit(coverageLimit), copay(coPay) {}

    double amountCovered(const Bill& bill) const override {
        double eligible = bill.total() * (1.0 - copay);
        return eligible < limit ? eligible : limit;
    }

    string name() const override {
        return "Insurance";
    }
};

class GovernmentScheme : public Payer {
private:
    double coverageRate;

public:
    explicit GovernmentScheme(double rate) : coverageRate(rate) {}

    double amountCovered(const Bill& bill) const override {
        return bill.total() * coverageRate;
    }

    string name() const override {
        return "Government Scheme";
    }
};

class CorporatePayer : public Payer {
private:
    double coverageRate;
    double maximumCoverage;

public:
    CorporatePayer(double rate, double maximum)
        : coverageRate(rate), maximumCoverage(maximum) {}

    double amountCovered(const Bill& bill) const override {
        double amount = bill.total() * coverageRate;
        return amount < maximumCoverage ? amount : maximumCoverage;
    }

    string name() const override {
        return "Corporate Health Plan";
    }
};

class BillingResource {
private:
    string resourceName;

public:
    explicit BillingResource(const string& name) : resourceName(name) {
        cout << resourceName << " acquired" << endl;
    }

    ~BillingResource() {
        cout << resourceName << " released" << endl;
    }
};

void processEmergencyClaim(const Bill& bill, const Payer& payer) {
    BillingResource database("Emergency Claim Database");

    cout << "Processing emergency claim" << endl;

    double covered = payer.amountCovered(bill);

    if (covered < 0 || covered > bill.total())
        throw runtime_error("Invalid payer coverage amount");

    cout << "Payer: " << payer.name() << endl;
    cout << "Bill Amount: " << bill.total() << endl;
    cout << "Covered Amount: " << covered << endl;
    cout << "Patient Pays: " << bill.total() - covered << endl;

    throw runtime_error("Simulated claim interruption");
}

int main() {
    cout << fixed << setprecision(2);

    cout << "B4 - FINAL ENGINEERING DECISION" << endl;
    cout << "================================" << endl;

    vector<unique_ptr<Bill>> bills;

    bills.push_back(make_unique<OPBill>("Ravi", 500, 1200));
    bills.push_back(make_unique<IPBill>("Meena", 15000, 25000, 7500));
    bills.push_back(make_unique<EmergencyBill>("Arun", 5000, 12000, 3000));

    cout << "\nBILL TYPE EXTENSION TEST" << endl;

    double grandTotal = 0;

    for (const auto& bill : bills) {
        bill->display();
        grandTotal += bill->total();
    }

    cout << "Grand Total: " << grandTotal << endl;

    vector<unique_ptr<Payer>> payers;

    payers.push_back(make_unique<SelfPay>());
    payers.push_back(make_unique<Insurance>(30000, 0.20));
    payers.push_back(make_unique<GovernmentScheme>(0.75));
    payers.push_back(make_unique<CorporatePayer>(0.90, 50000));

    cout << "\nPAYER EXTENSION TEST" << endl;

    for (const auto& payer : payers) {
        double covered = payer->amountCovered(*bills[2]);

        cout << payer->name()
             << " | Emergency Bill: " << bills[2]->total()
             << " | Covered: " << covered
             << " | Patient Pays: " << bills[2]->total() - covered
             << endl;
    }

    cout << "\nEXCEPTION SAFETY AND RESOURCE CLEANUP" << endl;

    try {
        processEmergencyClaim(*bills[2], *payers[3]);
    }
    catch (const exception& error) {
        cout << "Exception handled: " << error.what() << endl;
    }

    cout << "\nB4 IMPLEMENTATION COMPLETED" << endl;

    return 0;
}
