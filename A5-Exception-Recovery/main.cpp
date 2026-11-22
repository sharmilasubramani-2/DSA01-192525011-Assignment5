#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
using namespace std;

class Resource {
private:
    string name;

public:
    explicit Resource(string value) : name(value) {
        cout << name << " acquired" << endl;
    }

    ~Resource() {
        cout << name << " released" << endl;
    }
};

void processClaim() {
    Resource database("Database Connection");
    Resource transaction("Transaction");

    cout << "Processing insurance claim" << endl;

    throw runtime_error("Claim processing failed");
}

void handleClaim() {
    try {
        processClaim();
    }
    catch (const exception& error) {
        cout << "Error logged: " << error.what() << endl;
        cout << "Rethrowing exception" << endl;
        throw;
    }
}

int main() {
    cout << "HOSPITAL CLAIM RECOVERY SYSTEM" << endl;

    try {
        handleClaim();
    }
    catch (const exception& error) {
        cout << "Final handler: " << error.what() << endl;
    }

    cout << "\nRAII RESOURCE MANAGEMENT" << endl;

    {
        unique_ptr<Resource> report =
            make_unique<Resource>("Billing Report");

        cout << "Generating billing report" << endl;
    }

    cout << "\nProgram completed safely" << endl;

    return 0;
}
