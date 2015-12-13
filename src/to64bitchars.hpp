#pragma once
#ifndef SANAJAHTI1_TO64BITCHARS_HPP
#define SANAJAHTI1_TO64BITCHARS_HPP

#include <cstdint>
#include <vector>
#include <string>
#include <QString>

using std::vector;
using std::pair;
using std::string;

// converts std::string to custom 64-bit format, internally converts first to QString
vector<uint64_t> to64bitChars(const std::string& input);

// converts QString to custom 64-bit format
// format works like this: each 64-bit uint is a grapheme where each
// 8-bit sequence is a UTF-8 encoded byte, starting from the least significant byte
// this achieves very good Unicode support with a fixed lenght-encoding
// supports upto 8-bytes per grapheme, after that bytes simply ignored
vector<uint64_t> to64bitChars(const QString& input);

// returns the lenght of string in graphemes
int graphemeLength(const QString& input);
int graphemeLength(const std::string& input);


//sorting function that
//sorts elements primarily by lenght and secondary by alphabetic order
bool longLex(const pair<string, vector<pair<int, int>>>& a,
             const pair<string, vector<pair<int, int>>>& b);

#endif //SANAJAHTI1_TO64BITCHARS_HPP
