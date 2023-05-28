/*	https://leetcode.com/problems/median-of-two-sorted-arrays/
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).



Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.


Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-10^6 <= nums1[i], nums2[i] <= 10^6
*/


#include "4__Median_of_Two_Sorted_Arrays.h"

#include <numeric>

using namespace std;

double Solution::findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	// Split both arrays at a location such that the number of elements in the 2 lower end of the arrays
	// is the same as the number of elements in the 2 higher ends.
	//
	// Check if the smaller array's lower end is smaller than the larger array's higher end
	// Check if the smaller array's higher end is greater than the larger array's lower end
	// 
	// Adjust cutoff on lower array, try again

	// Identify the smaller and larger arrays
	auto& shorterArr = nums1;
	auto& longerArr = nums2;
	if (shorterArr.size() > longerArr.size())
		swap(shorterArr, longerArr);

	// Edge case: empty array
	if (shorterArr.size() == 0)
	{
		auto cutoff = (longerArr.size() - 1) / 2;
		double median = longerArr[cutoff];
		if (longerArr.size() % 2 == 0)
			median = (median + longerArr[cutoff + 1]) / 2;
		return median;
	}

	// Calculate cutoff of smaller array (cutoff always belongs to array of lower values)
	int startPos = 0;
	int endPos = (int)shorterArr.size() - 1;		// Safe casting due to problem contraints
	int cutoffPos1 = (endPos + startPos) / 2;

	// Calculate cutoff of larger array such that the sum of the sizes of the two low arrays is the same as the sum of the sizes of the two high arrays
	auto totalsize = (int)(shorterArr.size() + longerArr.size());		// Safe casting due to problem contraints
	int cutoffPos2 = (totalsize - 1) / 2 - cutoffPos1 - 1;		// There is always at least 1 element from the shorter array

	while ((cutoffPos1 >= 0 && cutoffPos1 < shorterArr.size()) && (cutoffPos2 >= 0 && cutoffPos2 < longerArr.size()))
	{
		// Check if all elements on the left of the smaller array is equal to or smaller than those of the right side of the larger array
		if (shorterArr[cutoffPos1] > longerArr[cutoffPos2 + 1])
		{
			// Move cutoff to the left
			if (cutoffPos1 == 0)
			{
				// All elements on the shorter array are smaller than the smallest element in the longer array
				cutoffPos1 = -1;
				++cutoffPos2;
				break;
			}
			endPos = cutoffPos1;
		}
		else if ((cutoffPos1 + 1 < shorterArr.size())	// Edge case: No elements to the right of shorter array's cutoff
			&& (longerArr[cutoffPos2] > shorterArr[cutoffPos1 + 1]))
		{
			// Move cutoff to the right
			startPos = cutoffPos1 + 1;
		}
		else
		{
			// Found cutoff
			break;
		}

		// Recalculate cutoffs
		cutoffPos1 = (endPos + startPos) / 2;
		cutoffPos2 = (totalsize - 1) / 2 - cutoffPos1 - 1;
	}

	// Calculate median
	auto shorterArrHighestLow = (cutoffPos1 < 0) || (cutoffPos1 >= shorterArr.size()) ? numeric_limits<int>::min() : shorterArr[cutoffPos1];
	auto longerArrHighestLow = (cutoffPos2 < 0) || (cutoffPos2 >= longerArr.size()) ? numeric_limits<int>::min() : longerArr[cutoffPos2];
	double median = max(shorterArrHighestLow, longerArrHighestLow);
	if (totalsize % 2 == 0)
	{
		// Median in between two values
		auto shorterArrLowestHigh = (cutoffPos1 + 1 < 0) || (cutoffPos1 + 1 >= shorterArr.size()) ? numeric_limits<int>::max() : shorterArr[cutoffPos1 + 1];
		auto longerArrLowestHigh = (cutoffPos2 + 1 < 0) || (cutoffPos2 + 1 >= longerArr.size()) ? numeric_limits<int>::max() : longerArr[cutoffPos2 + 1];
		median = (median + min(shorterArrLowestHigh, longerArrLowestHigh)) / 2;
	}

	return median;
}