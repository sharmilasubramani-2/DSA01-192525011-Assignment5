#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Bill {
protected:
    string patientName;
    int patientId;

public:
    Bill(string name, int id) : patientName(name), patientId(id) {}

    virtual double total() const = 0;

    virtual void display() const {
        cout << "Patient: " << patientName << endl;
        cout << "Patient ID: " << patientId << endl;
        cout << "Bill Amount: " << total() << endl;
    }

    virtual ~Bill() = default;
};

class OPBill : public Bill {
private:
    double consultationFee;
    double testCharges;

public:
    OPBill(string name, int id, double consultation, double tests)
        : Bill(name, id), consultationFee(consultation), testCharges(tests) {}

    double total() const override {
        return consultationFee + testCharges;
    }

    void display() const override {
        cout << "OUTPATIENT BILL" << endl;
        Bill::display();
    }
};

class IPBill : public Bill {
private:
    double roomCharges;
    double treatmentCharges;
    double medicineCharges;

public:
    IPBill(string name, int id, double room, double treatment, double medicine)
        : Bill(name, id), roomCharges(room),
          treatmentCharges(treatment), medicineCharges(medicine) {}

    double total() const override {
        return roomCharges + treatmentCharges + medicineCharges;
    }

    void display() const override {
        cout << "INPATIENT BILL" << endl;
        Bill::display();
    }
};

int main() {
    vector<Bill*> bills;

    bills.push_back(new OPBill("Ravi", 101, 500, 1200));
    bills.push_back(new IPBill("Meena", 102, 15000, 25000, 7500));

    double grandTotal = 0;

    for (const Bill* bill : bills) {
        bill->display();
        grandTotal += bill->total();
        cout << endl;
    }

    cout << "GRAND TOTAL: " << grandTotal << endl;

    for (Bill* bill : bills) {
        delete bill;
    }

    return 0;
}