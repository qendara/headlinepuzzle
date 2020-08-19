#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

#include "common.h"

using namespace std;

bool isAlpha(char c) {
    return (c >= 0x41 && c <= 0x5a);
}

bool isNotAlpha(char c) {
    return !isAlpha(c);
}

bool isEmpty(string s) {
    return s == "";
}

string create_order(string word) {
    vector<int> order(word.length());
    int curNum = 0;
    int pastPos = 0;
    char curLet = 'A';

    while(curLet <= 'Z') {
        int pos = word.find(curLet, pastPos);
        if (pos == string::npos) {
            curLet++;
            pastPos = 0;
        } else {
            order[pos] = curNum;
            curNum++;
            pastPos = pos+1;
        }
    }

    ostringstream os;
    for (int i=0; i<order.size(); i++) {
        os << order[i];
    }

    return os.str();
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
