#include "algorithm/Sorter.h"
#include "list/List.h"
#define DOCTEST
#include "common.h"

TEST_CASE("quickSort") {
	SUBCASE("sort vector") {
		std::vector<int> arr1{ 2, 3, 8, 4, 6, 9, 1, 0 };
		quickSort(arr1, arr1.size());
		for (auto x : arr1) {
			std::cout << x << ' ';
		}
		std::cout << std::endl;
	}

	SUBCASE("sort ListNode") {
		List<int> list;
		for (int i = 0; i < 10; i++) {
			if (i % 2 == 0)
				list.push_back(i);
			else
				list.push_front(i);
		}
		CHECK_EQ(list.dump(), "[9, 7, 5, 3, 1, 0, 2, 4, 6, 8]");

		quickSort(list, list.size());
		CHECK_EQ(list.dump(), "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]");
	}
}
