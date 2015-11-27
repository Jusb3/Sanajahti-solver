#pragma once
#ifndef SANAJAHTI1_TO64BITCHARS_HPP
#define SANAJAHTI1_TO64BITCHARS_HPP

#include <cstdint>
#include <vector>
#include <string>
#include <QString>

using std::vector;

vector<uint64_t> to64bitChars(const std::string& input);
vector<uint64_t> to64bitChars(const QString& input);

#endif //SANAJAHTI1_TO64BITCHARS_HPP
