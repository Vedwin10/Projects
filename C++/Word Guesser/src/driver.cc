#include "word_guess_functions.hpp"

using namespace std;

// Small version of game with normal mode and no evil algorithm

int main() {
    
    int word_length = GetLengthOfWord();
    string word_to_guess = PickWord(word_length, kRandomSeed);
    string guessed_word = GetBlankWord(word_length);
    int misses = 0;
    char next_guess = ' ';
    vector<char> guessed_letters = {};
    bool game_over = CheckEndConditions(guessed_word, misses, word_to_guess);

    while (!game_over) {
        PrintState(guessed_word, misses);
        game_over = CheckEndConditions(guessed_word, misses, word_to_guess);
        if (game_over) {
            break;
        }
        next_guess = GetNextGuess(guessed_letters);
        guessed_letters.push_back(next_guess);
        if (!CheckWordForGuess(guessed_word, word_to_guess, next_guess)) {
            misses++;
        }
    }

}
