#include <iostream>

#include "solver.h"
#include "headline.h"
#include "alphabet.h"
#include "common.h"

using namespace std;

Solver::Solver() {}

bool Solver::setHeadline(int key, Headline* headline) {
    if (key < 1 || key > 5) {
        return false;
    }

    headlines[key-1] = headline;
}

Headline* Solver::getHeadline(int key) {
    if (key < 1 || key > 5) {
        return NULL;
    } else {
        return headlines[key-1];
    }
}

void Solver::setAlphabet(Alphabet alpha) {
    alphabet = alpha;
}

Alphabet Solver::getAlphabet() {
    return alphabet;
}

Solver::~Solver() {
    for (int i=0; i<5; i++) {
        if (headlines[i] != NULL) {
            delete headlines[i];
        }
    }
}

void Solver::solveAllUsingAlphabet() {
    for (int i=0; i<5; i++) {
        if (headlines[i] == NULL) {
            cout << "Please fill in valid headlines first.\n";
            return;
        }
        headlines[i]->find_best_translation(alphabet.getOffset(0));
    }

    for (int i=0; i<5; i++) {
        cout << "   " << headlines[i]->get_plain() << "\n";
        cout << i+1 << ". " << headlines[i]->get_cipher() << "\n\n";
    }

    // TODO change colors if there's a vertical 5-letter word... this means
    // saving everything into a vector of strings before printing
    // will have to insert things into the string though? or just print letter at
    // a time? no, inserting things better, I think
    cout << spaced(alphabet.getOffset(0)) << "\n\n";

    for (int i=0; i<5; i++) {
        cout << spaced(headlines[i]->get_alphabet()) << "\n";
    }

    cout << "\n";
}

void Solver::guessHeadlinePlain(int head) {
    if (head < 1 || head > 5) {
        cout << "Invalid headline selected.\n";
        return;
    }

    headlines[head-1]->guessPlain();
}
