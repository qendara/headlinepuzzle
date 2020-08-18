#ifndef ALPHABET_H
#define ALPHABET_H

#include <string>

using namespace std;

class Alphabet {

    public:
        Alphabet();
        ~Alphabet();
        bool setAlphabet(string alpha);
        string getOffset(int off);
        string decimate(int off);
    private:
        bool validateAlphabet(string alpha);

        string alphabet;
};

#endif
