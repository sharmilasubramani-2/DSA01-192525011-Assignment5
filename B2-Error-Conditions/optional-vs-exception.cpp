#include <chrono>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
using namespace chrono;

bool validateReturnCode(int value) {
    return value >= 0;
}

bool validateException(int value) {
    if (value < 0) {
        throw invalid_argument("Invalid billing value");
    }
    return true;
}

void benchmark(int invalidPercent, int count) {
    vector<int> values(count, 100);
    int invalidCount = count * invalidPercent / 100;

    for (int i = 0; i < invalidCount; ++i) {
        values[i] = -1;
    }

    long long returnValid = 0;
    auto start = steady_clock::now();

    for (int value : values) {
        if (validateReturnCode(value)) {
            ++returnValid;
        }
    }

    double returnTime =
        duration<double, milli>(steady_clock::now() - start).count();

    long long exceptionValid = 0;
    start = steady_clock::now();

    for (int value : values) {
        try {
            if (validateException(value)) {
                ++exceptionValid;
            }
        }
        catch (const invalid_argument&) {
        }
    }

    double exceptionTime =
        duration<double, milli>(steady_clock::now() - start).count();

    cout << "\nInvalid rate: " << invalidPercent << "%" << endl;
    cout << "Return-code time: " << returnTime << " ms" << endl;
    cout << "Exception time: " << exceptionTime << " ms" << endl;
    cout << "Valid records - Return code: " << returnValid
         << " | Exceptions: " << exceptionValid << endl;

    if (returnValid != exceptionValid) {
        throw runtime_error("Validation results do not match");
    }
}

int main() {
    const int count = 1000000;
    cout << "CORRECTED VALIDATION BENCHMARK" << endl;
    cout << "Records per test: " << count << endl;
    benchmark(0, count);
    benchmark(1, count);
    benchmark(50, count);
    cout << "\nALL BENCHMARK CHECKS PASSED" << endl;
}
