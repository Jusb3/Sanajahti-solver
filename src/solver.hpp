#pragma once
#ifndef solver_hpp
#define solver_hpp

#include <string>
#include <vector>
#include <algorithm>
#include <QString>

#include "trie.hpp"

using std::string;
using std::vector;
using std::pair;

class SanajahtiSolver {
public:

    // main contructor, takes reference to wordlist vector, and the Sanajahti grid, and its dimensions
    // constructs a Trie (prefix tree) and initializes variables
    SanajahtiSolver(const vector<QString>& words, const vector<uint64_t>& grid, int x, int y);

    // does the solving, using the Trie
    // returns a vector of pairs where first pair is a word in Sanajahti, and second is the path of the word
    vector<pair<string, vector<pair<int, int>>>> solve();

private:
    // main recursive solving function of solver
    void solveRecursive(vector<uint64_t> prev,
                        vector<vector<bool> > visited,
                        int x, int y,
                        vector<pair<int, int> > curRoute,
                        int nodeIdx);

    // function to check if indices x, y within boundaries
    bool possibleNext(int x, int y, const vector<vector<bool> >& visited);

    // function to access a tile in sanajahti grid
    uint64_t getTile(int x, int y);

    // size of sanajahti grid, x and y
    int xsize_;
    int ysize_;

    // string in which the grid is stored
    vector<uint64_t> tiles_;

    // Trie of wordlist
    Trie tr_;

    // vector of results, cleared and rebuilt when solve() called
    vector<pair<vector<uint64_t>, vector<pair<int, int>>>> results_;
};


#endif /* solver_hpp */
