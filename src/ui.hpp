#pragma once
#ifndef UI_H
#define UI_H

#include "window.hpp"
#include <string>
#include <iostream>


class UI
{
public:
    UI(std::string option);
};

//sorting function
//sorts elements primarily by lenght and secondary by alphabetic order
bool longLex(const pair<string, vector<pair<int, int>>>& a,
             const pair<string, vector<pair<int, int>>>& b);

#endif // UI_H
