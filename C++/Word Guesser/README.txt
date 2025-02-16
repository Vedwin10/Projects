This code was based on a project designed by Jule Schatz and a project by Keith Schwarz

"driver.cc" contains a simple version of the game, which requires the user to guess a word that was randomly chosen from a pre-set dictionary of words.
"driver_full.cc" contains a more complex version of the game with an "evil" mode. The "evil" mode works like this:

The user is asked to select the length of the word. For example, 5.
The program will select all of the words in the dictionary with the length 5, and put them into a vector.
The user will then put in their first guess, for example, 'a'
The program will then parse the vector and split it into sections based on where the character 'a' occurs in all of the words. For example, some sections might be:
    'a' as the first letter
    'a' as the third letter
    'a' as the second and fourth letter
    no 'a' in the word
Each of these sections contain a vector of words that fall in the same section. The program then makes the section with the largest size the new vector of words to guess from.
The program keeps reducing the vector of words to guess from until it has only one word left, or until the user misses 5 times. 