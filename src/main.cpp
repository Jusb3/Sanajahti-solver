#include "window.hpp"
#include "ui.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    UI ui(argv[1]!=NULL?argv[1]:"");
    return argc;
}
