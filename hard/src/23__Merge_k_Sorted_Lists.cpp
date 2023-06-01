#include "23__Merge_k_Sorted_Lists.h"

ListNode* Solution::mergeKLists(std::vector<ListNode*>& lists)
{
	// Empty list
	if (lists.size() == 0)
		return nullptr;

	// Collect the pointers of each list ignoring empty
	std::vector<ListNode*> listHeads(lists.size());
	size_t i = 0;
	for (auto& list : lists)
	{
		if(list)
			listHeads.at(i) = list;
		i++;
	}

	// Assume any item as the lowest and pre-lowest
	ListNode** lowestHead = &(listHeads.at(0));
	ListNode* first = nullptr;
	ListNode* prev = nullptr;

	// Iterate while thre are items in the lists
	while (true)
	{
		// Find lowest head
		for (auto& head : listHeads)
		{
			if (!head)
				continue;

			if (!*lowestHead || (head && (*lowestHead)->val > head->val))
				lowestHead = &head;
		}

		// Is list done?
		if (!*lowestHead)
			break;

		// Track previous
		if (!prev)
			first = *lowestHead;
		else
			prev->next = *lowestHead;

		// Step the list
		prev = *lowestHead;
		*lowestHead = (*lowestHead)->next;
	}

	// Clean the next pointer
	if(prev)
		prev->next = nullptr;

	// We received a list of empty nodes, just return any of the nodes
	if (!first)
		return lists.at(0);

	return first;
}
