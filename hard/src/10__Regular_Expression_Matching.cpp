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

	bool isFinished() const
	{
		return m_pos == m_end;
	}

	SimpleStringIterator& next()
	{
		if(!isFinished())
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
		if (isFinished())
			return false;

		auto next = m_pos + 1;
		return (next != m_end && *next == '*');
	}

	bool match(const SimpleStringIterator& ssIt)
	{
		if (isFinished() || ssIt.isFinished())
			return false;

		if (*m_pos == '.')
			return true;

		return SimpleStringIterator::match(ssIt);
	}

	PatternIterator& goTo(int pos)
	{
		SimpleStringIterator::goTo(pos);
		return *this;
	}

	PatternIterator& next()
	{
		SimpleStringIterator::next();
		if (!isFinished() && *m_pos == '*')
			++m_pos;
		return *this;
	}
};

bool Solution::isMatch(std::string s, std::string p)
{
	// Since this exercise has no time constraint we can use a brute force

	// Let the brute force begin
	SimpleStringIterator string(s);
	PatternIterator pattern(p);
	return matchPattern(string, pattern);
}

bool Solution::matchPattern(SimpleStringIterator ssIt, PatternIterator pIt)
{
	// Input validation	//

	if (ssIt.isFinished() && pIt.isFinished())
	{
		// All matched
		return true;
	}
	else if (ssIt.isFinished() && !pIt.isFinished())
	{
		// No characters left but still tokens
		
		// Try to skip loops
		while (pIt.isLooped())
			pIt.next();

		return pIt.isFinished();
	}
	else if (!ssIt.isFinished() && pIt.isFinished())
	{
		// No more tokens
		return false;
	}

	// Token process	//

	while (pIt.isLooped())
	{
		// Save state
		auto pPos = pIt.pos();
		auto ssPos = ssIt.pos();

		// Iterate over the characters while it matches the loop token
		while (ssIt.pos() < ssIt.size() && pIt.match(ssIt))
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

		// The loop failed, restore string to pre-loop position and skip loop
		pIt.goTo(pPos).next();
		ssIt.goTo(ssPos);
	}

	// Consume the non-looped token
	if (!pIt.match(ssIt))
		return false;

	// Proceed to next iteration
	return matchPattern(ssIt.next(), pIt.next());
}
