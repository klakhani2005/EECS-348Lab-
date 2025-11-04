#include <iostream>
#include <fstream>
#include <string>
#include "string_calculator.h"
using namespace std;

int main() {
    string filename;
    cout << "Enter file name: ";
    cin >> filename;

    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return 1;
    }

    string num1, num2;
    int lineNum = 1;
    while (infile >> num1 >> num2) {
        cout << "Line " << lineNum++ << ": ";

        if (!isValidDouble(num1)) {
            cout << "Invalid number: " << num1 << endl;
            continue;
        }
        if (!isValidDouble(num2)) {
            cout << "Invalid number: " << num2 << endl;
            continue;
        }

        string result = addStrings(num1, num2);
        cout << num1 << " + " << num2 << " = " << result << endl;
    }

    infile.close();
    return 0;
}
