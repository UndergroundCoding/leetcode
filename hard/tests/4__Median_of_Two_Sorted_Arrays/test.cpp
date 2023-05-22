#include "gtest/gtest.h"

#include "4__Median_of_Two_Sorted_Arrays.h"

#include <vector>
#include <random>

TEST(Given, Example1) {
	//	Example 1:
	//
	//Input: nums1 = [1, 3], nums2 = [2]
	//Output : 2.00000

	std::vector<int> nums1{ 1, 3 };
	std::vector<int> nums2{ 2 };
	ASSERT_DOUBLE_EQ(2.0, Solution().findMedianSortedArrays(nums1, nums2));
}

TEST(Given, Example2)
{
	//Example 2 :
	//
	//	Input : nums1 = [1, 2], nums2 = [3, 4]
	//	Output : 2.50000

	std::vector<int> nums1{ 1, 2 };
	std::vector<int> nums2{ 3, 4 };
	ASSERT_DOUBLE_EQ(2.5, Solution().findMedianSortedArrays(nums1, nums2));
}

TEST(Tests, array_order_doesnt_matter)
{
	std::vector<int> nums1{ 1, 2 };
	std::vector<int> nums2{ 3, 4 };
	ASSERT_DOUBLE_EQ(2.5, Solution().findMedianSortedArrays(nums1, nums2));
	ASSERT_DOUBLE_EQ(2.5, Solution().findMedianSortedArrays(nums2, nums1));
}

TEST(Tests, one_empty_array)
{
	std::vector<int> nums1{};
	std::vector<int> nums2{ 3, 4, 5 };
	ASSERT_DOUBLE_EQ(4, Solution().findMedianSortedArrays(nums1, nums2));
	ASSERT_DOUBLE_EQ(4, Solution().findMedianSortedArrays(nums2, nums1));
}

TEST(Tests, all_items_in_shorter_array_smaller_than_items_in_longer_array)
{
	std::vector<int> nums1{ 1, 2 };
	std::vector<int> nums2{ 3, 4, 5 };
	ASSERT_DOUBLE_EQ(3, Solution().findMedianSortedArrays(nums1, nums2));
}

TEST(Tests, all_items_in_shorter_array_larger_than_items_in_longer_array)
{
	std::vector<int> nums1{ 1, 2, 3 };
	std::vector<int> nums2{ 4, 5 };
	ASSERT_DOUBLE_EQ(3, Solution().findMedianSortedArrays(nums1, nums2));
}

TEST(Tests, two_single_element_arrays)
{
	std::vector<int> nums1{ 1 };
	std::vector<int> nums2{ 3 };
	ASSERT_DOUBLE_EQ(2, Solution().findMedianSortedArrays(nums1, nums2));
	ASSERT_DOUBLE_EQ(2, Solution().findMedianSortedArrays(nums2, nums1));
}

TEST(Tests, randomly_generated_arrays)
{
	// Constraints
	constexpr int maxCombinedArrSize = 2000;
	constexpr int minCombinedArrSize = 1;
	constexpr int maxArrSize = 1000;
	constexpr int minArrSize = 0;
	constexpr int maxValue = 1000000; // 10^6
	constexpr int minValue = -1000000;  // -10^6

	// Prepare random generator
	std::random_device rnd_device;
	std::mt19937 mersenne_engine{ rnd_device() };

	for (int i = 0; i < 1000; i++)
	{
		// Create an array of random size fitting the constraints
		std::uniform_int_distribution<int> arraySizeDist{ minCombinedArrSize, maxCombinedArrSize };
		auto combinedArrSize = arraySizeDist(mersenne_engine);
		std:: vector<int> combinedArr(combinedArrSize);

		// Fill it with random ints within the given constraints
		std::uniform_int_distribution<int> intValueDist{ minValue, maxValue };
		generate(begin(combinedArr), end(combinedArr), [&intValueDist, &mersenne_engine]() {
			return intValueDist(mersenne_engine);
			}
		);

		// Split the array at a random point before sorting
		std::uniform_int_distribution<int> singleArraySizeDist{ minArrSize, combinedArrSize };
		auto splitPos = cbegin(combinedArr) + singleArraySizeDist(mersenne_engine);
		std::vector<int> nums1(cbegin(combinedArr), splitPos);
		sort(nums1.begin(), nums1.end());
		std::vector<int> nums2(splitPos, cend(combinedArr));
		sort(nums2.begin(), nums2.end());

		// Find the median
		sort(combinedArr.begin(), combinedArr.end());
		auto centerPos = (combinedArrSize - 1) / 2;
		double median = combinedArr[centerPos];	// Assume odd-sized array
		if (combinedArr.size() % 2 == 0)
		{
			// Even array, must consider the 2 center values
			median = (median + combinedArr[centerPos + 1]) / 2;
		}

		// Run test
		Solution solution{};
		auto calculatedMedian = solution.findMedianSortedArrays(nums1, nums2);
		ASSERT_DOUBLE_EQ(median, calculatedMedian);
	}
}