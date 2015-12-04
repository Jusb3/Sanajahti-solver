#include "trie.hpp"
#include "to64bitchars.hpp"

Trie::Trie() {}
Trie::Trie(const std::vector<QString>& words)
{
    // construct root and put it into Trie
    auto root = TrieNode(-1, 0);
    store_.push_back(root);

    // for each word in wordlist, normalize unicode and encode string to custom 64-bit fixed-width format
    for (auto& word: words) {
        const auto encodedWord = to64bitChars(word);
        add(encodedWord);
    }
}

// add a word to the Trie structure
void Trie::add(const std::vector<uint64_t>& word)
{
    // iterate over chars in word, traversing into right child node, or if it doesn't exist, create one
    int nodeIdx = 0;
    int endidx = (int)(word.size());
    for (int stringIdx = 0; stringIdx < endidx; stringIdx++) {
        const auto nextChar = word[stringIdx];

        // get child idx, or find out it doesn't exist yet
        const auto it = std::find_if(store_[nodeIdx].children.begin(), store_[nodeIdx].children.end(),
                                     [nextChar](std::pair<uint64_t, int>& x){return x.first == nextChar;});

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

// get a node from trie
const TrieNode& Trie::getNode(const int nodeIdx) const
{
    return store_[nodeIdx];
}

// get the amount of nodes in trie
int Trie::getSize()
{
    return (int)store_.size();
}
