#ifndef solver_hpp
#define solver_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;
using std::tuple;
using std::unordered_map;

class SanajahtiSolver
{
public:
    // Solver constructor, takes the input tiles and filename to the wordlist
    SanajahtiSolver(int xsize, int ysize, string tiles, const string& filename);
    
    // solves stored sanajahti, returns all found words and their paths
    vector<tuple<string, vector<tuple<int, int>>>> solve();
    
private:
    // recursive function that pushes to results_ if found
    void getstuff(string prev, uint16_t state, int x, int y, vector<tuple<int, int>> curRoute);
    // gets the visited status for (x,y)
    bool getPos(uint16_t arr, int x, int y);
    // returns new visited state with visited (x,y) set to true
    uint16_t setPos(uint16_t arr, int x, int y);
    // gets the char at tile (x,y)
    char getCharAt(int x, int y);
    
    int xsize_, ysize_;
    uint16_t visited44_ = 0;
    vector<vector<bool>> visited_;
    unordered_map<string, bool> words_;
    string tiles_;
    vector<tuple<string, vector<tuple<int, int>>>> results_;
};

#endif /* solver_hpp */
