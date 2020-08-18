#include <string>
#include <algorithm>

#include "common.h"

using namespace std;

bool isAlpha(char c) {
    return (c >= 0x41 && c <= 0x5a);
}


string create_pattern(string word) {
    string pat;
    char curLet = 'A';

    for(int i=0; i<word.length(); i++) {
        int pos = word.find(word[i]);
        if (pos < i) {
            pat.push_back(pat[pos]);
        } else if (isAlpha(word[i])) {
            pat.push_back(curLet);
            curLet++;
        } else {
            pat.push_back(word[i]);
        }
    }

    return pat;
}

char lower(char s) {
    return tolower(s);
}

string lower_word(string s) {
    transform(s.begin(), s.end(), s.begin(), lower);
    return s;
}

char upper(char s) {
    return toupper(s);
}

string upper_word(string s) {
    transform(s.begin(), s.end(), s.begin(), upper);
    return s;
}

string spaced(string str) {
    string new_string(str.length()*2-1, ' ');

    for (int i=0; i<str.length(); i++) {
        new_string[i*2] = str[i];
    }

    return new_string;
}
