#include <iostream>
#include <vector>
#include <memory>
#include <variant>
#include <iomanip>
#include <cmath>
#include <type_traits>
using namespace std;

class Bill {
public:
    virtual double total() const = 0;
    virtual ~Bill() = default;
};

class OPBill : public Bill {
    double consultation;
    double medicine;

public:
    OPBill(double c, double m) : consultation(c), medicine(m) {}

    double total() const override {
        return consultation + medicine;
    }
};

class IPBill : public Bill {
    double room;
    double treatment;
    double medicine;

public:
    IPBill(double r, double t, double m)
        : room(r), treatment(t), medicine(m) {}

    double total() const override {
        return room + treatment + medicine;
    }
};

struct VariantOP {
    double consultation;
    double medicine;
};

struct VariantIP {
    double room;
    double treatment;
    double medicine;
};

using BillVariant = variant<VariantOP, VariantIP>;

double variantTotal(const BillVariant& bill) {
    return visit([](const auto& item) -> double {
        if constexpr (is_same_v<decay_t<decltype(item)>, VariantOP>)
            return item.consultation + item.medicine;
        else
            return item.room + item.treatment + item.medicine;
    }, bill);
}

int main() {
    vector<unique_ptr<Bill>> polymorphicBills;
    vector<BillVariant> variantBills;

    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0) {
            double consultation = 500 + i * 100;
            double medicine = 1200 + i * 50;

            polymorphicBills.push_back(
                make_unique<OPBill>(consultation, medicine)
            );

            variantBills.push_back(
                VariantOP{consultation, medicine}
            );
        }
        else {
            double room = 15000 + i * 500;
            double treatment = 25000 + i * 1000;
            double medicine = 7500 + i * 200;

            polymorphicBills.push_back(
                make_unique<IPBill>(room, treatment, medicine)
            );

            variantBills.push_back(
                VariantIP{room, treatment, medicine}
            );
        }
    }

    double polymorphicTotal = 0;
    double variantGrandTotal = 0;

    cout << fixed << setprecision(2);
    cout << "TEN BILL CORRECTNESS COMPARISON" << endl;
    cout << "===============================" << endl;

    for (size_t i = 0; i < polymorphicBills.size(); ++i) {
        double first = polymorphicBills[i]->total();
        double second = variantTotal(variantBills[i]);

        cout << "Bill " << i + 1
             << " | Polymorphism: " << first
             << " | Variant: " << second << endl;

        if (abs(first - second) > 0.001) {
            cerr << "Mismatch detected in bill " << i + 1 << endl;
            return 1;
        }

        polymorphicTotal += first;
        variantGrandTotal += second;
    }

    cout << "\nPolymorphic Grand Total: "
         << polymorphicTotal << endl;

    cout << "Variant Grand Total: "
         << variantGrandTotal << endl;

    if (abs(polymorphicTotal - variantGrandTotal) > 0.001) {
        cerr << "Grand total mismatch" << endl;
        return 1;
    }

    cout << "\nALL TEN BILL CORRECTNESS TESTS PASSED" << endl;

    return 0;
}
