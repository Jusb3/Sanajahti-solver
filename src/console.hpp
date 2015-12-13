#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <QString>

class Console {
public:
    // initializes some variables, allows run() to be called
    Console();
    // asks the user for wordlist file and grid, and saves them
    void run();
    // returns the grid user inputed, as custome encoded string
    std::vector<uint64_t> getGrid();
    // returns the wordlist words as a vector of QStrings
    const std::vector<QString> getWords() const;

    int getX(); // grid x-size
    int getY(); // grid y-size
private:
    std::string library; 
    std::vector<uint64_t> grid;
    int x_size;
    int y_size;
    std::vector<QString> words;
};

// checks that the grid is valid (grid is not empty, and is rectangular)
bool isValidGrid(std::vector<std::string> rows);
