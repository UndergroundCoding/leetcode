#include "gtest/gtest.h"

#include "10__Regular_Expression_Matching.h"

TEST(Given, Example1)
{
	//Example 1:
	//
	//Input: s = "aa", p = "a"
	//Output : false
	ASSERT_FALSE(Solution().isMatch("aa", "a"));
}

TEST(Given, Example2)
{
	//Example 2 :
	//
	//Input : s = "aa", p = "a*"
	//Output : true

	ASSERT_TRUE(Solution().isMatch("aa", "a*"));
}

TEST(Given, Example3)
{
	//Example 3 :
	//
	//Input : s = "ab", p = ".*"
	//Output : true
	ASSERT_TRUE(Solution().isMatch("ab", ".*"));
}

TEST(Tests, single_char_match)
{
	ASSERT_TRUE(Solution().isMatch("a", "a"));
}

TEST(Tests, single_char_not_match)
{
	ASSERT_FALSE(Solution().isMatch("a", "b"));
}

TEST(Tests, multi_char_match)
{
	ASSERT_TRUE(Solution().isMatch("aa", "aa"));
}

TEST(Tests, multi_char_not_match)
{
	ASSERT_FALSE(Solution().isMatch("aa", "ab"));
}

TEST(Tests, repeated_match)
{
	ASSERT_TRUE(Solution().isMatch("aa", "a*"));
	ASSERT_TRUE(Solution().isMatch("aaabbbc", "a*b*c"));
	ASSERT_TRUE(Solution().isMatch("a", "a*b*c*.*"));
}

TEST(Tests, repeated_not_match)
{
	ASSERT_FALSE(Solution().isMatch("ab", "a*"));
}

TEST(Tests, wildcard_match)
{
	ASSERT_TRUE(Solution().isMatch("", "."));
	ASSERT_TRUE(Solution().isMatch("a", "."));
}

TEST(Tests, repeated_wildcard_match)
{
	ASSERT_TRUE(Solution().isMatch("a", ".*"));
	ASSERT_TRUE(Solution().isMatch("ab", ".*"));
	ASSERT_TRUE(Solution().isMatch("", ".*"));
	ASSERT_TRUE(Solution().isMatch("aaabbbc", ".*"));
}

TEST(Tests, empty_string)
{
	ASSERT_TRUE(Solution().isMatch("", ""));
	ASSERT_TRUE(Solution().isMatch("", "."));
	ASSERT_TRUE(Solution().isMatch("", ".*"));
	ASSERT_TRUE(Solution().isMatch("", "c"));
	ASSERT_TRUE(Solution().isMatch("", "c*"));
	ASSERT_TRUE(Solution().isMatch("", "ac"));
}

TEST(Tests, empty_pattern)
{
	ASSERT_FALSE(Solution().isMatch("a", ""));
	ASSERT_TRUE(Solution().isMatch("ab", ".*"));
	ASSERT_TRUE(Solution().isMatch("", ".*"));
}