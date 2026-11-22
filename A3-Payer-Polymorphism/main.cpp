#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;

class Bill {
public:
    virtual double total() const = 0;
    virtual ~Bill() = default;
};

class OPBill : public Bill {
private:
    double amount;

public:
    explicit OPBill(double value) : amount(value) {}

    double total() const override {
        return amount;
    }
};

class IPBill : public Bill {
private:
    double amount;

public:
    explicit IPBill(double value) : amount(value) {}

    double total() const override {
        return amount;
    }
};

class Payer {
public:
    virtual double amountCovered(const Bill& bill) const = 0;
    virtual ~Payer() = default;
};

class SelfPay : public Payer {
public:
    double amountCovered(const Bill&) const override {
        return 0;
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
};

class GovernmentScheme : public Payer {
private:
    double coverageRate;

public:
    explicit GovernmentScheme(double rate) : coverageRate(rate) {}

    double amountCovered(const Bill& bill) const override {
        return bill.total() * coverageRate;
    }
};

int main() {
    vector<unique_ptr<Bill>> bills;
    bills.push_back(make_unique<OPBill>(1700));
    bills.push_back(make_unique<IPBill>(47500));

    vector<unique_ptr<Payer>> payers;
    payers.push_back(make_unique<SelfPay>());
    payers.push_back(make_unique<Insurance>(30000, 0.20));
    payers.push_back(make_unique<GovernmentScheme>(0.75));

    vector<string> names = {
        "Self Pay",
        "Insurance",
        "Government Scheme"
    };

    for (size_t i = 0; i < payers.size(); ++i) {
        cout << "\n" << names[i] << endl;

        for (const auto& bill : bills) {
            double total = bill->total();
            double covered = payers[i]->amountCovered(*bill);

            cout << "Bill Amount: " << total << endl;
            cout << "Covered Amount: " << covered << endl;
            cout << "Patient Pays: " << total - covered << endl;
        }
    }

    return 0;
}
