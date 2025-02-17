This project uses trees and nodes containing musical notes to tweak and modify an .mp3 file to sound "musically better."

The MotifNode class is a class that holds 6 notes (called a motif), each note being a struct with a duration and a pitch, a fitness score which describes how good the motif sounds, 
pointers to its children in the tree, and a pointer to its parent. 
Using MotifNodes, the MusicalTree class implements a genetic algorithm that works like a survival-of-the-fittest concept. The algorithm has 3 phases:

1. Pre-Evolution: Selection + Reproduction
2. Generation (with X a paramater for how many times we want to run generations): Evolution + Pruning
3. Final Prune

- Selection: Traverses every node in the tree and selects on those who have a fitness score above a certain threshold (only these will have the algorithm run on them)
- Reproduction: Creates new children by adding/subtracting random values to pitch and duration, and their fitness score is recalculated
- Pruning: Recursively go through the tree and remove children that fall below a certain threshold, unless they are the root node

This projects focuses on Managing dynamic memory through classes, as well as recursion with complex structures. 

Credits for this project go to Jule Schatz for inspiration, as well as Robyn Nemeth, a music ed major at Frost School of Music (for helping implementing fitness score calculation)