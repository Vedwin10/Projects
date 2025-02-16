#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "motif_node.hpp"

using namespace std;

// This function is written for you. I recommend not changing it until 
// you are done with the MP. 
double CalculateHarmonicScore(const vector<Note>& motif) {

  //ideas for improvement from Robyn Nemeth
    
  //standardize octave
  //uniform rhythm
  //on and off beats - ratios of intervals
  //divide each note by a standardized number (0.05s)
  //if it's not a sixteenth, eighth, quarter, etc. (a note), then it's bad
  //if I jumpt from 60 to 66, then the next one can't go back to 60, the furthest it can go back is 63; note: goes both ways

  //steps to improve:
  // 1. get rid of randomness and actually penalize/reward  //DONE
  // 2. keep octave equivalence, interval, and pitch loops //DONE
  // 3. add the timing/duration of the notes check (standardize time, and penalize if it's on an off beat) //DONE
  // 4. penalize for extra jumps or anything like that //DONE



  //start with score 0
  double harmonic_score = 0.0;

  //if the note is C, D, E, F, G, A, B add 0-9, else subtract 0-9
  for (int i = 0; i < motif.size(); ++i) {
    int note_ = motif[i].pitch % 12;  // Modulo 12 for octave equivalence
    // C major notes
    if (note_ == 0 || note_ == 2 || note_ == 4 || note_ == 5 || note_ == 7 ||
        note_ == 9 || note_ == 11) {
      harmonic_score += 10; //add 10 instead of random 0-9
    }
    // other notes 
    else {
      harmonic_score -= 10; //subtract 10 instead of random 0-9
    }
  }

  //if interval is minor second, tritone, or minor seventh, punish, if interval is perfect fifth, major fourth, major seventh, reward
  for (int i = 1; i < motif.size(); ++i) {
    int interval = abs(motif[i].pitch - motif[i - 1].pitch) % 12;  // Modulo 12 for octave equivalence
    // bad sounding intervals
    if (interval == 1 || interval == 6 || interval == 10) {
      harmonic_score -= 10; // subtract 10 instead of 0-9
    } 
    // good sounding intervals
    else if (interval == 7 || interval == 5 || interval == 4) {
      harmonic_score += 10; // add 10 instead of 0-9
    }
  }

  // Incentive motifs have nice pitches
  // if interval is outside 60-72, penalize. If interval is outside 50-80, penalize again.
  for (const auto& note : motif) {
    if (note.pitch < kMinAcceptablePitch || note.pitch > kMaxAcceptablePitch) {
      harmonic_score -= 10;  // Penalize motifs with pitches outside the acceptable range; subtract 10 instead of 0-9
    }
    if (note.pitch < kExtrMinAcceptablePitch ||
        note.pitch > kExtrMaxAcceptablePitch) {
      harmonic_score -= 20;  // Penalize motifs with pitches outside the acceptable range; subtract 10 instead of 0-9
    }
  }

  //check durations of notes
  // whole note = 0.7 seconds
  // half note = 0.35 seconds
  // quarter note = 0.175 seconds
  // eighth note = 0.0875 seconds
  // sixteenth note = 0.04375 seconds
  double whole_note = 0.7;
  double half_note = whole_note/2;
  double quarter_note = whole_note/4;
  double eighth_note = whole_note/8;
  double sixteenth_note = whole_note/16;

  //check for these durations and lengths
  for (int i = 0; i < motif.size(); ++i) {
    int duration = motif[i].duration; 

    //if duration is some good note length, reward
    if (duration == whole_note || duration == half_note || duration == quarter_note || duration == eighth_note || duration == sixteenth_note) {
      harmonic_score += 10;
    } else { //else, penalize
      harmonic_score -= 10;
    }
  }

  //now check for jumps in intervals
  for (int i = 2; i < motif.size(); ++i) {
    int interval1 = motif[i-2].pitch - motif[i-1].pitch;
    int interval2 = motif[i-1].pitch - motif[i].pitch;
    // bad jumps (first jump is 6, then next is more than 3)
    if (interval1 < 0 && interval2 > 0) { //this means the note jumped, then dropped
      if (abs(interval2) > (interval1/2)) { //if it dropped more than half of what it jumped, penalize
        harmonic_score -=10;
      }
    } else if (interval1 > 0 && interval2 < 0) { //this means note dropped, then jumped
      if (abs(interval1) > (interval1/2)) { //if it jumped more than half of what it dropped, penalize
        harmonic_score -=10;
      }
    }
  }

  return harmonic_score;
}

double CalculateFitnessScore(const vector<Note>& motif) {
  int n = 6;
  double harmonic_score = CalculateHarmonicScore(motif);
  double worst_score_possible = -280.0;
  double best_score_possible = 170.0;
  double normalized_score = (harmonic_score - worst_score_possible) / (best_score_possible - worst_score_possible) * 100;
  return normalized_score;
}

MotifNode::MotifNode(const vector<Note>& motif) {
  motif_ = motif;
  fitness_score_ = CalculateFitnessScore(motif);
  children_ = {};
  parent_ = nullptr;
}

void MotifNode::AddChildNode(MotifNode* new_child) {
  children_.push_back(new_child);
  new_child->parent_ = this;
}

bool MotifNode::ReplaceChildNode(MotifNode* new_child, MotifNode* old_child) {
  for (int i = 0; i < children_.size(); i++) {
    if (children_[i] == old_child) {
      children_[i] = new_child;
      new_child->parent_ = this;
      return true;
    }
  }
  return false;
}

bool MotifNode::RemoveChildNode(MotifNode* node) {
  for (int i = 0; i < children_.size(); i++) {
    if (children_[i] == node) {
      children_.erase(children_.begin() + i);
      return true;
    }
  }
  return false;
}

void MotifNode::SetNullParent() {
  parent_ = nullptr;
}

MotifNode* MotifNode::GetParentNode() const {
  return parent_;
}

const vector<Note>& MotifNode::GetMotif() const {
  return motif_;
}

const vector<MotifNode*>& MotifNode::GetChildren() const {
  return children_;
}

double MotifNode::GetFitnessScore() const {
  return fitness_score_;
}

void MotifNode::SetFitnessScore(double val) {
  fitness_score_ = val;
}