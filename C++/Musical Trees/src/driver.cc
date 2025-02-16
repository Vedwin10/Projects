#include "musical_tree.hpp"
#include "utilities.hpp"

int main() {
  // Create MelodyGenerator object
  MusicalTree mt(false);
  GenerateMP3(mt.GenerateMelody(), "starting.mp3");

  std::vector<Note> melody = mt.GenerateMelody();
  for (const auto& note : melody) {
    std::cout << note.pitch << "-" << note.duration << " ";
  }
  cout << std::endl;

  // Evolve the tree structure for a fixed number of generations
  mt.GeneticAlgorithm(150);

  // Generate melody by traversing the evolved tree structure
  melody = mt.GenerateMelody();
  for (const auto& note : melody) {
    std::cout << note.pitch << "-" << note.duration << " ";
  }
  cout << std::endl;

  // Generage MP3 based on melody vector
  GenerateMP3(melody, "output.mp3");

}
