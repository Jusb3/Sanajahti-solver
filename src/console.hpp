#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

class Console{
public:
    Console();
    void run();
    std::string getLibrary();
    std::string getGrid();
    int getX();
    int getY();
private:
    std::string library; 
    std::string grid; 
    int x_size;
    int y_size;
};

bool isValidGrid(std::vector<std::string> rows);
