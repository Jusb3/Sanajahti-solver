#include "ui.hpp"
#include "console.hpp"
#include "to64bitchars.hpp"
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
    else {
        char **argv = {};
        int argc = 0;
        QApplication app(argc, argv);
        Window window;
        window.show();
        app.exec();
    }
}

bool longLex(const pair<string, vector<pair<int, int>>>& a,
             const pair<string, vector<pair<int, int>>>& b)
{
    QString fir= QString::fromStdString(a.first);
    QString sec= QString::fromStdString(b.first);

    const auto firGraphemeLength = graphemeLength(fir);
    const auto secGraphemeLength = graphemeLength(sec);

    //if (fir.length() == sec.length())
    if (firGraphemeLength == secGraphemeLength)
        for (int j=0; j < fir.length(); j++)
            if (fir.at(j) != sec.at(j))
                return fir.at(j) < sec.at(j);
    //return fir.length() > sec.length();
    return firGraphemeLength > secGraphemeLength;
}
