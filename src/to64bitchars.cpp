//
// Created by Juho Marttila on 27/11/15.
//

#include "to64bitchars.hpp"
#include <QTextBoundaryFinder>

vector<uint64_t> to64bitChars(const std::string& input) {
    const auto word = QString(input.data());
    return to64bitChars(word);
}

vector<uint64_t> to64bitChars(const QString& input) {
    bool onlyascii = true;
    std::vector<uint64_t> word64;
    word64.reserve(input.length()+1);
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
    else {
        const auto normWord = input.normalized(QString::NormalizationForm_C);

        // use boundary analysis to split utf-8 string to graphemes
        int prevbound = 0;
        auto boundFinder = QTextBoundaryFinder(QTextBoundaryFinder::Grapheme, normWord);
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
