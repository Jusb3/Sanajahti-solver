#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <QString>

class Console {
public:
    Console();
    void run();
    std::string getLibrary();
    std::vector<uint64_t> getGrid();
    const std::vector<QString> getWords() const;
    int getX();
    int getY();
private:
    std::string library; 
    std::vector<uint64_t> grid;
    int x_size;
    int y_size;
    std::vector<QString> words;
};

bool isValidGrid(std::vector<std::string> rows);
