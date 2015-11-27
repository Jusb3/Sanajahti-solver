#include "solver.hpp"

using std::string;

// main contructor, takes reference to wordlist vector, and the Sanajahti grid, and its dimensions
// constructs a Trie (prefix tree) and initializes variables
SanajahtiSolver::SanajahtiSolver(
        const vector<QString>& words,
        const vector<uint64_t>& grid,
        int x, int y): tr_(words)
{
    tiles_ = grid;
    xsize_ = x;
    ysize_ = y;
}

// does the solving, using the Trie
// returns a vector of pairs where first pair is a word in Sanajahti, and second is the path of the word
vector<pair<string, vector<pair<int, int>>>> SanajahtiSolver::solve()
{

    // initialize a vector of visited tiles, used when going through the grid
    vector<vector<bool>> visited;
    visited.resize((unsigned long)xsize_);
    for (auto& x: visited) {
        x.resize((unsigned long)ysize_, false);
    }

    // empty start route supplied to all grid travelsals (1 for each tile)
    vector<pair<int, int>> startRoute;

    // traverse grid starting from each tile
    for (int i = 0; i < xsize_; i++) {
        for (int j = 0; j < ysize_; j++) {
            auto curTile = getTile(i, j);
            // root node
            auto curNode = tr_.getNode(0);
            // get right child of root node (right char)
            auto it = std::find_if(
                    curNode.children.begin(), curNode.children.end(),
                    [curTile](std::pair<uint64_t , int>& x){return x.first == curTile;}
            );
            // start recursive find if there are any words that start with this character
            vector<uint64_t> startString;
            if (it != curNode.children.end()) {
                solveRecursive(startString, visited, i, j, startRoute, it->second);
            }
        }
    }
    vector<pair<string, vector<pair<int, int>>>> stringResults;
    for (auto& result: results_) {
        string resultString;
        for (auto char64: result.first) {
            for (int i = 0; i < 8; i++) {
                const unsigned char thisChar = (unsigned char)((char64 >> (8*i)) & 0xFF);
                if (thisChar != 0) {
                    resultString += thisChar;
                }
            }
        }
        stringResults.push_back(std::make_pair(resultString, result.second));
    }

    sort(stringResults.begin(), stringResults.end());
    auto last = unique(stringResults.begin(), stringResults.end(),
                       [](pair<string, vector<pair<int, int>>> a, pair<string, vector<pair<int, int>>> b)
                       {return a.first == b.first; }
    );
    stringResults.erase(last, stringResults.end());

    return stringResults;
}

void SanajahtiSolver::solveRecursive(vector<uint64_t> prev,
                                vector<vector<bool>> visited,
                                int x, int y,
                                vector<pair<int, int>> curRoute,
                                int nodeIdx)
{
    // get current node from trie
    auto curNode = tr_.getNode(nodeIdx);
    // this string represents the path search has taken
    auto curString = prev;
    curString.push_back(getTile(x,y));
    // mark this tile as visited
    visited[x][y] = true;
    // append this node to the route recursion has taken (from root)
    curRoute.push_back(std::make_pair(x, y));
    // if trie has word here, push it into results, along with current route
    if (curNode.isWordEnd) {
        results_.push_back(std::make_pair(curString, curRoute));
    }

    // recursively iterate all neighbors that have a possible char and are not visited yet
    // iterate over neighbors, x, y
    for (int newx = -1; newx <= 1; newx++) {
        for (int newy = -1; newy <= 1; newy++) {
            // filter out going to this current node
            if (newy != 0 || newx != 0) {
                // check that neighbor is not outside bounds and not visited yet
                if (possibleNext(x+newx, y+newy, visited)) {
                    // check if possible character in neighbor node
                    auto newChar = getTile(x+newx, y+newy);
                    auto it = std::find_if(
                            curNode.children.begin(), curNode.children.end(),
                            [newChar](std::pair<uint64_t, int>& a){return a.first == newChar;}
                    );
                    // if possible char found, traverse to that node
                    if (it != curNode.children.end()) {
                        solveRecursive(curString, visited, x+newx, y+newy, curRoute, it->second);
                    }
                }
            }
        }
    }
}

// check that x, y not visited and not outside bounds
bool SanajahtiSolver::possibleNext(int x, int y, const vector<vector<bool>>& visited)
{
    if (x < 0 || y < 0 || x >= xsize_ || y >= ysize_)
        return false;
    return !(visited[x][y]);
}

// get char of Sanajahti grid tile
uint64_t SanajahtiSolver::getTile(int x, int y)
{
    return tiles_[y*xsize_ + x];
}