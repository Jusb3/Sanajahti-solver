#include "console.hpp"
#include "to64bitchars.hpp"
#include <fstream>

Console::Console()
{
    x_size = 0;
    y_size = 0;
    library = "";
}

void Console::run()
{
    std::vector<std::string> rows;
    std::string row;
    bool cont = true;
    while (cont) {
        std::cout << "Enter wordlist:";
        std::getline(std::cin, library);
        std::ifstream thisfileTest(library);
        if (thisfileTest.is_open()) {
            cont = false;
        }
        else {
            std::cout << "File not found" << std::endl;
        }
    }

    std::ifstream thisfile(library);

    std::string line;
    while (std::getline(thisfile, line)) {
        words.push_back(QString(line.data()));
    }

    do {
        rows.clear();
        std::cout << "Enter the Sanajahti grid, row by row, separated by enter, empty row ends the entry:\n";
        while (getline(std::cin, row))
            if (row.empty())
                break;
            else
                rows.push_back(row);
    } while (!isValidGrid(rows));

    x_size = (int)rows[0].length();
    y_size = (int)rows.size();

    for (auto& r: rows) {
        const auto encodedChars = to64bitChars(r);
        for (auto c: encodedChars) {
            grid.push_back(c);
        }
    }
}

std::vector<uint64_t> Console::getGrid()
{
    return grid;
}

const std::vector<QString> Console::getWords() const
{
    return words;
}

int Console::getX()
{
    return x_size;
}

int Console::getY()
{
    return y_size;
}

bool isValidGrid(std::vector<std::string> rows)
{
    if (rows.size() == 0) {
        std::cout << "The grid cannot be empty.\nPlease type the asked parameters again.\n";
        return false;
    }
    for (unsigned int count = 1; count < rows.size(); count++) {
        if (graphemeLength(rows[count]) != graphemeLength(rows[0])) {
            std::cout << "The grid is not rectangular.\nPlease type the asked parameters again.\n";
            return false;
        }
    }
    return true;
}
