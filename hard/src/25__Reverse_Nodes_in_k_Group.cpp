#include "25__Reverse_Nodes_in_k_Group.h"

#include <algorithm>
#include <vector>

ListNode* Solution::reverseKGroup(ListNode* head, int k)
{
	if (!head || !head->next || k <= 1)
	{
		// Single element, nothing to do
		return head;
	}

	// Keep track of current position in list
	ListNode* pos = head;

	while (pos)
	{
		// Store nodes in an array for index-access
		std::vector<ListNode*> group;

		// Steps through each node to ensure the list has enough elements
		for (int i = 0; i < k; i++)
		{
			if (!pos)
			{
				// Not enough elements, return group-reversed list
				return head;
			}

			// Keep track of each node
			group.push_back(pos);

			// Step node
			pos = pos->next;
		}

		// Start swapping
		for (int i = 0; i < k / 2; i++)
		{
			// Swap left-most value with right-most value in group
			std::swap(group[i]->val, group[k - (i + 1)]->val);
		}
	}

	return head;
}
