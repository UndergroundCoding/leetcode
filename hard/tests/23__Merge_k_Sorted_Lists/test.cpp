#include "gtest/gtest.h"

#include "23__Merge_k_Sorted_Lists.h"

#include <random>

std::vector<ListNode> generateLinkedListNodes(std::vector<int> values)
{
	if (values.empty())
		return std::vector<ListNode>(1);

	std::vector<ListNode> listNodes(values.size());
	for (auto& itListNode = listNodes.begin(); itListNode != listNodes.end(); itListNode++)
	{
		if (itListNode + 1 != listNodes.end())
			itListNode->next = &*(itListNode + 1);		// Dereference the iterator and take address

		auto pos = itListNode - listNodes.begin();
		itListNode->val = values.at(pos);
	}
	return listNodes;
}

TEST(TestHelper, generateLinkedListNodes) {
	// Non-empty list
	auto listNodes = generateLinkedListNodes({ 1, 4, 5 });

	auto listNode = listNodes.at(0);

	ASSERT_EQ(listNode.val, 1);
	ASSERT_EQ(listNode.next->val, 4);
	ASSERT_EQ(listNode.next->next->val, 5);
	ASSERT_EQ(listNode.next->next->next, nullptr);

	// Empty list
	listNodes = generateLinkedListNodes({});
	listNode = listNodes.at(0);
	ASSERT_EQ(listNode.val, 0);
	ASSERT_EQ(listNode.next, nullptr);
}

TEST(Given, Example1) {
	/*
	Example 1:

	Input: lists = [[1,4,5],[1,3,4],[2,6]]
	Output: [1,1,2,3,4,4,5,6]
	Explanation: The linked-lists are:
	[
	  1->4->5,
	  1->3->4,
	  2->6
	]
	merging them into one sorted list:
	1->1->2->3->4->4->5->6
	*/

	auto list1 = generateLinkedListNodes({ 1,4,5 });
	auto list2 = generateLinkedListNodes({ 1,3,4 });
	auto list3 = generateLinkedListNodes({ 2,6 });

	std::vector<ListNode*> listNodes{ &list1.at(0), &list2.at(0), &list3.at(0) };

	auto listNode = Solution().mergeKLists(listNodes);

	std::vector<int> expectedResult{ 1,1,2,3,4,4,5,6 };
	for (auto val : expectedResult)
	{
		ASSERT_EQ(listNode->val, val);
		listNode = listNode->next;
	}
	ASSERT_EQ(listNode, nullptr);
}

TEST(Given, Example2) {
	/*
	Example 2:

	Input: lists = []
	Output: []
	*/

	std::vector<ListNode*> listNodes{};

	auto listNode = Solution().mergeKLists(listNodes);

	ASSERT_EQ(listNode, nullptr);
}

TEST(Given, Example3) {
	/*
	Example 3:

	Input: lists = [[]]
	Output : []
	*/

	std::vector<ListNode*> listNodes{ nullptr };

	auto listNode = Solution().mergeKLists(listNodes);

	ASSERT_EQ(listNode, nullptr);
}

TEST(Tests, Various)
{
	auto list1 = generateLinkedListNodes({ 0,1,4,5 });
	auto list2 = generateLinkedListNodes({ 0, 0, 100 });
	ListNode default{};

	std::vector<ListNode*> listNodes{ nullptr, &list1.at(0),  &list2.at(0), nullptr, &default };
	auto listNode = Solution().mergeKLists(listNodes);

	std::vector<int> expectedResult{ 0,0,0,0,1,4,5,100 };
	for (auto val : expectedResult)
	{
		ASSERT_EQ(listNode->val, val);
		listNode = listNode->next;
	}
	ASSERT_EQ(listNode, nullptr);
}

TEST(Tests, RandomlyGenerated)
{
	// Constraints
	constexpr int MaxLists = 10000;	// 10^4
	constexpr int MaxNodesPerList = 500;
	constexpr int MaxNodes = 10000;	// 10^4
	constexpr int MinVal = -10000;	// -10^4
	constexpr int MaxVal = 10000;	// 10^4

	// Prepare random generator
	std::random_device rnd_device;
	std::mt19937 mersenne_engine{ rnd_device() };

	std::vector<int> expectedResult{};
	expectedResult.reserve(MaxNodes);

	// Determine how many lists to create
	std::uniform_int_distribution<int> nListsDist{ 0, MaxNodesPerList };
	auto nLists = nListsDist(mersenne_engine);
	std::vector<std::vector<ListNode>> listLists(nLists);

	// Generate the lists
	int totalNodes = 0;
	for(int i = 0; i < nLists && totalNodes < MaxNodes; i++)
	{
		// Generate a vector of random size
		std::uniform_int_distribution<int> listSizeDist{ 0, MaxNodesPerList };
		auto listSize = listSizeDist(mersenne_engine);
		listSize = totalNodes + listSize > MaxNodes ? MaxNodes - totalNodes : listSize;
		auto& list = listLists.at(i);
		list.resize(listSize);

		// Iterate the vector assigning random values
		for (auto& node : list)
		{
			std::uniform_int_distribution<int> valDist{ MinVal, MaxVal };
			auto val = valDist(mersenne_engine);
			node.val = val;

			// Add the value to the expected result as well
			expectedResult.push_back(val);
		}

		// Sort the vector
		std::sort(list.begin(), list.end(), [](auto& a, auto& b)
			{
				return a.val < b.val;
			});

		// Iterate the vector linking the nodes
		if (list.size() > 0)
		{
			for (auto it = list.begin(); it != list.end() - 1; it++)
			{
				it->next = &*(it + 1);
			}
		}

		totalNodes += listSize;
	}

	// Sort the expected results
	std::sort(expectedResult.begin(), expectedResult.end());

	// Convert the list of lists into a list of node pointers
	std::vector<ListNode*> lists{};
	lists.reserve(listLists.size());
	for (auto& list : listLists)
	{
		if (list.size() == 0)
			lists.push_back(nullptr);
		else
			lists.push_back(&list.at(0));
	}

	// Run and check
	auto listNode = Solution().mergeKLists(lists);
	for (auto val : expectedResult)
	{
		ASSERT_EQ(listNode->val, val);
		listNode = listNode->next;
	}
	ASSERT_EQ(listNode, nullptr);
}