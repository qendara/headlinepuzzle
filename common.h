#ifndef COMMON_H
#define COMMON_H

#include <string>

using namespace std;

bool isAlpha(char c); 
bool isNotAlpha(char c);
bool isEmpty(string s);

string create_pattern(string word);
string create_order(string word);

char upper(char s);
char lower(char s);
string upper_word(string s);
string lower_word(string s);

string spaced(string str);

const string RED = "\e[31m";
const string GREEN = "\e[38;5;47m";
const string YELLOW = "\e[33m";
const string BLUE = "\e[38;5;27m";
const string MAGENTA = "\e[38;5;213m";
const string CYAN = "\e[36m";
const string DEFAULT = "\e[39m";

#endif
