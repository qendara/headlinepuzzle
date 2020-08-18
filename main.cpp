#include <iostream>
#include <string>

#include "headline.h"
#include "alphabet.h"
#include "solver.h"
#include "menu.h"

using namespace std;

int main() {

    //Headline headline("LVTSYRRB HGSFG VISFVAS 3.74 ESAFSSG RL GSCVFVUORX");

    //headline.find_best_translation("EDQZMHUTCPYBKXNJWLFROIVAGS");

    //cout << headline.get_alphabet();
    //cout << "\n";
    //cout << headline.get_plain();
    //cout << "\n";

    //headline.guessPlain();

    //Alphabet alphabet;
    //alphabet.setAlphabet("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    //cout << "Decimated by 3: " << alphabet.decimate(3) << "\n";

    Solver solver;
    solver.setHeadline(1, new Headline("UFWANNF VOT GACWFV DOT QORA HOZVAG RAMMAN UZBHMZWA"));
    solver.setHeadline(2, new Headline("UXWTEJDBBQNNTT SMQGXET FTMNU NKT UNXSSQIH DXN DS UNDJRU"));
    solver.setHeadline(3, new Headline("KYKWV YLNC LWGNGL GDSBBH FLSCNYLW QNHZYAEGSD KH QLCPNWG"));
    solver.setHeadline(4, new Headline("XJU VOTV DLWA MQOB 1 DFNNFLB EFDCOCXAOBV BAAG JLLG OFG"));
    solver.setHeadline(5, new Headline("LVTSYRRB HGSFG VISFVAS 3.74 ESAFSSG RL GSCVFVUORX"));

    Alphabet alpha;
    alpha.setAlphabet("EDQZMHUTCPYBKXNJWLFROIVAGS");
    solver.setAlphabet(alpha);

    solver.solveAllUsingAlphabet();

    Menu menu;
    menu.mainMenu();

    return 0;
}
