#include "ui.hpp"
#include "console.hpp"
#include <QApplication>

UI::UI(std::string option)
{
    if (option == "console"){
        auto cons = Console();
        cons.run();
        std::ifstream sanat(cons.getLibrary());
        std::vector<string> words;
        std::vector<QString> Qwords;
        std::string line;

        // read words to vector and filter non-ascii
        /*while (std::getline(sanat, line)) {
            // filter out non-ascii words (first bit 1 in char)
            bool valid = true;
            for (auto c: line) {
                if (c >> 7 != 0)
                    valid = false;
            }
            if (valid)
                words.push_back(line);
        }*/
        while (std::getline(sanat, line)) {
            Qwords.push_back(QString(line.data()));
        }

        // construct solver with words and solve sanajahti
        auto solver = SanajahtiSolver(Qwords, cons.getGrid(), cons.getX(), cons.getY());
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

