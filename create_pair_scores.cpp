#include <string>
#include <map>
#include <iostream>
#include <fstream>

#include "common.h"

using namespace std;

int main() {
    ifstream file("past_answers.txt");
    string line;
    map<string, int> pairs;

    while(getline(file, line)) {

        for(int i=0; i<line.length()-1; i++) {
            string word = "";
            if (!isAlpha(line[i])) {
                continue;
            } else {
                word.push_back(line[i]);
            }

            int j=1;
            while (i+j<line.length() && !isAlpha(line[i+j])) {
                j++;
            }
            if (i+j!=line.length()) {
                word.push_back(line[i+j]);

                if (pairs.find(word) == pairs.end()) {
                    pairs.insert(pair<string, int>(word, 1));
                } else {
                    pairs[word]++;
                }
            }
        }
    }

    file.close();

    ofstream outfile("pair_scores.txt");
    map<string, int>::iterator p;
    for(p=pairs.begin(); p!=pairs.end(); p++) {
        outfile << p->first;
        outfile << " ";
        outfile << p->second;
        outfile << "\n";
    }

    outfile.close();

    return 0;

}

