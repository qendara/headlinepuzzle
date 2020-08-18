# headlinepuzzle

This repo is a collection of code written to help me solve the [Headline Puzzle](https://www.thephoenixsociety.org/cryptogram.html). Most of the code is part of the actual solver, but a few files are written to help generate the .txt files used by the solver. I have included the txt files here, so you don't have to generate them yourself, but you can if you want to.

## create_patterns.cpp
This program will create the file patterns.txt, which consists of lines of the form "PATTERN WORD [WORD ...]". These patterns are useful when looking at the ciphered word and trying to generate a list of possible plaintext words for it.

## create_pair_scores.cpp
This program looks at previously solved puzzles (past_answers.txt) and generates diletter scores based on their frequency, saved in file pair_scores.txt. These "pair scores" are useful when scoring possible headline translations with a given alphabet.

## create_orders.cpp
This program will create the file orders.txt, which consists of lines of the form "ORDER WORD [WORD ...]". These orders are useful when solving the hat, since you know the order of the letters in the word.


## Dependencies
This code (mainly the helper code, not the solver) relies on the Ubuntu list of words found at /usr/share/dict/american-english. Please modify this path for the word list on other operating systems.
