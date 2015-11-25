#include "console.hpp"

Console::Console()
{
    grid="";
    x_size=0;
    y_size=0;
    library="";
}

void Console::run()
{
    std::vector<std::string> rows;
    std::string row;
    std::cout << "Enter wordlist:";
    std::getline(std::cin, library);
    do{
        rows.clear();
        std::cout << "Enter the Sanajahti grid, row by row, separated by enter, empty row ends the entry:\n";
        while(getline(std::cin, row))
            if (row.empty())
                break;
            else
                rows.push_back(row);
    }while(!isValidGrid(rows));
    x_size=rows[0].length();
    y_size=rows.size();
    for(unsigned int count=0;count<rows.size();count++)
        grid+=rows[count];
}

std::string Console::getLibrary()
{
    return library;
}

std::string Console::getGrid()
{
    return grid;
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
    if(rows.size()==0){
        std::cout << "The grid cannot be empty.\nPlease type the asked parameters again.\n";
        return false;
    }
    for(unsigned int count=1;count<rows.size();count++)
        if(rows[count].length()!=rows[0].length()){
            std::cout << "The grid is not rectangular.\nPlease type the asked parameters again.\n";
            return false;
        }
    return true;
}
