#include <string>
#include <iostream>
#include <algorithm>


#include "common.h"
#include "alphabet.h"

using namespace std;

Alphabet::Alphabet() {}

bool Alphabet::setAlphabet(string alpha) {
    bool ret = validateAlphabet(alpha);

    if (ret) alphabet = alpha;

    return ret;
}

bool Alphabet::validateAlphabet(string alpha) {

    if (alpha.length() != 26) {
        return false;
    }

    for (int i=0; i<alpha.length(); i++) {
        if (!isAlpha(alpha[i])) {
            return false;
        }
    }

    string::iterator pos = unique(alpha.begin(), alpha.end());
    if (pos != alpha.end()) {
        return false;
    }

    return true;
}

string Alphabet::getOffset(int off) {
    if (alphabet == "") {
        return "";
    }

    if (off == 0) {
        return alphabet;
    }

    string new_alpha;
    for (int i=0; i<26; i++) {
        new_alpha.push_back(alphabet[(i+off+26)%26]);
    }

    return new_alpha;
}

Alphabet::~Alphabet() {}

string Alphabet::decimate(int off) {
    if (off == 0) {
        return alphabet;
    }

    if (off % 2 == 0) {
        return "";
    }

    string new_alpha;

    // ABCDEFGHIJKLMNOPQRSTUVWXYZ
    // ADGJMPSVYBEHKNQTWZCFILORUX
    for (int i=0; i<26; i++) {
        new_alpha.push_back(alphabet[(off*i)%26]);
    }

    return new_alpha;
}
