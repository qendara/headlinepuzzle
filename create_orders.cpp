#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <sstream>

#include "common.h"

using namespace std;


int main() {
    
    map<string, string> patterns;

    // Read in all the words
    // /usr/share/dict/american-english
    ifstream dict("/usr/share/dict/american-english");

    string word;

    while(getline(dict, word)) {
        bool badWord = false;
        // Capitalize the word so we don't have any lowercase
        word = upper_word(word);
        for (int i=0; i<word.length(); i++) {
            if (!isAlpha(word[i])) {
                badWord = true;
            }
        }
        if (!badWord) {
            // For each word, create the pattern, like ABCCDEF for pattern
            string pat = create_order(word);

            // Fill in the map of <word, pattern>
            if(patterns.find(word) == patterns.end()) {
                patterns.insert(pair<string, string>(word, pat));
            }
        }
    }

    dict.close();

    map<string, vector<string> > words;
    // Now, turn it around - make the map <pattern, <word, word, ...> >
    map<string, string>::iterator iter;
    for(iter=patterns.begin(); iter!=patterns.end(); iter++) {
        if(words.find(iter->second) != words.end()) {
            words[iter->second].push_back(iter->first);
        } else {
            words.insert(pair<string, vector<string> >(iter->second, vector<string>()));
            words[iter->second].push_back(iter->first);
        }
    }

    // Write this new map to file

    ofstream pat_dict("orders.txt");
    map<string, vector<string> >::iterator p;
    for (p=words.begin(); p!=words.end(); p++) {
        pat_dict << p->first;
        for (int i=0; i<(p->second).size(); i++) {
            pat_dict << "\t" << (p->second)[i];
        }
        pat_dict << "\n";
    }

    pat_dict.close();

    return 0;

}
