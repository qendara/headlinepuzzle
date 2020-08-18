#ifndef HEADLINE_H
#define HEADLINE_H

#include <string>
#include <map>
#include <vector>

#include "alphabet.h"

using namespace std;

class Headline {
    public:
        Headline(string cip);
        string get_cipher() const;
        string get_plain() const;
        string get_alphabet();
        void find_best_translation(string alpha);
        void guessPlain();

    private:
        int score_translation(string translation);
        string translate(int off);
        string replaceLetters(string word, map<char, char> letterMap);
        vector<string> condenseMatches(string cipher, vector<string> matches, map<char, char> letterMap);
        string cipher;
        string plain;
        Alphabet alphabet;
        int offset;
        map<string, int> scores;
};

#endif
