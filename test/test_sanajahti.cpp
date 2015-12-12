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












