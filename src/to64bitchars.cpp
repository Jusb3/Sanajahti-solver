//
// Created by Juho Marttila on 27/11/15.
//

#include "to64bitchars.hpp"
#include <QTextBoundaryFinder>

// converts std::string to custom 64-bit format
vector<uint64_t> to64bitChars(const std::string& input) {
    const auto word = QString(input.data());
    return to64bitChars(word);
}


// converts QString to custom 64-bit format
// format works like this: each 64-bit uint is a grapheme where each
// 8-bit sequence is a UTF-8 encoded byte, starting from the least significant byte
// this achieves very good Unicode support with a fixed lenght-encoding
// supports upto 8-bytes per grapheme, after that bytes simply ignored
vector<uint64_t> to64bitChars(const QString& input) {
    bool onlyascii = true;
    std::vector<uint64_t> word64;
    word64.reserve(input.length()+1);

    // check if string is completely ascii so that boundary finding can be optimized out
    for (auto qchar : input) {
        if (qchar > 122 || qchar < 97) {
            onlyascii = false;
            break;
        }
    }
    if (onlyascii) {
        for (auto qchar : input) {
            word64.push_back(reinterpret_cast<unsigned char&>(qchar));
        }
    }
    // case that word has non-ascii char(s)
    else {
        const auto normWord = input.normalized(QString::NormalizationForm_C);

        // use boundary analysis to split utf-8 string to graphemes
        int prevbound = 0;
        auto boundFinder = QTextBoundaryFinder(QTextBoundaryFinder::Grapheme, normWord);

        // iterate over grapheme boundaries
        while (true) {
            const auto nextBoundary = boundFinder.toNextBoundary();
            if (nextBoundary == -1)
                break;
            auto thisSlice = normWord.midRef(prevbound, nextBoundary-prevbound).toUtf8();
            uint64_t char64 = 0;
            for (int i = 0; i < thisSlice.length(); i++) {
                unsigned char nextadded;
                nextadded = reinterpret_cast<unsigned char&>(thisSlice.data()[i]);
                char64 = char64 | ((nextadded) << (8*i));
            }
            word64.push_back(char64);
            prevbound = nextBoundary;
        }
    }
    return word64;
}

// returns the length of string, in graphemes (user perceived characters)
int graphemeLength(const QString& input) {
    auto boundFinder = QTextBoundaryFinder(QTextBoundaryFinder::Grapheme, input);
    boundFinder.toEnd();
    return boundFinder.position();
}

int graphemeLength(const std::string& input) {
    return graphemeLength(QString(input.data()));
}
