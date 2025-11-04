#include "string_calculator.h"
#include <cctype>
#include <algorithm>
#include <iostream>

static string trimLeadingZeros(string s) {
    int i = 0;
    while (i + 1 < (int)s.size() && s[i] == '0' && s[i+1] != '.') i++;
    return s.substr(i);
}

bool isValidDouble(const string &s) {
    if (s.empty()) return false;
    int i = 0, n = s.size();
    if (s[i] == '+' || s[i] == '-') i++;
    if (i == n) return false;

    bool hasDot = false, hasDigitBefore = false, hasDigitAfter = false;

    for (; i < n; ++i) {
        char c = s[i];
        if (isdigit(c)) {
            if (!hasDot) hasDigitBefore = true;
            else hasDigitAfter = true;
        } else if (c == '.') {
            if (hasDot) return false;
            hasDot = true;
        } else {
            return false;
        }
    }
    if (!hasDot) return hasDigitBefore;
    return hasDigitBefore && hasDigitAfter;
}

static string addIntegerStrings(string a, string b) {
    string result = "";
    int carry = 0;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int n = max(a.size(), b.size());
    for (int i = 0; i < n; i++) {
        int da = (i < (int)a.size()) ? a[i] - '0' : 0;
        int db = (i < (int)b.size()) ? b[i] - '0' : 0;
        int sum = da + db + carry;
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
    }
    if (carry) result.push_back(carry + '0');
    reverse(result.begin(), result.end());
    return result;
}

static void equalizeFractionParts(string &aFrac, string &bFrac) {
    while (aFrac.size() < bFrac.size()) aFrac += '0';
    while (bFrac.size() < aFrac.size()) bFrac += '0';
}

string addStrings(string a, string b) {
    bool negA = false, negB = false;
    if (a[0] == '-') { negA = true; a = a.substr(1); }
    if (a[0] == '+') a = a.substr(1);
    if (b[0] == '-') { negB = true; b = b.substr(1); }
    if (b[0] == '+') b = b.substr(1);

    size_t dotA = a.find('.');
    size_t dotB = b.find('.');
    string aInt = (dotA == string::npos) ? a : a.substr(0, dotA);
    string bInt = (dotB == string::npos) ? b : b.substr(0, dotB);
    string aFrac = (dotA == string::npos) ? "" : a.substr(dotA + 1);
    string bFrac = (dotB == string::npos) ? "" : b.substr(dotB + 1);

    equalizeFractionParts(aFrac, bFrac);
    string fullA = aInt + aFrac;
    string fullB = bInt + bFrac;

    string fullSum = addIntegerStrings(fullA, fullB);

    if (!aFrac.empty()) {
        int pos = fullSum.size() - aFrac.size();
        fullSum.insert(pos, ".");
    }
    return trimLeadingZeros(fullSum);
}
