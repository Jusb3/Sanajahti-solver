#include "trie.hpp"

Trie::Trie() {}
Trie::Trie(const std::vector<std::string> words)
{
    // construct root and put all words into trie
    auto root = TrieNode(-1, 0);
    store_.push_back(root);
    for (auto& s: words) {
        add(s);
    }
}

void Trie::add(const std::string& word)
{
    // iterate over chars in word, traversing into right child node, or if it doesn't exist, create one
    int nodeIdx = 0;
    int endidx = (int)(word.length());
    for (int stringIdx = 0; stringIdx < endidx; stringIdx++) {
        const auto nextChar = word[stringIdx];

        // get child idx, or find out it doesn't exist yet
        const auto it = std::find_if(store_[nodeIdx].children.begin(), store_[nodeIdx].children.end(),
                                     [nextChar](std::pair<char, int>& x){return x.first == nextChar;});

        // child doesn't exist, create one
        if (it == store_[nodeIdx].children.end()) {
            auto newNode = TrieNode(nodeIdx, nextChar);
            store_.push_back(newNode);
            store_[nodeIdx].children.push_back(std::make_pair(nextChar, store_.size()-1));
            nodeIdx = (int)(store_.size()-1);
        }
        // traverse to child
        else {
            nodeIdx = it->second;
        }
    }
    // mark that this trienode is end of word
    store_[nodeIdx].isWordEnd = true;
    return;
}

const TrieNode& Trie::getNode(const int nodeIdx) const
{
    return store_[nodeIdx];
}

int Trie::getSize()
{
    return (int)store_.size();
}