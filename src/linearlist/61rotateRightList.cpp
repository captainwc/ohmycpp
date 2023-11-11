/**
 * BRIEF: 右移链表元素
 *
 * IDEA: 形成一个环，找出移动后新的头，然后断开其前一个的next即可
 *
 * LINK: https://leetcode.cn/problems/rotate-list/
 *
 * Create by shuaikai 2023/10/25 10:13:05
 * Copyright (c) shuaikai. All rights reserved.
 */

#include "algorithm/Utils.h"
#include "common.h"

using namespace std;

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr)
            return nullptr;
        auto pNode = head;
        vector<ListNode*> nodes;
        while (pNode->next != nullptr) {
            nodes.emplace_back(pNode);
            pNode = pNode->next;
        }
        pNode->next = head;
        nodes.emplace_back(pNode);
        int step = k % nodes.size();
        int idx = (step == 0) ? 0 : (nodes.size() - step);
        int prev = (idx == 0) ? (nodes.size() - 1) : (idx - 1);
        nodes[prev]->next = nullptr;
        return nodes[idx];
    }
};

int main() {
    Solution su;
    auto list = getLinkList("1,2,3,4,5");
    printLinkList(su.rotateRight(list, 2));

    return 0;
}