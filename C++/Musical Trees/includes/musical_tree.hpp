#ifndef MUSICAL_TREE_HPP
#define MUSICAL_TREE_HPP

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "motif_node.hpp"

using namespace std;

class MusicalTree {
public:
  //------------------REQUIRED------------------------
  // REQUIRES:
  // MODIFIES: This MusicalTree
  // EFFECTS : Initializes the MusicalTree with a root node
  // Part 1
  MusicalTree(bool verbose);

  // REQUIRES: This MusicalTree is valid
  // MODIFIES: This MusicalTree
  // EFFECTS : Runs the entire genetic algorithm by evolving and pruning the
  //           tree per the number of generations passed in
  void GeneticAlgorithm(int numGenerations);

  // REQUIRES: This MusicalTree is valid
  // MODIFIES:
  // EFFECTS : Returns a single vector of all the motifs in the tree
  std::vector<Note> GenerateMelody();

  // REQUIRES: This MusicalTree is valid
  // MODIFIES: This MusicalTree
  // EFFECTS : Removes all nodes from the tree that have a motif with a fitness
  // level below the threshold. See specifications for exact algorithm required.
  // If tree is the root and tree has no children, do nothing. 
  // DO NOT check the size_ in this function (it will break the autograder)
  // However, you may and should update the size_ in this function.
  // Part 1
  void PruneNodes(MotifNode* tree, double threshold);

  // Part 1
  ~MusicalTree();

  //copy
  MusicalTree(const MusicalTree& tree);

  //assignment
  MusicalTree& operator=(const MusicalTree& tree);

  // USED FOR TESTING, already implemented
  MotifNode* GetRoot() const {return root_;}
  int GetSize() const { return size_; }

  //----------------------------------------------------
  // Add more functions here

private:
  //--------A few recommended functions below-----------

  // REQUIRES: This MusicalTree is valid
  // MODIFIES:
  // EFFECTS : This function validates that the tree starting at root is valid.
  //           I recommend using this function to debug your code.
  void ValidateTree(MotifNode* node);

  // REQUIRES: This MusicalTree is valid
  // MODIFIES: melody
  // EFFECTS : Traverses the tree and adds motifs to the melody
  //           hint: This is a helper function for implementing
  //                 GenerateMelody()
  void TraverseTree(MotifNode* node, vector<Note>& melody);

  //helper function for destructor
  void PopAll(MotifNode* tree) {
    for (int i = 0; i < tree->GetChildren().size(); i++) {
      PopAll(tree->GetChildren()[i]);
    }
    delete tree;
  }

  //recursive helper function for copy constructor
  MotifNode* CopyMotifNodes(MotifNode* node) {
    MotifNode* to_return = new MotifNode(node->GetMotif());
    to_return->SetFitnessScore(node->GetFitnessScore());
    for (int i = 0; i < node->GetChildren().size(); i++) {
      to_return->AddChildNode(CopyMotifNodes(node->GetChildren()[i]));
    }
    return to_return;
  }

  //recursive helper for selection process
  void SelectNodes(MotifNode* node, double sp, vector<MotifNode*>& nodes, bool verbose) {
    if (verbose) {
      cout << "node: ";
      for (int i = 0; i < node->GetMotif().size(); i++) {
        cout << node->GetMotif()[i].pitch << "-" << node->GetMotif()[i].duration << " ";
      }
      cout << endl;
      cout << "Fitness_Score: " << node->GetFitnessScore() << endl;

      cout << "  Selection Prob: " << sp << endl;
    }

    if(sp < max((node->GetFitnessScore())/100, 0.10)) {
      nodes.push_back(node);
      if (verbose) cout << "  Selected" << endl;
    } else {
      if (verbose) cout << "  Not Selected" << endl;
    }

    for (MotifNode* child : node->GetChildren()) {
      SelectNodes(child, sp, nodes, verbose);
    }
  }

  //recursvie helper for reproduction
  void mutate(MotifNode*& node) {

    //ideas for improvement from Robyn Nemeth
    
    //standardize octave
    //uniform rhythm
    //on and off beats - ratios of intervals
    //divide each note by a standardized number (0.05s)
    //if it's not a sixteenth, eighth, quarter, etc. (a note), then it's bad
    //if it jumps from 60 to 66, then the next one can't go back to 60, the furthest it can go back is 63, works other way as well

    // steps (for future, not this extra credit):
    // instead of adding random pitch or duration, do it like this:
    // add +2/-2 pitch to nearest octave note, or exact amount if distance < 2
    // add exact duration to nearest whole/half/etc. note, or add -0.1/0.1


    srand(time(NULL));
    vector<Note> parent_motif = node->GetMotif();
    vector<Note> new_motif;

    for (Note note : node->GetMotif()) { //create new motif based on parent motif
      int pitch_to_add = 0;
      int rp = (rand() % 5) - 2; //random pitch from [-2, 2]
      double rd = ((static_cast<double>(rand()) / RAND_MAX) * 0.2) - 0.1; //random duration from [-0.1, 0.1]
      int np = note.pitch + rp;
      double nd = note.duration + rd;

      //check for mins and maxes
      if (np > 127) np = 127;
      else if (np < 0) np = 0;
      if (nd > 0.7) nd = 0.7;
      else if(nd < 0.1) nd = 0.1;

      //add note
      Note to_add(np, nd);
      new_motif.push_back(to_add);
    }

    MotifNode* new_child = new MotifNode(new_motif); //create new child using mutated motif
    node->AddChildNode(new_child);
    size_++;
  }

  //-------------- REQUIRED -------------------------
  MotifNode* root_;
  int size_;
  bool verbose_;
  //----------------------------------------------------
};

#endif
