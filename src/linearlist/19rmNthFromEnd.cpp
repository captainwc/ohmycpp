/**
 * BRIEF: remove the Nth node from end of a linklist
 *
 * IDEA: 快慢指针，快的先走 k 步，然后到底的时候慢的就是倒数第 k 个。（实际上 size - k 也不慢）
 *
 * LINK: https://leetcode.cn/problems/remove-nth-node-from-end-of-list/
 *
 * Create by shuaikai 2023/10/24 18:47:19
 * Copyright (c) shuaikai. All rights reserved.
 */

#include "common.h"

using namespace std;

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // I. 求size，然后size-n => O(2n)
        // II. 双指针：快比慢先行 n 步，则快到底时，慢到倒数第 n 个
        auto fast = head;
        auto slow = head;
        ListNode* prev = nullptr;
        for (int i = 0; i < n - 1 && fast != nullptr; i++, fast = fast->next) {
            // 应当保证存在倒数第n个元素
        }
        if (fast == nullptr) {
            return head;
        }
        while (fast->next != nullptr) {
            fast = fast->next;
            prev = slow;
            slow = slow->next;
        }
        if (prev == nullptr) {
            if (slow->next == nullptr) {
                return nullptr;
            } else {
                return slow->next;
            }
        } else {
            prev->next = slow->next;
            return head;
        }
    }
};

int main() {
    Solution su;

    return 0;
}