#include <chrono>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
using namespace chrono;

bool validateWithReturnCode(int value) {
    return value >= 0;
}

bool validateWithException(int value) {
    if (value < 0) {
        throw invalid_argument("Invalid billing value");
    }
    return true;
}

void runBenchmark(int invalidPercent, int count) {
    vector<int> values(count, 100);
    int invalidCount = count * invalidPercent / 100;

    for (int i = 0; i < invalidCount; ++i) {
        values[i] = -1;
    }

    volatile long long returnChecksum = 0;
    auto start = steady_clock::now();

    for (int value : values) {
        returnChecksum += validateWithReturnCode(value) ? 1 : 0;
    }

    auto returnTime = duration<double, milli>(
        steady_clock::now() - start).count();

    volatile long long exceptionChecksum = 0;
    start = steady_clock::now();

    for (int value : values) {
        try {
            exceptionChecksum += validateWithException(value) ? 1 : 0;
        }
        catch (const invalid_argument&) {
            ++exceptionChecksum;
        }
    }

    auto exceptionTime = duration<double, milli>(
        steady_clock::now() - start).count();

    cout << "\nInvalid input rate: " << invalidPercent << "%" << endl;
    cout << "Return-code validation: " << returnTime << " ms" << endl;
    cout << "Exception validation: " << exceptionTime << " ms" << endl;
    cout << "Checksums: " << returnChecksum << " / "
         << exceptionChecksum << endl;
}

int main() {
    const int count = 1000000;

    cout << "RETURN CODE VS EXCEPTION BENCHMARK" << endl;
    cout << "Input count: " << count << endl;

    runBenchmark(0, count);
    runBenchmark(1, count);
    runBenchmark(50, count);
}
