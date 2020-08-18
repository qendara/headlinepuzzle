#include "common.h"

#include <string>
#include <vector>
#include <fstream>
#include <iterator>


int main() {

    ifstream dict("/usr/share/dict/american-english");

    string word;

    vector<string> words;

    while (getline(dict, word)) {
        bool badWord = false;
        word = upper_word(word);
        if (word.length() != 5) {
            badWord = true;
        } else {
            for (int i=0; i<word.length(); i++) {
                if (!isAlpha(word[i])) {
                    badWord = true;
                }
            }
        }
        if (!badWord) {
            words.push_back(word);
        }
    }

    dict.close();

    ofstream word_list("fives.txt");
    vector<string>::iterator p;
    for (p=words.begin(); p!=words.end(); p++) {
        word_list << *p << "\n";
    }

    word_list.close();

    return 0;
}
