#include "solver.hpp"

using std::string;

// main contructor, takes reference to wordlist vector, and the Sanajahti grid, and its dimensions
// constructs a Trie (prefix tree) and initializes variables
SanajahtiSolver::SanajahtiSolver(const vector<string>& words, const string& grid, int x, int y): tr_(words) {
    tiles_ = grid;
    xsize_ = x;
    ysize_ = y;
}

// does the solving, using the Trie
// returns a vector of pairs where first pair is a word in Sanajahti, and second is the path of the word
vector<pair<string, vector<pair<int, int>>>> SanajahtiSolver::solve() {

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
            auto curChar = getTile(i, j);
            // root node
            auto curNode = tr_.getNode(0);
            // get right child of root node (right char)
            auto it = std::find_if(
                    curNode.children.begin(), curNode.children.end(),
                    [curChar](std::pair<char, int>& x){return x.first == curChar;}
            );
            // start recursive find if there are any words that start with this character
            if (it != curNode.children.end()) {
                solveRecursive("", visited, i, j, startRoute, it->second);
            }
        }
    }

    sort(results_.begin(), results_.end());
    auto last = unique(results_.begin(), results_.end(),
                       [](pair<string, vector<pair<int, int>>> a, pair<string, vector<pair<int, int>>> b)
                       {return a.first == b.first; }
    );
    results_.erase(last, results_.end());

    return results_;
}

void SanajahtiSolver::solveRecursive(string prev,
                                vector<vector<bool>> visited,
                                int x, int y,
                                vector<pair<int, int>> curRoute,
                                int nodeIdx)
{
    // get current node from trie
    auto curNode = tr_.getNode(nodeIdx);
    // this string represents the path search has taken
    auto curString = prev + getTile(x, y);
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
                            [newChar](std::pair<char, int>& a){return a.first == newChar;}
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
bool SanajahtiSolver::possibleNext(int x, int y, const vector<vector<bool>>& visited) {
    if (x < 0 || y < 0 || x >= xsize_ || y >= ysize_)
        return false;
    return !(visited[x][y]);
}

// get char of Sanajahti grid tile
char SanajahtiSolver::getTile(int x, int y) {
    return tiles_[y*xsize_ + x];
}