#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

class Bill {
protected:
    string patientName;

public:
    explicit Bill(string name) : patientName(name) {}

    virtual double total() const = 0;
    virtual void display() const = 0;

    virtual ~Bill() = default;
};

class OPBill : public Bill {
private:
    double consultationFee;
    double testCharges;

public:
    OPBill(string name, double consultation, double tests)
        : Bill(name), consultationFee(consultation), testCharges(tests) {}

    double total() const override {
        return consultationFee + testCharges;
    }

    void display() const override {
        cout << "OP " << patientName << ": " << total() << endl;
    }
};

class IPBill : public Bill {
private:
    double roomCharges;
    double treatmentCharges;
    double medicineCharges;

public:
    IPBill(string name, double room, double treatment, double medicine)
        : Bill(name), roomCharges(room),
          treatmentCharges(treatment), medicineCharges(medicine) {}

    double total() const override {
        return roomCharges + treatmentCharges + medicineCharges;
    }

    void display() const override {
        cout << "IP " << patientName << ": " << total() << endl;
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
    double coverLimit;
    double coPayRate;

public:
    Insurance(double limit, double rate)
        : coverLimit(limit), coPayRate(rate) {}

    double amountCovered(const Bill& bill) const override {
        return min(bill.total(), coverLimit) * (1.0 - coPayRate);
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

int main() {
    cout << fixed << setprecision(2);

    vector<unique_ptr<Bill>> bills;

    bills.push_back(make_unique<OPBill>("Ravi", 500, 1200));
    bills.push_back(make_unique<IPBill>("Meena", 15000, 25000, 7500));

    vector<unique_ptr<Payer>> payers;

    payers.push_back(make_unique<SelfPay>());
    payers.push_back(make_unique<Insurance>(30000, 0.20));
    payers.push_back(make_unique<GovernmentScheme>(0.75));

    cout << "HOSPITAL BILLING VALIDATION" << endl;
    cout << "===========================" << endl;

    double grandTotal = 0;

    for (const auto& bill : bills) {
        bill->display();
        grandTotal += bill->total();
    }

    cout << "TOTAL BILL AMOUNT: " << grandTotal << endl;

    cout << "\nPAYER VALIDATION" << endl;

    for (const auto& payer : payers) {
        cout << "\n" << payer->name() << endl;

        for (const auto& bill : bills) {
            double amount = bill->total();
            double covered = payer->amountCovered(*bill);
            double patientPay = amount - covered;

            cout << "Bill: " << amount
                 << " | Covered: " << covered
                 << " | Patient Pays: " << patientPay << endl;

            if (covered < 0 || covered > amount) {
                cerr << "VALIDATION FAILED" << endl;
                return 1;
            }
        }
    }

    cout << "\nALL BILLING VALIDATIONS PASSED" << endl;

    return 0;
}
