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
	std::vector<std::string> test1 = {};				// Test an empty grid
	std::vector<std::string> test2 = {"a", "", "c"};	// Test a non rectancular grid

	ASSERT_FALSE(isValidGrid(test1)) << "The grid wasn't empty although it should be";
	ASSERT_FALSE(isValidGrid(test2)) << "The grid was rectangular even though it shouldn't be";
}


// Test that the function getSize in trie.cpp returns the correct amount of nodes
TEST(GetNodeSize, 8) {
	Trie trie;
	int size = trie.getSize();
	EXPECT_EQ(size, 1) << "Function getSize in trie.cpp returned a wrong amount of nodes";
}


// Test that the function getNode in trie.cpp returns successfully a node from trie
TEST(GetNode, 9) {
	std::vector<QString> words = {"auto", "auta"}; // Define, which words will be put into the trie
	Trie trie(words); // Initialize the tree

	uint64_t correct1_char = 97;	// ASCII letter a
	uint64_t correct2_char = 117;	// ASCII letter u
	uint64_t correct3_char = 116;	// ASCII letter t
	uint64_t correct4_char = 111;	// ASCII letter o
	int correct1_index = 1;			// The index of root node
	int correct2_index = 2;			// The index of the first child node
	int correct3_index = 3;			// The index of the second child node
	int correct4_index = 4;			// The index of the third child node
	int correct5_index = 5;			// The index of the fourth child node

	// Get the output of the function getNode recursively
	const auto node1_char = trie.getNode(0).children[0].first;
	const auto node1_index = trie.getNode(0).children[0].second;
	const auto node2_char = trie.getNode(node1_index).children[0].first;
	const auto node2_index = trie.getNode(node1_index).children[0].second;
	const auto node3_char = trie.getNode(node2_index).children[0].first;
	const auto node3_index = trie.getNode(node2_index).children[0].second;
	const auto node4_char = trie.getNode(node3_index).children[0].first;
	const auto node4_index = trie.getNode(node3_index).children[0].second;
	const auto node5_char = trie.getNode(node3_index).children[1].first;
	const auto node5_index = trie.getNode(node3_index).children[1].second;

	// Check the equality
	EXPECT_EQ(node1_char, correct1_char) << "Incorrect char in the root node";
	EXPECT_EQ(node1_index, correct1_index) << "Incorrect index for the root node";
	EXPECT_EQ(node2_char, correct2_char) << "Incorrect char in the first child node";
	EXPECT_EQ(node2_index, correct2_index) << "Incorrect index for the first child node";
	EXPECT_EQ(node3_char, correct3_char) << "Incorrect char in the second child node";
	EXPECT_EQ(node3_index, correct3_index) << "Incorrect index for the second child node";
	EXPECT_EQ(node4_char, correct4_char) << "Incorrect char in the third child node";
	EXPECT_EQ(node4_index, correct4_index) << "Incorrect index in the third child node";
	EXPECT_EQ(node5_char, correct1_char) << "Incorrect char in the fourth child node";
	EXPECT_EQ(node5_index, correct5_index) << "Incorrect index in the four";
}













