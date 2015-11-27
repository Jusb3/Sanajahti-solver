#include "trie.hpp"

Trie::Trie() {}
Trie::Trie(const std::vector<QString>& words)
{
    // construct root and put all words into trie
    auto root = TrieNode(-1, 0);
    store_.push_back(root);
    for (auto& word: words) {
        const auto normWord = word.normalized(QString::NormalizationForm_C);

        std::vector<uint64_t> word64;
        int prevbound = 0;
        auto boundFinder = QTextBoundaryFinder(QTextBoundaryFinder::Grapheme, normWord);
        while (true) {
            const auto nextBoundary = boundFinder.toNextBoundary();
            if (nextBoundary == -1)
                break;
            auto thisSlice = normWord.mid(prevbound, nextBoundary-prevbound).toUtf8();
            uint64_t char64 = 0;
            for (int i = 0; i < thisSlice.length(); i++) {
                unsigned char nextadded;
                nextadded = reinterpret_cast<unsigned char&>(thisSlice.data()[i]);
                char64 = char64 | ((nextadded) << (8*i));
            }
            word64.push_back(char64);
        }
        //std::cout << word64 << std::endl;
        add(word64);
    }
}

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

const TrieNode& Trie::getNode(const int nodeIdx) const
{
    return store_[nodeIdx];
}

int Trie::getSize()
{
    return (int)store_.size();
}