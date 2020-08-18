#ifndef SOLVER_H
#define SOLVER_H

#include "headline.h"
#include "alphabet.h"

#include <string>
#include <vector>

using namespace std;

class Solver {

    public:
        Solver();
        ~Solver();
        bool setHeadline(int key, Headline* headline);
        Headline* getHeadline(int key);
        void setAlphabet(Alphabet alpha);
        Alphabet getAlphabet();
        void solveAllUsingAlphabet();
        void guessHeadlinePlain(int head);

    private:
        Alphabet alphabet;
        vector<Headline*> headlines = vector<Headline*>(5);
};

#endif
