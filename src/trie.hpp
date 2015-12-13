#pragma once
#ifndef SANAJAHTI1_TRIE_HPP
#define SANAJAHTI1_TRIE_HPP


#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <QString>

// node of trie, stores info about, the character, children (chars and vector indices), parent, and if the word from
// root to this node is a complete word
struct TrieNode {
    int parentIdx; // parent index of Node, root has parent idx -1
    uint64_t nodeChar;  // char of trie node, in custom 64-bit format
    // children of Node, vector of pairs (child char, child vector index): { (char, idx), (char, idx) } etc.
    std::vector<std::pair<uint64_t, int>> children;
    bool isWordEnd; // true if this node is an end of a word, can still have children (for other words)

    // TrieNode constructor
    TrieNode(int parentIdx, uint64_t nodeChar): parentIdx(parentIdx), nodeChar(nodeChar), isWordEnd(false) {}
};

// The trie class itself, stores TrieNodes
// The trie class is a suffix tree data structure that
// stores the wordlist in a  way that makes the solving algorithm fast
class Trie {
public:
    // empty constructor, only root is constructed, caller needs to add words
    Trie();
    // construct trie with words
    Trie(const std::vector<QString>& words);
    // add word to trie, uses a custom 64-bit format
    void add(const std::vector<uint64_t>& word);
    // get reference to a TrieNode
    const TrieNode& getNode(const int nodeIdx) const;
    // get the amount of TrieNodes stored
    int getSize();
private:
    // the Trie nodes are stored in a vector (makes memory handling easier and should make cache locality better)
    std::vector<TrieNode> store;
};


#endif //SANAJAHTI1_TRIE_HPP
