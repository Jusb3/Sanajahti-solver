//
// Created by Juho Marttila on 27/11/15.
//

#include "to64bitchars.hpp"
#include <QTextBoundaryFinder>

vector<uint64_t> to64bitChars(const std::string& input) {
    // normalize unicode
    const auto word = QString(input.data());
    return to64bitChars(word);
}

vector<uint64_t> to64bitChars(const QString& input) {
    const auto normWord = input.normalized(QString::NormalizationForm_C);

    // use boundary analysis to split utf-8 string to graphemes
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
        prevbound = nextBoundary;
    }
    return word64;
}