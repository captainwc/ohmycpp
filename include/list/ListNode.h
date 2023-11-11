/**
 * Create by shuaikai 2023/10/23 20:11:06
 *
 * @brief for leetcode
 *
 * Copyright (c) shuaikai. All rights reserved.
 */

#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <memory>
#include <string>

struct ListNode {
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {
    }

    ListNode(int x) : val(x), next(nullptr) {
    }

    ListNode(int x, ListNode* next) : val(x), next(next) {
    }
};

class LinkList {
public:
    LinkList() {
        head_ = new ListNode();
        tail_ = head_;
        size_ = 0;
    }

    LinkList(ListNode* head, int size) {
        head_ = head;
        size_ = size;
    }

    bool empty() {
        return size_ == 0;
    }

    void push_back(int val) {
        auto node = new ListNode(val);
        if (empty()) {
            head_->next = node;
            tail_ = node;
        } else {
            tail_->next = node;
            tail_ = node;
        }
        size_++;
    }

    void push_front(int val) {
        auto node = new ListNode(val);
        if (empty()) {
            head_->next = node;
            tail_ = node;
        } else {
            node->next = head_->next;
            head_->next = node;
        }
        size_++;
    }

    void pop_back() {
        if (empty()) {
            return;
        }
        auto node = head_;
        while (node->next != tail_) {
            node = node->next;
        }
        delete tail_;
        tail_ = node;
        tail_->next = nullptr;
        size_--;
    }

    void pop_front() {
        if (empty()) {
            return;
        }
        auto node = head_->next;
        head_->next = node->next;
        delete node;
        size_--;
    }

    ListNode* front() {
        if (empty()) {
            return nullptr;
        }
        return head_->next;
    }

    ListNode* back() {
        if (empty()) {
            return nullptr;
        }
        return tail_;
    }

    int size() {
        return size_;
    }

    std::string dump() {
        std::string str = "[";
        auto pNode = head_->next;
        while (pNode != nullptr) {
            str.append(std::to_string(pNode->val) + ",");
            pNode = pNode->next;
        }
        str.pop_back();
        str.append("]");
        return str;
    }

private:
    int size_;
    ListNode* head_;
    ListNode* tail_;
};

#endif  // LIST_NODE_H