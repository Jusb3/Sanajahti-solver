#include "solver.hpp"

// Solver constructor, takes the input tiles and filename to the wordlist
SanajahtiSolver::SanajahtiSolver(int xsize,
                                 int ysize,
                                 string tiles,
                                 const string& filename)
{
    std::ifstream sanakirja(filename);
    string s, sink;
    
    xsize_ = xsize;
    ysize_ = ysize;
    
    // currently only parses kotus xml file
    while (getline(sanakirja, s)) {
        string word;
        replace(s.begin(), s.end(), '<', ' ');
        replace(s.begin(), s.end(), '>', ' ');
        std::stringstream ss(s);
        ss >> sink >> sink >> word;
        words_[word] = true;
    }
    tiles_ = tiles;
}

// solves stored sanajahti, returns all found words and their paths
vector<tuple<string, vector<tuple<int, int>>>>
SanajahtiSolver::solve()
{
    results_.clear();
    uint16_t startState = 0;
    vector<tuple<int, int>> start;
    
    // update results_ for all starting tiles
    for (int x = 0; x < xsize_; x++) {
        for (int y = 0; y < ysize_; y++) {
            vector<tuple<int, int>> start;
            getstuff("", startState, x, y, start);
        }
    }
    
    // remove duplicates from results_
    sort(results_.begin(), results_.end());
    auto last = unique(results_.begin(), results_.end(),
                       [](tuple<string, vector<tuple<int, int>>> a, tuple<string, vector<tuple<int, int>>> b)
                       {
                           return std::get<0>(a) == std::get<0>(b);
                       });
    results_.erase(last, results_.end());
    return results_;
}

void SanajahtiSolver::getstuff(string prev,
                               uint16_t state,
                               int x, int y,
                               vector<tuple<int, int>> curRoute)
{
    if (x < 0 || y < 0 || x > 3 || y > 3) {
        return;
    }
    curRoute.push_back(std::make_tuple(x, y));
    state = setPos(state, x, y);
    string curstring = prev+getCharAt(x, y);
    if (words_.find(curstring) != words_.end()) {
        results_.push_back(make_tuple(curstring, curRoute));
    }
    if (!getPos(state, x+1, y))
        getstuff(curstring, state, x+1, y, curRoute);
    if (!getPos(state, x+1, y+1))
        getstuff(curstring, state, x+1, y+1, curRoute);
    if (!getPos(state, x, y+1))
        getstuff(curstring, state, x, y+1, curRoute);
    if (!getPos(state, x-1, y+1))
        getstuff(curstring, state, x-1, y+1, curRoute);
    if (!getPos(state, x-1, y))
        getstuff(curstring, state, x-1, y, curRoute);
    if (!getPos(state, x-1, y-1))
        getstuff(curstring, state, x-1, y-1, curRoute);
    if (!getPos(state, x, y-1))
        getstuff(curstring, state, x, y-1, curRoute);
    if (!getPos(state, x+1, y-1))
        getstuff(curstring, state, x+1, y-1, curRoute);

}

bool SanajahtiSolver::getPos(uint16_t arr, int x, int y) {
    // row major ordering
    if (x < 0 || y < 0 || x > 3 || y > 3) {
        return true;
    }
    return ((arr >> (y*4)) >> x) & 1;
}

uint16_t SanajahtiSolver::setPos(uint16_t arr, int x, int y) {
    return arr | ((1 << (y*4)) << x);
}

char SanajahtiSolver::getCharAt(int x, int y) {
    return tiles_[y*4+x];
}