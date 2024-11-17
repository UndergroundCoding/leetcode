#include "gtest/gtest.h"

#include "135__Candy.h"



namespace _135 {
	TEST(Test_135__Candy, Example1) {
		//Example 1:
		//Input: ratings = [1, 0, 2]
		//Output : 5
		//Explanation : You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

		Solution solution{};
		std::vector<int> ratings{ 1, 0, 2 };
		// 0 0 1
		// 1 0 0
		ASSERT_EQ(solution.candy(ratings), 5);
	}

	TEST(Test_135__Candy, Example2) {
		//Example 2 :
		//	Input : ratings = [1, 2, 2]
		//	Output : 4
		//	Explanation : You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
		//	The third child gets 1 candy because it satisfies the above two conditions.

		Solution solution{};
		std::vector<int> ratings{ 1, 2, 2 };
		ASSERT_EQ(solution.candy(ratings), 4);
	}

	TEST(Test_135__Candy, Failed1) {
		Solution solution{};
		std::vector<int> ratings{ 1, 3, 2, 2, 1 };
		// 0 1 0 0 0
		// 0 1 0 1 0
		ASSERT_EQ(solution.candy(ratings), 7);
	}

	TEST(Test_135__Candy, Failed2) {
		Solution solution{};
		std::vector<int> ratings{ 1,2,87,87,87,2,1 };
		// 0 1 2 0 0 0 0
		// 0 0 0 0 2 1 0
		ASSERT_EQ(solution.candy(ratings), 13);
	}

	TEST(Test_135__Candy, Custom1) {
		Solution solution{};
		std::vector<int> ratings{ 1,2,87,87,87,3, 2, 1 };
		ASSERT_EQ(solution.candy(ratings), 17);
	}

	TEST(Test_135__Candy, Failed3) {
		Solution solution{};
		std::vector<int> ratings{ 29,51,87,87,72,12 };
		// 0 1 2 0 0 0
		// 0 0 0 2 1 0
		ASSERT_EQ(solution.candy(ratings), 12);
	}

	TEST(Test_135__Candy, Failed4) {
		Solution solution{};
		std::vector<int> ratings{ 1,2,3,1,0 };
		// 0 1 2 0 0
		// 0 0 2 1 0
		ASSERT_EQ(solution.candy(ratings), 9);
	}
}