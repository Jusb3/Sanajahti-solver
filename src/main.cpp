#include "solver.hpp"
#include "UI.hpp"
#include <iostream>
#include <fstream>

int main(int argc, const char * argv[]) {
    auto ui= UI();
    ui.Run();
    std::ifstream sanat(ui.GetLibrary());
    std::vector<string> words;
    std::string line;

    // read words to vector and filter non-ascii
    while (std::getline(sanat, line)) {
        // filter out non-ascii words (first bit 1 in char)
        bool valid = true;
        for (auto c: line) {
            if (c >> 7 != 0)
                valid = false;
        }
        if (valid)
            words.push_back(line);
    }

    // construct solver with words and solve sanajahti
    auto solver = SanajahtiSolver(words, ui.GetGrid(), ui.GetX(), ui.GetY());
    auto results = solver.solve();

    // display results
    for (auto& s: results) {
        auto name = std::get<0>(s);
        auto route = std::get<1>(s);
        std::cout << name;
        for (auto point: route) {
            std::cout << "  " << "(" << std::get<0>(point) << "," << std::get<1>(point) << ")";
        }
        std::cout << std::endl;
    }
    return 0;
}