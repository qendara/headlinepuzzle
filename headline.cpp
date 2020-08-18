#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>

#include "common.h"
#include "alphabet.h"
#include "headline.h"

using namespace std;


Headline::Headline(string cip) : cipher(cip), plain(""), alphabet(Alphabet()), offset(-1) {
    ifstream file("pair_scores.txt");
    string line;
    string word;
    int score;


    while(getline(file, line)) {
        istringstream s(line);
        s >> word;
        s >> score;

        scores.insert(pair<string, int>(word, score));
    }

    file.close();


}

string Headline::get_cipher() const {
    return cipher;
}

string Headline::get_plain() const {
    if (plain != "") {
        return plain;
    } else {
        return NULL;
    }
}

string Headline::get_alphabet() {
    if (alphabet.getOffset(0) != "" && offset > -1) {
        return alphabet.getOffset(offset);
    } else {
        return NULL;
    }
}

int Headline::score_translation(string translated) {
    
    int score = 0;

    string pair;

    for (int i=0; i<translated.length()-1; i++) {
        if (!isAlpha(translated[i])) {
            continue;
        } else {
            pair.push_back(translated[i]);
        }
        int j = 1;
        while (i+j<translated.length() && !isAlpha(translated[i+j])) {
            j++;
        }
        pair.push_back(translated[i+j]);

        if (scores.find(pair) != scores.end()) {
            score += scores[pair];
        }

        pair = "";
    }

    return score;

}

string Headline::translate(int off) {
    string translated;
    string offsetAlpha = alphabet.getOffset(off);
    // translate each letter 
    for(string::iterator pos = cipher.begin(); pos != cipher.end(); pos++) {
        int alphaPos = offsetAlpha.find(*pos);
        if (alphaPos != string::npos) {
            translated.push_back(offsetAlpha[(alphaPos-off+26)%26]);
        } else {
            translated.push_back(*pos);
        }
    }

    return translated;
}

void Headline::find_best_translation(string alpha) {
    int best_score = 0;
    string best_translation;
    int best_offset = 0;
    alphabet.setAlphabet(alpha);

    for (int i=1; i<26; i++) {
        string translated = translate(i);
        int score = score_translation(translated);
        if (score > best_score) {
            best_score = score;
            best_translation = translated;
            best_offset = i;
        }
    }

    plain = best_translation;

    offset = best_offset;
}

bool sortByValLength(pair<string, vector<string> >& a, pair<string, vector<string> >& b) {
    return a.second.size() < b.second.size();
}

string Headline::replaceLetters(string word, map<char, char> letterMap) {
    for (string::iterator s=word.begin(); s!=word.end(); s++) {
        if (letterMap.find(*s) != letterMap.end()) {
            *s = lower(letterMap[*s]);
        }
    }

    return word;
}

vector<string> Headline::condenseMatches(string cipher, vector<string> matches, map<char, char> letterMap) {
    vector<string> newMatches;


    for (vector<string>::iterator i=matches.begin(); i!=matches.end(); i++) {
        bool isValid = true;
        for (int ind=0; ind<cipher.length(); ind++) {
            if (letterMap.find(cipher[ind]) != letterMap.end()) {
                if ((*i)[ind] != letterMap[cipher[ind]]) {
                    isValid = false;
                }
            }
        }
        if (isValid) {
            newMatches.push_back(*i);
        }
    }

    return newMatches;
}


void Headline::guessPlain() {
    // Load patterns map

    ifstream file("patterns.txt");
    string line;
    string key;
    string word;
    map<string, vector<string> > patterns;


    while(getline(file, line)) {
        istringstream s(line);
        s >> key;

        patterns.insert(make_pair(word, vector<string>()));

        while (s >> word) {
            patterns[key].push_back(word);
        }

    }

    file.close();

    // Split cipher into words
    istringstream sCipher(cipher);
    vector<pair<string, vector<string> > > cipherWords;
    vector<string> plainWords;
    map<char, char> letterMap;

    // Create vector pair of cipherWords to possible matches
    while (sCipher >> word) {
        // filter out unnecessary characters (like quotes/question marks, etc.)
        // TODO this will filter out the characters but won't put them back afterward
        while (! isAlpha(word[0])) {
            word = word.substr(1);
        }
        while (! isAlpha(word[word.length()-1])) {
            word = word.substr(0, word.length()-1);
        }
        plainWords.push_back(word);
        string pattern = create_pattern(word);
        if (patterns.find(pattern) != patterns.end()) {
            cipherWords.push_back(make_pair(word, patterns[pattern]));
        } else {
            cipherWords.push_back(make_pair(word, vector<string>()));
        }
    }

    // sort cipher word maps by length of possible matches
    sort(cipherWords.begin(), cipherWords.end(), sortByValLength);

    // for each cipher word:
    // allow user to select match or provide their own
    // given that match, for each other word, replace appropriate letters and
    //   narrow down possible matches
    // theoretically then we want to re-sort the map of possible matches

    for (int i=0; i<cipherWords.size(); i++) {
        cout << cipherWords[i].first << "\n";
        for (int j=0; j<cipherWords[i].second.size(); j++) {
            cout << "[" << j+1 << "] " << cipherWords[i].second[j] << "\n";
        }

        cout << "Enter number of plaintext word, or 0 for none of these: ";

        int entry = 0;
        string s;
        getline(cin, s);
        istringstream instr(s);
        instr >> entry;
        if (entry > (cipherWords[i].second.size()+1) || entry < 0) {
            entry = 0;
        }
        if (entry != 0) {
            string answerWord = cipherWords[i].second[entry-1];
            for (int j=0; j<plainWords.size(); j++) {
                if (plainWords[j] == cipherWords[i].first) {
                    plainWords[j] = lower_word(answerWord);
                }
            }
            for (int j=0; j<cipherWords[i].first.length(); j++) {
                letterMap.insert(make_pair(cipherWords[i].first[j], answerWord[j]));
            }

            // now replace appropriate letters in all other words - in plainWords
            for (int j=0; j<plainWords.size(); j++) {
                plainWords[j] = replaceLetters(plainWords[j], letterMap);
            }

            // also cut down on possibilities in cipherWords for all other entries
            for (int j=i+1; j<cipherWords.size(); j++) {
                cipherWords[j].second = condenseMatches(cipherWords[j].first, cipherWords[j].second, letterMap);
            }
        }

    }

    cout << "Final result: \n";
    copy(plainWords.begin(), plainWords.end(), ostream_iterator<string>(cout, " "));

    // notes: if user doesn't select an option, still replace letters
    //   maybe allow users second chance to select it??? maybe not

    // maybe output stringed letters TODO

}
