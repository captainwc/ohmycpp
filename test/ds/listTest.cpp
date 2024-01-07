#include <codecvt>

#include "algorithm/Utils.h"
#define DOCTEST
#include "common.h"
#include "list/ListNode.h"

TEST_CASE("list relevant") {
    SUBCASE("LNode") {
        List<int> list;
        for (int i = 0; i < 10; i++) {
            if (i % 2 == 0)
                list.push_back(i);
            else
                list.push_front(i);
        }

        REQUIRE_EQ(list.size(), 10);
        REQUIRE_EQ(list.dump(), "[9, 7, 5, 3, 1, 0, 2, 4, 6, 8]");

        CHECK_EQ(list[0].val, 9);
        CHECK_EQ(list[5].val, 0);
        CHECK_EQ(list[9].val, 8);

        CHECK_THROWS_AS(list[10], std::out_of_range);
        CHECK_THROWS_AS(list[-1], std::out_of_range);

        list.insert(list.head, 0);
        list.insert(list.head->next->next->next, 0);
        list.insert(list.tail, 0);
        CHECK_EQ(list.size(), 13);

        list.remove(0);
        CHECK_EQ(list.size(), 9);

        CHECK_EQ(list.dump(), "[9, 7, 5, 3, 1, 2, 4, 6, 8]");
    }

    SUBCASE("list insert") {
        LinkList list;
        for (int i = 0; i < 10; i++) {
            if (i % 2 == 0) {
                list.push_back(i);
            } else {
                list.push_front(i);
            }
        }
        CHECK_EQ("[9,7,5,3,1,0,2,4,6,8]", list.dump());
    }

    SUBCASE("LinkList::Iterator") {
        auto list = utils::list::getLinkList("1,3,2,4,5");

        std::for_each(list.begin(), list.end(), [](ListNode& node) {
            node.val *= node.val;
        });

        std::string str = utils::printer::list2String(list);
        CHECK_EQ("[1,9,4,16,25]", str);
    }
}