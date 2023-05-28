/*	https://leetcode.com/problems/regular-expression-matching/
Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:

'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).



Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
Example 3:

Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".


Constraints:

1 <= s.length <= 20
1 <= p.length <= 20
s contains only lowercase English letters.
p contains only lowercase English letters, '.', and '*'.
It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.
*/

#include "10__Regular_Expression_Matching.h"

using CIterator = std::string::const_iterator;

class SimpleStringIterator
{
protected:
	int m_size;
	CIterator m_end;
	CIterator m_pos;

public:
	SimpleStringIterator() = delete;
	SimpleStringIterator(const std::string& string) : m_size(string.size()), m_pos(string.cbegin()), m_end(string.cend())
	{
	}

	bool isFinished()
	{
		return m_pos == m_end;
	}

	SimpleStringIterator next()
	{
		++m_pos;
		return *this;
	}

	int pos()
	{
		return m_size - (m_end - m_pos);
	}

	int size()
	{
		return m_size;
	}

	SimpleStringIterator& goTo(int pos)
	{
		if (pos < 0 || pos >= m_size)
			throw std::exception("Bad pos");
		m_pos = m_end - (m_size - pos);
		return *this;
	}

	bool match(const SimpleStringIterator& ssIt)
	{
		return *m_pos == *(ssIt.m_pos);
	}
};

class PatternIterator : public SimpleStringIterator
{
public:
	PatternIterator() = delete;
	PatternIterator(const std::string& pattern) : SimpleStringIterator(pattern)
	{
	}

	bool isLooped()
	{
		auto next = m_pos + 1;
		return (next != m_end && *next == '*');
	}

	bool match(const SimpleStringIterator& ssIt)
	{
		if (*m_pos == '.')
			return true;

		return SimpleStringIterator::match(ssIt);
	}

	PatternIterator& next()
	{
		if (isLooped())
			// Step over '*'
			++m_pos;
		SimpleStringIterator::next();
		return *this;
	}
};

bool matchPattern(SimpleStringIterator& ssIt, PatternIterator& pIt)
{
	// Input validation	//

	if (ssIt.isFinished())
	{
		// No more characters to match
		return true;
	}

	if (pIt.isFinished())
	{
		// More characters to match but no more tokens
		return false;
	}

	// Token process	//

	if (pIt.isLooped())
	{
		// Save state
		auto pPos = pIt.pos();
		auto ssPos = ssIt.pos();

		// Iterate over the characters while it matches the loop token
		while(ssIt.pos() < ssIt.size() && pIt.match(ssIt))
		{
			// Attempt a match (start recursion)
			if (matchPattern(ssIt.next(), pIt.next()))
			{
				// The pattern worked
				return true;
			}
			// The loop was valid but did not complete the match
			// Set pattern to the start of loop position and try again with the next character
			pIt.goTo(pPos);
		}

		// The loop failed, restore string to pre-loop position
		ssIt.goTo(ssPos);
	}

	// Consume the non-looped token
	if (!pIt.match(ssIt))
		return false;

	// Proceed to next iteration
	return matchPattern(ssIt.next(), pIt.next());
}

bool Solution::isMatch(std::string s, std::string p)
{
	// Since this exercise has no time constraint we can use a brute force

	// Let the brute force begin
	SimpleStringIterator string(s);
	PatternIterator pattern(p);
	return matchPattern(string, pattern);
}
