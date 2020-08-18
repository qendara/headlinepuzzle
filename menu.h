#ifndef MENU_H
#define MENU_H

#include <string>

#include "headline.h"
#include "solver.h"

using namespace std;

class Menu {

    public:
        Menu();
        ~Menu();
        void mainMenu();
        void setHeadlines();
        void setAlphabet();
        void solveUsingAlphabet();
        void guessHeadline();
        void decimateAlphabet();

    private:
        Solver* solver;
};

#endif
