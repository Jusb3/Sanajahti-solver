#include <gtest/gtest.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <chrono>
#include <array>
#include "../src/to64bitchars.cpp"
#include "../src/solver.cpp"
#include "../src/trie.cpp"
#include "../src/console.cpp"


int main(int argc, char* argv[])
{
	std::cout << "The tests begin..." << std::endl;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


// Test that the length of the grapheme is correct
TEST(TestLength, 1) {
	QString test1 = "televisio";
	QString test2 = "ui";
	QString test3 = 
	"atomiydinenergiareaktorigeneraattorilauhduttajaturbiiniratasvaihde";
	QString test4 = "ääkkönen";

	const auto len1 = graphemeLength(test1);
	const auto len2 = graphemeLength(test2);
	const auto len3 = graphemeLength(test3);
	const auto len4 = graphemeLength(test4);

	EXPECT_EQ(len1, 9) << "Wrong length with the word: televisio";
	EXPECT_EQ(len2, 2) << "Wrong length with the word: ui";
	EXPECT_EQ(len3, 66) << 
	"Wrong length with the word: atomiydinenergiareaktorigeneraattorilauhduttajaturbiiniratasvaihde";
	EXPECT_EQ(len4, 8) << "Wrong length with the word: ääkkönen";
}


// Test that the solver finds the correct string
TEST(Solver, 2) {
	std::string test = "abcdefghijklmnopqrstuvwxyz"; 
	std::vector<uint64_t> correct = {97, 98, 99, 100, 101, 102,
		103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 
		114, 115, 116, 117, 118, 119 ,120, 121, 122};
	std::vector<uint64_t> grid;
	grid = to64bitChars(test);

	EXPECT_EQ(grid, correct) << "The function to64bitChars didn't produce the correct string";
}

// Test that x_size can be returned successfully
TEST(GetX, 3) {
	Console console;
	int x_size = console.getX();
	EXPECT_EQ(x_size, 0) << "Incorrect x_size";
}


// Test that y_size can be returned successfully
TEST(GetY, 4) {
	Console console;
	int y_size = console.getY();
	EXPECT_EQ(y_size, 0) << "Incorrect y_size";
}


// Test that the library can be returned succesfully
TEST(GetLibrary, 5) {
	Console console;
	std::string library = console.getLibrary();
	EXPECT_EQ(library, "") << "Error in returning the library";
}


// Test that the grid can be returned succesfully
TEST(GetGrid, 6) {
	Console console;
	std::vector<uint64_t> test = console.getGrid();
	std::vector<uint64_t> correct = {};
	EXPECT_EQ(test, correct) << "Error in getting the grid";

}


// Test that the grid is valid
TEST(IsValidGrid, 7) {
	std::vector<std::string> test1 = {}; 				// Test an empty grid
	std::vector<std::string> test2 = {"a", "", "c"};	// Test a non rectancular grid

	ASSERT_FALSE(isValidGrid(test1));
	ASSERT_FALSE(isValidGrid(test2));
}

















