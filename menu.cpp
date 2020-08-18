#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include "solver.h"
#include "headline.h"
#include "alphabet.h"
#include "common.h"

#include "menu.h"

using namespace std;


Menu::Menu() {
    solver = new Solver();
}

Menu::~Menu() {
    delete solver;
}

void Menu::mainMenu() {
    vector<string> options = {
        "Enter headlines",
        "Enter alphabet",
        "Solve individual headline based on word patterns",
        "Decimate alphabet",
        "Solve all headlines using given alphabet",
        "Find hat in dictionary",
        "Find hat in file",
        "Exit"
    };

    int choice = 0;

    while (choice != options.size()) {
        for (int i=0; i<options.size(); i++) {
            cout << "[" << i+1 << "] " << options[i] << "\n";
        }

        string entry;
        cout << "Please enter menu option: ";
        getline(cin, entry);
        istringstream instr(entry);
        instr >> choice;
        if (choice > options.size() || options.size() < 1) {
            cout << RED << "Invalid choice, please try again.\n" << DEFAULT;
        } else {
            switch(choice) {
                case 1:
                    setHeadlines();
                    break;
                case 2:
                    setAlphabet();
                    break;
                case 3:
                    guessHeadline();
                    break;
                case 4:
                    decimateAlphabet();
                    break;
                case 5:
                    solveUsingAlphabet();
                    break;
                case 6:
                    findHatInDict();
                    break;
                case 7:
                    findHatInFile();
                    break;
                default:
                    cout << GREEN << "Thanks for playing!\n" << DEFAULT;
                    exit(0);
            }
        }
    }
}

void Menu::setHeadlines() {

    string headline;

    for (int i=1; i<6; i++) {
        cout << "Please enter enciphered headline " << i << ": ";
        getline(cin, headline);
        solver->setHeadline(i, new Headline(headline));
    }

    cout << "All five headlines have been set\n";
}

void Menu::setAlphabet() {

    Alphabet alpha;
    string lets;
    while (! alpha.setAlphabet(lets)) {
        cout << "Please enter valid alphabet: ";
        getline(cin, lets);
    }

    solver->setAlphabet(alpha);

    cout << "Alphabet has been set.\n";
}

void Menu::solveUsingAlphabet() {
    cout << "Solve using alphabet\n";

    // check that headlines are filled in
    // should be enough to just check the first one
    if (solver->getHeadline(1) == NULL) {
        cout << "Please first enter the five headlines.\n";
        setHeadlines();
    }

    // check that alphabet is filled in
    if (solver->getAlphabet().getOffset(0) == "") {
        cout << "Please first enter the alphabet to use.\n";
        setAlphabet();
    }

    solver->solveAllUsingAlphabet();
}

void Menu::guessHeadline() {
    if (solver->getHeadline(1) == NULL) {
        cout << "Please first enter the five headlines.\n";
        setHeadlines();
    }

    cout << "Which headline would you like to solve? (1-5) ";
    string ans;
    int choice = 0;
    getline(cin, ans);
    istringstream instr(ans);
    instr >> choice;

    solver->guessHeadlinePlain(choice);
    cout << "\n\n";

}

void Menu::decimateAlphabet() {
    if (solver->getAlphabet().getOffset(0) == "") {
        cout << "Please first enter the alphabet to use.\n";
        setAlphabet();
    }
    vector<int> offsets = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};
    string yellows = "UVW";
    string reds = "XYZ";

    for (int i=0; i<offsets.size(); i++) {
        string alpha = solver->getAlphabet().decimate(offsets[i]);
        for (int j=0; j<alpha.length(); j++) {
            if (yellows.find(alpha[j]) != string::npos) {
                cout << " " << YELLOW << alpha[j] << DEFAULT;
            } else if (reds.find(alpha[j]) != string::npos) {
                cout << " " << RED << alpha[j] << DEFAULT;
            } else {
                cout << " " << alpha[j];
            }
        }
        cout << "\n";
    }
    cout << "\n";

}

void Menu::findHatInDict() {
    string order;
    cout << "Enter pattern of hat (starting with 0!): ";
    getline(cin, order);

    // import orders.txt
    map<string, vector<string> > orders;
    ifstream orders_dict("orders.txt");
    string line;
    string key;
    string word;

    while (getline(orders_dict, line)) {
        istringstream s(line);
        s >> key;
        orders.insert(make_pair(key, vector<string>()));

        while (s >> word) {
            orders[key].push_back(word);
        }
    }
    orders_dict.close();

    if (orders.find(order) != orders.end()) {
        for(int i=0; i<orders[order].size(); i++) {
            cout << orders[order][i] << "\n";
        }
    } else {
        cout << "No matches found.\n";
    }

}

void Menu::findHatInFile() {

}
