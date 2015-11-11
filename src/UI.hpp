#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

class UI
{
public:
	UI();
	void Run();
	std::string GetLibrary();
	std::string GetGrid();
	int GetX();
	int GetY();
private:
	std::string library; 
	std::string grid; 
	int x_size;
	int y_size;
};

bool IsValidGrid(std::vector<std::string> rows);