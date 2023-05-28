#pragma once

#include <string>

class SimpleStringIterator;
class PatternIterator;

class Solution
{
public:
    bool isMatch(std::string s, std::string p);
    bool matchPattern(SimpleStringIterator ssIt, PatternIterator pIt);
};
