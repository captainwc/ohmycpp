/**
 * BRIEF: LRU设计与实现
 *
 * IDEA: 哈希+双向链表
 *
 * LINK: 嘻嘻嘻
 *
 * Create by shuaikai 2024/03/07 22:29:57
 * Copyright (c) shuaikai. All rights reserved.
 */

#include "leetcode/lc.h"

struct LstNode {
    int      val;
    LstNode* prev;
    LstNode* next;

    explicit LstNode(int v, LstNode* p = nullptr, LstNode* n = nullptr) : val(v), prev(p), next(n) {
    }

    ~LstNode() {
        delete next;
    }
};

class List {
private:
    LstNode* head_;
    LstNode* tail_;
    int      size_;

public:
    List() : size_(0) {
        head_       = new LstNode(-1);
        tail_       = new LstNode(-2);
        head_->next = tail_;
        tail_->prev = head_;
    }

    ~List() {
        delete head_;
    }

    bool empty() {
        return head_->next = tail_;
    }

    int size() {
        return size_;
    }

    void pop_back() {
        if (!empty()) {
            auto p        = tail_->prev;
            tail_->prev   = p->prev;
            p->prev->next = tail_;
            delete p;
            size_--;
        }
    }

    void push_front(LstNode* p) {
        if (empty()) {
            head_->next = p;
            p->prev     = head_;
            p->next     = tail_;
            tail_->prev = p;
        } else {
            p->next       = head_->next;
            p->prev       = head_;
            p->next->prev = p;
            head_->next   = p;
        }
        size_++;
    }

    void move_to_head(LstNode* p) {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        size_--;
        push_front(p);
    }
};

class LRUCache {
private:
    unordered_map<int, LstNode*> mp;
    List                         lst;
    int                          capacity;

public:
    LRUCache(int capacity) : capacity(capacity) {
    }

    int get(int key) {
        if (mp.find(key) != mp.end()) {
            auto target = mp[key];
            lst.move_to_head(target);
            return target->val;
        }
        return -1;
    }

    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            auto target = mp[key];
            target->val = value;
            lst.move_to_head(target);
        } else {
            if (lst.size() == capacity) {
                lst.pop_back();
            }
            auto p  = new LstNode(value);
            mp[key] = p;
            lst.push_front(p);
        }
    }
};

int main() {
    LRUCache lru(2);
    lru.put(1, 1);
    lru.put(2, 2);
    lru.get(1);
    lru.put(3, 3);
    lru.get(2);
    lru.put(4, 4);
    lru.get(1);
    lru.get(3);
    lru.get(4);
    return 0;
}