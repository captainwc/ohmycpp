/**
 * BRIEF: 两两交换链表的元素，如 1 2 3 4 -> 2 1 4 3
 *
 * IDEA: 利用递归的定义。函数返回的是已经交换好的，所以只需要处理前两个
 *
 * LINK: https://leetcode.cn/problems/swap-nodes-in-pairs/submissions/476908878/
 *
 * Create by shuaikai 2023/10/24 19:33:12
 * Copyright (c) shuaikai. All rights reserved.
 */

#include "algorithm/Utils.h"
#include "common.h"
#include "list/ListNode.h"

using namespace std;

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        if (head->next == nullptr) {
            return head;
        }

        auto newHead = head->next;
        auto r = head->next->next;
        head->next->next = head;
        head->next = swapPairs(r);
        return newHead;
    }
};

int main() {
    Solution su;
    LinkList list = utils::list::getLinkList("1,2,3,4");
    utils::printer::printLinkList(su.swapPairs(list.front()));
    return 0;
}