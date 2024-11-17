#pragma once

/*
There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.

Example 1:
Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

Example 2:
Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.


Constraints:

n == ratings.length
1 <= n <= 2 * 104
0 <= ratings[i] <= 2 * 104
*/

#include <vector>
#include <algorithm>
#include <numeric>

namespace _135
{
	class Solution {
	public:
		int candy(std::vector<int>& ratings) {
			auto reverse_ratings = ratings;
			std::reverse(reverse_ratings.begin(), reverse_ratings.end());

			auto adjustments1 = onewayAdjustments(ratings);
			auto adjustments2 = onewayAdjustments(reverse_ratings);
			std::reverse(adjustments2.begin(), adjustments2.end());

			std::vector<int> combined_adjustments(ratings.size());
			std::transform(adjustments1.cbegin(), adjustments1.cend(), adjustments2.cbegin(), combined_adjustments.begin(), [](const int& lhs, const int& rhs) {
				return std::max(lhs, rhs);
				});

			auto adjustment_sum = 0;
			for (const auto& adjustment : combined_adjustments) {
				adjustment_sum += adjustment;
			}

			return static_cast<int>(ratings.size() + adjustment_sum);
		}

		static std::vector<int> onewayAdjustments(std::vector<int>& ratings) {
			std::vector<int> adjustments(ratings.size());
			int last_given = 0;
			auto previous_rating = std::numeric_limits<int>::max();
			for (auto i = 0; i < ratings.size(); i++) {
				auto rating = ratings.at(i);

				if (rating > previous_rating) {
					last_given++;
				}
				else {
					last_given = 0;
				}

				previous_rating = rating;
				adjustments.at(i) = last_given;
			}

			return adjustments;
		}
	};
}