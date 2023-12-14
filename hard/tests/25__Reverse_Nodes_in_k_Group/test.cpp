#include "gtest/gtest.h"

#include "25__Reverse_Nodes_in_k_Group.h"

#include <vector>

std::vector<ListNode> generateLinkedListNodes(std::vector<int> values)
{
	if (values.empty())
		return std::vector<ListNode>(1);

	std::vector<ListNode> listNodes(values.size());
	for (auto itListNode = listNodes.begin(); itListNode != listNodes.end(); itListNode++)
	{
		if (itListNode + 1 != listNodes.end())
			itListNode->next = &*(itListNode + 1);		// Dereference the iterator and take address

		auto pos = itListNode - listNodes.begin();
		itListNode->val = values.at(pos);
	}
	return listNodes;
}

TEST(Given, Example1) {
	/*
	Example 1:

	Input: head = [1,2,3,4,5], k = 2
	Output: [2,1,4,3,5]
	*/

	auto input = generateLinkedListNodes({ 1, 2, 3, 4, 5 });
	auto output = Solution().reverseKGroup(&input.front(), 2);

	std::vector<int> expectedResult{ 2,1,4,3,5 };
	for (auto val : expectedResult)
	{
		ASSERT_EQ(output->val, val);
		output = output->next;
	}
	ASSERT_EQ(output, nullptr);
}

TEST(Given, Example2) {
	/*
	Example 2:

	Input: head = [1,2,3,4,5], k = 3
	Output: [3,2,1,4,5]
	*/

	auto input = generateLinkedListNodes({ 1, 2, 3, 4, 5 });
	auto output = Solution().reverseKGroup(&input.front(), 3);

	std::vector<int> expectedResult{ 3,2,1,4,5 };
	for (auto val : expectedResult)
	{
		ASSERT_EQ(output->val, val);
		output = output->next;
	}
	ASSERT_EQ(output, nullptr);
}

TEST(Tests, Invalid) {
	// k == 0
	auto input = generateLinkedListNodes({ 1, 2, 3 });
	ASSERT_NO_THROW(Solution().reverseKGroup(&input.front(), 0));

	// k < 0
	ASSERT_NO_THROW(Solution().reverseKGroup(&input.front(), -1));

	// Empty list
	ASSERT_EQ(nullptr, Solution().reverseKGroup(nullptr, 1));

	// k > list size
	ASSERT_NO_THROW(Solution().reverseKGroup(&input.front(), static_cast<int>(input.size()) + 1));
}

TEST(Tests, singleNode) {
	auto input = generateLinkedListNodes({ 1 });
	auto output = Solution().reverseKGroup(&input.front(), 1);

	std::vector<int> expectedResult{ 1 };
	for (auto val : expectedResult)
	{
		ASSERT_EQ(output->val, val);
		output = output->next;
	}
	ASSERT_EQ(output, nullptr);
}

TEST(Tests, kEquals1) {
	std::vector<int> data = { 1, 2, 3, 4, 5 };
	auto input = generateLinkedListNodes(data);
	auto output = Solution().reverseKGroup(&input.front(), 1);

	for (auto val : data)
	{
		ASSERT_EQ(output->val, val);
		output = output->next;
	}
	ASSERT_EQ(output, nullptr);
}

TEST(Tests, listSizeEqualsK) {
	auto input = generateLinkedListNodes({ 1, 2, 3, 4, 5 });
	auto output = Solution().reverseKGroup(&input.front(), static_cast<int>(input.size()));

	for (auto val : { 5, 4, 3, 2, 1 })
	{
		ASSERT_EQ(output->val, val);
		output = output->next;
	}
	ASSERT_EQ(output, nullptr);
}

TEST(Tests, listSizeMultipleOfK) {
	auto input = generateLinkedListNodes({ 1, 2, 3, 4, 5 ,6 });
	auto output = Solution().reverseKGroup(&input.front(), 2);

	std::vector<int> expectedResult{ 2, 1, 4, 3, 6, 5 };
	for (auto val : expectedResult)
	{
		ASSERT_EQ(output->val, val);
		output = output->next;
	}
	ASSERT_EQ(output, nullptr);
}
