#include "solver.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {
    string arg1(argv[1]);
    string arg2(argv[2]);
    auto solver = SanajahtiSolver(4, 4, arg2, arg1);
    auto results = solver.solve();
    
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