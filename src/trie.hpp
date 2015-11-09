#ifndef SANAJAHTI1_TRIE_HPP
#define SANAJAHTI1_TRIE_HPP


#include <vector>
#include <string>
#include <tuple>

// node of trie, stores info about, the character, children (chars and vector indices), parent, and if the word from
// root to this node is a complete word
struct TrieNode {
    int parentIdx;
    char nodeChar;
    // vector of pairs (child char, child vector index)
    std::vector<std::pair<char, int>> children;
    bool isWordEnd;
    TrieNode(int parentIdx, char nodeChar): parentIdx(parentIdx), nodeChar(nodeChar), isWordEnd(false) {}
};

// The trie class itself, stores TrieNodes
class Trie {
public:
    Trie();
    // construct trie with words
    Trie(const std::vector<std::string> words);
    // add word to trie
    void add(const std::string& word);
    // get reference to a TrieNode
    const TrieNode& getNode(const int nodeIdx) const;
    // get the amount of TrieNodes stored
    int getSize();
private:
    // the Trie nodes are stored in a vector (makes memory handling easier and should make cache locality better)
    std::vector<TrieNode> store_;
};


#endif //SANAJAHTI1_TRIE_HPP
