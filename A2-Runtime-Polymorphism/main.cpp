#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Bill {
public:
    Bill() {
        cout << "Bill constructor called" << endl;
    }

    virtual void generate() const {
        cout << "Generating a general bill" << endl;
    }

    virtual ~Bill() {
        cout << "Bill destructor called" << endl;
    }
};

class OPBill : public Bill {
public:
    OPBill() {
        cout << "OPBill constructor called" << endl;
    }

    void generate() const override {
        cout << "Generating outpatient bill" << endl;
    }

    ~OPBill() override {
        cout << "OPBill destructor called" << endl;
    }
};

class IPBill : public Bill {
public:
    IPBill() {
        cout << "IPBill constructor called" << endl;
    }

    void generate() const override {
        cout << "Generating inpatient bill" << endl;
    }

    ~IPBill() override {
        cout << "IPBill destructor called" << endl;
    }
};

int main() {
    cout << "RUNTIME POLYMORPHISM" << endl;

    vector<unique_ptr<Bill>> bills;

    bills.push_back(make_unique<OPBill>());
    bills.push_back(make_unique<IPBill>());

    cout << "\nFUNCTION CALLS THROUGH BASE CLASS POINTERS" << endl;

    for (const auto& bill : bills) {
        bill->generate();
        cout << endl;
    }

    cout << "OBJECT DESTRUCTION" << endl;

    bills.clear();

    return 0;
}