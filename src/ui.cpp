#include "ui.hpp"
#include "console.hpp"
#include "to64bitchars.hpp"
#include <QApplication>
#include <fstream>

UI::UI(const std::string &option)
{
    //check if program was run with argument "console"
    if (option == "console"){
        auto cons = Console();
        cons.run();
        const auto Qwords = cons.getWords();
        // construct solver with words and solve sanajahti
        auto solver = SanajahtiSolver(Qwords);
        auto results = solver.solve(cons.getGrid(), cons.getX(), cons.getY());
        std::sort(results.begin(), results.end(), longLex);

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
    //if console argument was not given, run GUI
    else {
        char **argv = {};
        int argc = 0;
        QApplication app(argc, argv);
        QFont font;
        font.setFamily("Arial");
        font.setBold(true);
        font.setPointSize(11);
        QApplication::setFont(font);
        Window window;
        window.show();
        app.exec();
    }
}
