#ifndef WORD_GUESS_FUNCTIONS_HPP
#define WORD_GUESS_FUNCTIONS_HPP

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <map>

#include "word_guess_constants.hpp"

using namespace std;

// REQUIRES: size to be a value between 2 and 10 (including 2 and 10).
// MODIFIES:
// EFFECTS: Out of the words from kDictionaryFile that are of length size,
//          this function returns one of them randomly selected using
//          srand(random_seed) to initialize the random number generator.

string PickWord(unsigned int size, int random_seed);

// REQUIRES: guessed_letters only has valid guesses, aka lowercase letters
// MODIFIES:
// EFFECTS: Returns true if guess is valid. Guess is valid if it is
//          a lowercase letter that is not in guessed_letters.
bool GuessValid(char guess, vector<char> guessed_letters);

// REQUIRES: size is greater than 0.
// MODIFIES:
// EFFECTS: Returns a string of length size that consists of '-' characters
//          only.
string GetBlankWord(unsigned int size);

// REQUIRES:
// MODIFIES:
// EFFECTS: Returns true if word has no '-' characters in it.
bool WordCompleted(const string& word);

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Prints to standard output the current state of the game.
void PrintState(const string& mystery_word_so_far, unsigned int misses);

// REQUIRES:
// MODIFIES: cout, cin
// EFFECTS: Returns a number between (1, 10] from the user.
int GetLengthOfWord();

// REQUIRES:
// MODIFIES: cout, cin
// EFFECTS: Returns a lowercase letter not in guessed_letters from the user.
char GetNextGuess(const vector<char>& guessed_letters);

// REQUIRES:
// MODIFIES: cout, word_so_far
// EFFECTS: If the guess is in the word, the function updates word_so_far to
//          replace any "-" with the guessed letter. The function returns true
//          if the guess is in the word. Additionally, it calls GuessFeedback to
//          print out feedback to the user
bool CheckWordForGuess(string& word_so_far, string word, char guess);

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Prints feedback to the user if the guess is in the word.
void GuessFeedback(bool correct_guess, char guess);

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Returns true if word_so_far has no '-' characters or if misses
//          equals kMaxMisses. In both cases it also prints out feedback.
bool CheckEndConditions(const string& word_so_far,
                        unsigned int misses,
                        const string& solution);

// runs the game mode neutral based on the code for Part 1 in driver.cc
void NeutralGame();

// returns a vector full of words of length size
vector<string> PickWords(unsigned int size);

// check if the game is over on evil mode
bool CheckEndConditionsEvil(const string& word_so_far, unsigned int misses, vector<string> solutions);

// function that returns vector full of new solutions
vector<string> GetNewSolutions(char guess, const int word_length, vector<string> solutions);

// check word for guess evil version
bool CheckWordForGuessEvil(string& word_so_far, vector<string>& words, char guess);

#endif
