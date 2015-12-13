#include "ui.hpp"
#include "console.hpp"
#include <QApplication>
#include <fstream>

UI::UI(std::string option)
{
    if (option == "console"){
        auto cons = Console();
        cons.run();
        std::ifstream sanat(cons.getLibrary());
        //std::vector<string> words;
        std::vector<QString> Qwords;
        std::string line;

        while (std::getline(sanat, line)) {
            Qwords.push_back(QString(line.data()));
        }

        // construct solver with words and solve sanajahti
        auto solver = SanajahtiSolver(Qwords);
        auto results = solver.solve(cons.getGrid(), cons.getX(), cons.getY());

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
    }
    else {
        char **argv = {};
        int argc = 0;
        QApplication app(argc, argv);
        Window window;
        window.show();
        app.exec();
    }
}

