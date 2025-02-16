#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "musical_tree.hpp"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Part 1
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



MusicalTree::MusicalTree(bool verbose) {
    srand((time(NULL)));
    verbose_ = verbose;
    size_ = 1;
    vector<Note> motifs;
    for (int i = 0; i < 6; i++) {
        int random_pitch = rand() % 128;
        double random_duration = 0.1 + (static_cast<double>(rand()) / (RAND_MAX / 0.6));
        Note n(random_pitch, random_duration);
        motifs.push_back(n);
    }
    root_ = new MotifNode(motifs);
}

void MusicalTree::PruneNodes(MotifNode* tree, double threshold) {
    if (root_->GetChildren().empty()) return; //do nothing is root has no children
    int children_size = static_cast<int>(tree->GetChildren().size())-1;
    for (int i = children_size; i >= 0; i--) {
        PruneNodes(tree->GetChildren()[i], threshold);
    }

    if (tree->GetFitnessScore() < threshold) {
        if (tree->GetChildren().empty()) { //leaf node (no children) can't be root because a root with no children means size=1
            if (tree->GetParentNode() != nullptr) {
                tree->GetParentNode()->RemoveChildNode(tree);
                size_--;
                delete tree;
            }
        } else { //any node (could be root) with children
            MotifNode* last = tree->GetChildren()[tree->GetChildren().size()-1];
            if (tree != root_) { //the node is also a child of some parent
                tree->GetParentNode()->ReplaceChildNode(last, tree);
            } else {
                last->SetNullParent();
                root_ = last;
            }
            for (int i = 0; i < tree->GetChildren().size()-1; i++) { //add tree's children to new parent (except new parent itself)
                last->AddChildNode(tree->GetChildren()[i]);
            }
            delete tree;
            size_--;
        }
    }
}

//Big Three
//Destructor
MusicalTree::~MusicalTree() {
    PopAll(root_);
}

//Copy Constructor
MusicalTree::MusicalTree(const MusicalTree& tree) {
    size_ = tree.size_;
    verbose_ = tree.verbose_;

    root_ = CopyMotifNodes(tree.root_);
}

//Assignment Operator
MusicalTree& MusicalTree::operator=(const MusicalTree& tree) {
    if (this == &tree) return *this;

    PopAll(root_);

    size_ = tree.size_;
    verbose_ = tree.verbose_;

    root_ = CopyMotifNodes(tree.root_);

    return *this;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Part 2
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Runs the entire genetic algorithm by evolving and pruning the tree per the number of generations passed in
void MusicalTree::GeneticAlgorithm(int numGenerations) {
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //Pre-Evolution--------------------------------------------------------------------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    srand(time(NULL));
    double s_p = static_cast<double>(rand()) / RAND_MAX;
    vector<MotifNode*> selection;
    double threshold;

    for (int i = 0; i < 2; i++) { //EVOLVE 2 times
        if (verbose_) cout << "EVOLVE" << endl;

        //SELECTION
        if (verbose_) cout << "SelectNodes: " << endl;

        selection.clear();
        SelectNodes(root_, s_p, selection, verbose_);

        //REPRODUCTION
        for (MotifNode* node : selection) {
            if (verbose_) {
                cout << "Reproduce: ";
                for (unsigned int j = 0; j < node->GetMotif().size(); j++) {
                    cout << node->GetMotif()[j].pitch << "-" << node->GetMotif()[j].duration << " ";
                }
                cout << endl;
            }

            mutate(node);

            if (verbose_) {
                MotifNode* created_child = node->GetChildren()[node->GetChildren().size()-1];
                vector<Note> child_motif = created_child->GetMotif();
                cout << " Child: ";
                for (unsigned int j = 0; j < child_motif.size(); j++) {
                    cout << child_motif[j].pitch << "-" << child_motif[j].duration << " ";
                }
                cout << endl;
            }
        }

    } //Pre-evolution finished

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //Generations----------------------------------------------------------------------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    for (int i = 0; i < numGenerations; i++) {
        if (verbose_) cout << "GEN " << i << " size: " << size_ << endl;


        //EVOLVE

        s_p = static_cast<double>(rand()) / RAND_MAX;

        for (int j = 0; j < 4; j++) { //EVOLVE 4 times
            if (verbose_) cout << "EVOLVE" << endl;

            //SELECTION
            if (verbose_) cout << "SelectNodes: " << endl;

            selection.clear();
            SelectNodes(root_, s_p, selection, verbose_);

            //REPRODUCTION
            for (MotifNode* node : selection) {
                if (verbose_) {
                    cout << "Reproduce: ";
                    for (unsigned int k = 0; k < node->GetMotif().size(); k++) {
                        cout << node->GetMotif()[k].pitch << "-" << node->GetMotif()[k].duration << " ";
                    }
                    cout << endl;
                }

                mutate(node);

                if (verbose_) {
                    MotifNode* created_child = node->GetChildren()[node->GetChildren().size()-1];
                    vector<Note> child_motif = created_child->GetMotif();
                    cout << " Child: ";
                    for (unsigned int k = 0; k < child_motif.size(); k++) {
                        cout << child_motif[k].pitch << "-" << child_motif[k].duration << " ";
                    }
                    cout << endl;
                }
            }

        } //evolution finished

        //PRUNE
        if (verbose_) {
            cout << "PRUNE " << endl;
            cout << " size: " << size_ << endl;
        }

        threshold = 10;
        while(size_ > 200) {
            PruneNodes(root_, threshold);
            if (verbose_) {
                cout << "  prune cutoff: " << threshold << endl;
                cout << "  size: " << size_ << endl;
            }
            threshold++;
        }

    }

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //Final Prune----------------------------------------------------------------------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    if (verbose_) cout << "Final Prune " << size_ << endl;

    //reduce to 1-2 nodes
    while(size_ > 2) {
        PruneNodes(root_, threshold);
        threshold += 0.01;
    }

}

//Returns a single vector of all the motifs in the tree
vector<Note> MusicalTree::GenerateMelody() {
    vector<Note> to_return;
    for (Note note : root_->GetMotif()) {
        to_return.push_back(note);
    }
    if(root_->GetChildren().size() == 1) {
        for (Note note : root_->GetChildren()[0]->GetMotif()) {
            to_return.push_back(note);
        }
    }
    return to_return;
}