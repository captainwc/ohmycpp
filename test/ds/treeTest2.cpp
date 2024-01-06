#include "../../include/tree/TNode.h"

// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #include <doctest.h>

// TEST_CASE("TNode test, which using Shared_ptr") {
// 	SUBCASE("build") {
// 		auto vals = std::vector<int>{ -1, 1, 2, 3, 4, 5, 6, 7 };
// 		auto root = createTree<int>(vals);
// 		std::cout << root->val << std::endl;
// 	}
// }

int main() {
    auto vals = std::vector<int>{-1, 1, 2, 3, 4, 5, 6, 7};
    auto root = createTree<int>(vals);
    std::cout << root->val << std::endl;
}