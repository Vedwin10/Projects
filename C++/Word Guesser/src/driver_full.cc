//ADD include statements needed here

#include "word_guess_functions.hpp"

#include <map>

using namespace std;

void NeutralGame() {

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

vector<string> PickWords(unsigned int size) {

  // TODO init variables you need
  vector<string> vect;

  // opens file with the name, kDictionaryFile
  ifstream f_in(kDictionaryFile);

  // Checks that the file was opened correctly
  if (!f_in) {
    std::cerr << "Error: Unable to open file " << kDictionaryFile << std::endl;
    return {" "};
  }

  // Reads in one word at a time until the end of the file
  string word;
  while (f_in >> word) {
    if (size == word.length()) {
      vect.push_back(word);
    }
  }

  return vect;

}

// Checks if game is over in evil mode
bool CheckEndConditionsEvil(const string& word_so_far, unsigned int misses, vector<string> solutions) {

  if (misses == kMaxMisses) {
    cout << "You used up your last guess and lost!" << endl;
    cout << "The word was, " << solutions[0] << "." << endl;
    return true;
  }

  if (WordCompleted(word_so_far)) {
    cout << "You win! You guessed the word, " << word_so_far << "." << endl;
    return true;
  }

  return false;

}

// function that returns vector of new solutions
vector<string> GetNewSolutions(char guess, const int word_length, vector<string> solutions) {

  map<string, vector<string>> myMap = {};
  string key = "";
  vector<string> toReturn = {};

  for (int i = 0; i < solutions.size(); i++) {
    key = "";
    for (int j = 0; j < solutions[i].length(); j++) {
      if (solutions[i][j] == guess) {
        key += guess;
      } else {
        key += "-";
      }
    }
    if (myMap.find(key) == myMap.end()) {
      myMap.insert({key, {solutions[i]}});
    } else {
      myMap[key].push_back(solutions[i]);
    }
  }

  string x = "";
  for(int i=0;i<word_length;i++) {
    x+="-";
  }
  toReturn = myMap[x];
  for (const auto& element : myMap) {
    if (element.second.size() > toReturn.size()) {
      toReturn = element.second;
    }
  }

  return toReturn;

}

// function that checks guess in evil mode
bool CheckWordForGuessEvil(string& word_so_far, vector<string>& words, char guess) {

  words = GetNewSolutions(guess, word_so_far.length(), words);
  string sample_from_subset = words[0];
  bool is_in_word = false;

  for (int i = 0; i < sample_from_subset.length(); i++) {
    if (guess == sample_from_subset[i]) {
      is_in_word = true;
      word_so_far[i] = guess;
    }
  }

  GuessFeedback(is_in_word, guess);
  return is_in_word;

}


// cout statements
// cout << "Select a mode, neutral or evil : ";
// cout << "Invalid. Please pick neutral, or evil : ";
string SelectMode() {

    string mode;
    cout << "Select a mode, neutral or evil : ";
    cin >> mode;

    while (mode != "neutral" && mode != "evil") {
        cout << "Invalid. Please pick neutral, or evil : ";
        cin >> mode;
    }

    return mode;

}

int main() { 
    
    string mode = SelectMode(); 

    if (mode == "neutral") {
        NeutralGame();
    } else {
        int word_length = GetLengthOfWord();
        vector<string> words_to_guess = PickWords(word_length);
        string guessed_word = GetBlankWord(word_length);
        int misses = 0;
        char next_guess = ' ';
        vector<char> guessed_letters = {};
        bool game_over = CheckEndConditionsEvil(guessed_word, misses, words_to_guess);

        while(!game_over) {
            PrintState(guessed_word, misses);
            game_over = CheckEndConditionsEvil(guessed_word, misses, words_to_guess);
            if (game_over) break;
            next_guess = GetNextGuess(guessed_letters);
            guessed_letters.push_back(next_guess);
            if (!CheckWordForGuessEvil(guessed_word, words_to_guess, next_guess)) {
                misses++;
            }
        }

    }

}
