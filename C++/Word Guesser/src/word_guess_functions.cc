#include "word_guess_functions.hpp"

using namespace std;

// REQUIRES: size to be a value between 2 and 10 (including 2 and 10).
// MODIFIES:
// EFFECTS: Out of the words from kDictionaryFile that are of length size,
//          this function returns one of them randomly selected using
//          srand(random_seed) to initialize the random number generator.
string PickWord(unsigned int size, int random_seed) {
  // We won't go over how to read in information from a file until later in the
  // course. Therefore, I have added in the code that opens and reads from a
  // file, one word at a time. It's up to you to implement the rest of the
  // function. This is a great chance to practice your code reading and problem
  // solving skills!

  srand(random_seed);

  vector<string> vect;

  // opens file
  ifstream f_in(kDictionaryFile);

  // Checks that the file was opened correctly
  if (!f_in) {
    std::cerr << "Error: Unable to open file " << kDictionaryFile << std::endl;
    return " ";
  }

  // Reads in one word at a time until the end of the file
  string word;
  while (f_in >> word) {
    if (size == word.length()) {
      vect.push_back(word);
    }
  }

  return vect[rand() % vect.size()];

}

// REQUIRES: guessed_letters only has valid guesses, aka lowercase letters
// MODIFIES:
// EFFECTS: Returns true if guess is valid. Guess is valid if it is
//          a lowercase letter that is not in guessed_letters.
bool GuessValid(char guess, vector<char> guessed_letters) {

  if ((int)guess < 97 || (int)guess > 122) {
    return false;
  }
  
  for (int i = 0; i < guessed_letters.size(); i++) {
    if (guess == guessed_letters[i]) {
      return false;
    }
  }

  return true;

}

// REQUIRES: size is greater than 0.
// MODIFIES:
// EFFECTS: Returns a string of length size that consists of '-' characters
//          only.
string GetBlankWord(unsigned int size) {
  
  string x;
  for (int i = 0; i < size; i++) {
    x += "-";
  }

  return x;
  
}

// REQUIRES:
// MODIFIES:
// EFFECTS: Returns true if word has no '-' characters in it.
bool WordCompleted(const string& word) {
  
  for (int i = 0; i < word.length(); i++) {
    if (word[i] == '-') {
      return false;
    }
  }

  return true;

}

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Prints to standard output the current state of the game. 
void PrintState(const string& mystery_word_so_far, unsigned int misses) {
  cout << endl;
  cout << "--- Current State --- " << endl;

  cout << "You have " << kMaxMisses - misses << " lives left." << endl;
  cout << "Word: ";
  for (unsigned int i = 0; i < mystery_word_so_far.length(); i++) {
    cout << mystery_word_so_far[i] << " ";
  }
  cout << endl;
  cout << endl;
}

// REQUIRES:
// MODIFIES: cout, cin
// EFFECTS: Returns a number between (1, 10] from the user.
int GetLengthOfWord() { 

  int length;
  cout << "Enter a word length: ";
  cin >> length;

  while (length < 2 || length > 10) {
    cout << "Invalid length. Please enter a length between (1, 10] : ";
    cin >> length;
  }

  return length;

}

// REQUIRES:
// MODIFIES: cout, cin
// EFFECTS: Returns a lowercase letter not in guessed_letters from the user.
char GetNextGuess(const vector<char>& guessed_letters) { 

  char next_guess = ' ';
  cout << "What is your next guess? " << endl;
  cin >> next_guess;

  while (!GuessValid(next_guess, guessed_letters)) {
    cout << "Invalid guess. Please enter a lowercase letter that you have not guessed yet : " << endl;
    cin >> next_guess;
  }

  return next_guess;

}

// REQUIRES:
// MODIFIES: cout, word_so_far
// EFFECTS: If the guess is in the word, the function updates word_so_far to
//          replace any "-" with the guessed letter. The function returns true
//          if the guess is in the word. Additionally, it calls GuessFeedback to
//          print out feedback to the user
bool CheckWordForGuess(string& word_so_far, string word, char guess) {
  
  bool is_in_word = false;
  for (int i = 0; i < word.length(); i++) {
    if (guess == word[i]) {
      is_in_word = true;
      word_so_far[i] = guess;
    }
  }

  GuessFeedback(is_in_word, guess);
  return is_in_word;

}

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Prints feedback to the user if the guess is in the word.
void GuessFeedback(bool correct_guess, char guess) {

  if (correct_guess) {
    cout << "The letter \'" << guess << "\' is in the word!" << endl;
  } else  {
    cout << "The letter \'" << guess << "\' is not in the word." << endl;
  }

}

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Returns true if word_so_far has no '-' characters or if misses
//          equals kMaxMisses. In both cases it also prints out feedback.
bool CheckEndConditions(const string& word_so_far, unsigned int misses, const string& solution) {

  if (misses == kMaxMisses) {
    cout << "You used up your last guess and lost!" << endl;
    cout << "The word was, " << solution << "." << endl;
    return true;
  }

  if (WordCompleted(word_so_far)) {
    cout << "You win! You guessed the word, " << word_so_far << "." << endl;
    return true;
  }

  return false;

}
