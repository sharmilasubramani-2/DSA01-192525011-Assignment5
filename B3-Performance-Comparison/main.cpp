#include <iostream>
#include <vector>
#include <variant>
#include <chrono>
#include <stdexcept>
#include <iomanip>
#include <string>
using namespace std;

using Clock = chrono::high_resolution_clock;

volatile double benchmarkResult = 0.0;

class Bill {
public:
    virtual double total() const = 0;
    virtual ~Bill() = default;
};

class OPBill : public Bill {
private:
    double consultation;
    double medicine;

public:
    OPBill(double c, double m) : consultation(c), medicine(m) {}

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

template <typename Function>
double measure(Function function) {
    auto start = Clock::now();
    double result = function();
    auto end = Clock::now();

    benchmarkResult = result;

    return chrono::duration<double, milli>(end - start).count();
}

double benchmarkVirtual(size_t count) {
    OPBill outpatient(500, 1200);
    IPBill inpatient(15000, 25000, 7500);

    Bill* bills[] = {&outpatient, &inpatient};

    double sum = 0;

    for (size_t i = 0; i < count; ++i)
        sum += bills[i % 2]->total();

    return sum;
}

double benchmarkVariant(size_t count) {
    BillVariant outpatient = VariantOP{500, 1200};
    BillVariant inpatient = VariantIP{15000, 25000, 7500};

    double sum = 0;

    for (size_t i = 0; i < count; ++i)
        sum += variantTotal(i % 2 == 0 ? outpatient : inpatient);

    return sum;
}

bool validateReturnCode(double amount) {
    return amount >= 0;
}

void validateException(double amount) {
    if (amount < 0)
        throw runtime_error("Invalid billing amount");
}

double benchmarkReturnCodes(size_t count, size_t invalidCount) {
    double sum = 0;

    for (size_t i = 0; i < count; ++i) {
        double amount = i < invalidCount ? -100.0 : 100.0;

        if (validateReturnCode(amount))
            sum += amount;
    }

    return sum;
}

double benchmarkExceptions(size_t count, size_t invalidCount) {
    double sum = 0;

    for (size_t i = 0; i < count; ++i) {
        double amount = i < invalidCount ? -100.0 : 100.0;

        try {
            validateException(amount);
            sum += amount;
        }
        catch (const runtime_error&) {
        }
    }

    return sum;
}

int main() {
    cout << fixed << setprecision(3);

    cout << "HOSPITAL BILLING PERFORMANCE BENCHMARK" << endl;
    cout << "======================================" << endl;

    cout << "\n1. RUNTIME POLYMORPHISM BENCHMARK" << endl;

    vector<size_t> sizes = {1000, 1000000, 10000000};

    for (size_t count : sizes) {
        double elapsed = measure([&]() {
            return benchmarkVirtual(count);
        });

        cout << count << " operations: "
             << elapsed << " ms" << endl;
    }

    cout << "\n2. VARIANT AND VISIT BENCHMARK" << endl;

    double variantTime = measure([]() {
        return benchmarkVariant(10000000);
    });

    cout << "10000000 operations: "
         << variantTime << " ms" << endl;

    cout << "\n3. RETURN CODE VS EXCEPTION VALIDATION" << endl;

    const size_t count = 1000000;

    vector<double> invalidRates = {0.0, 0.01, 0.50};

    for (double rate : invalidRates) {
        size_t invalidCount = static_cast<size_t>(count * rate);

        cout << "\nInvalid input rate: "
             << rate * 100 << "%" << endl;

        double returnTime = measure([&]() {
            return benchmarkReturnCodes(count, invalidCount);
        });

        double exceptionTime = measure([&]() {
            return benchmarkExceptions(count, invalidCount);
        });

        cout << "Return-code validation: "
             << returnTime << " ms" << endl;

        cout << "Exception-based validation: "
             << exceptionTime << " ms" << endl;
    }

    cout << "\n4. BENCHMARK COMPLETED" << endl;
    cout << "Final checksum: " << benchmarkResult << endl;

    return 0;
}
