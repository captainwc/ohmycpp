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

#include <bits/stdc++.h>
using namespace std;

/**
关键在于：
（1）链表中删除了节点，那么map中对应的键值也要删除！
（2）上一条要求，node中不仅要存放value，还要存放key
*/
struct DLNode {
    int     key;
    int     val;
    DLNode* prev;
    DLNode* next;
    DLNode() = default;

    DLNode(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {
    }

    ~DLNode() {
        delete next;
    }
};

class DList {
private:
    DLNode* head;
    DLNode* tail;
    int     size_;

public:
    DList() : size_(0) {
        head       = new DLNode();
        tail       = new DLNode();
        head->next = tail;
        tail->prev = head;
    }

    ~DList() {
        delete head;
    }

    [[nodiscard]] bool empty() const {
        return size_ == 0;
    }

    [[nodiscard]] int size() const {
        return size_;
    }

    void push_back(DLNode* p) {
        if (empty()) {
            p->next    = tail;
            p->prev    = head;
            head->next = p;
            tail->prev = p;
        } else {
            p->next       = tail;
            p->prev       = tail->prev;
            tail->prev    = p;
            p->prev->next = p;
        }
        size_++;
    }

    optional<DLNode*> pop() {
        if (!empty()) {
            auto p        = head->next;
            head->next    = p->next;
            p->next->prev = head;
            size_--;
            return make_optional<DLNode*>(p);
        }
        return nullopt;
    }

    DLNode* pop_front() {
        if (!empty()) {
            auto p        = head->next;
            head->next    = p->next;
            p->next->prev = head;
            size_--;
            return p;
        }
        return nullptr;
    }

    void move2back(DLNode* p) {
        if (p->next != tail) {
            p->prev->next = p->next;
            p->next->prev = p->prev;
            size_--;
            push_back(p);
        }
    }
};

class LRUCache {
private:
    unordered_map<int, DLNode*> cache;
    DList                       list;
    int                         capacity;

public:
    explicit LRUCache(int capacity) : capacity(capacity) {
    }

    int get(int key) {
        if (cache.count(key) == 0) {
            return -1;
        }
        auto p = cache[key];
        list.move2back(p);
        return p->val;
    }

    void put(int key, int value) {
        if (cache.count(key) == 0) {
            if (list.size() >= capacity) {
                // ! 关键步骤
                auto p = list.pop_front();
                cache.erase(p->key);
                // ！注意这里无需 delete p！因为list会被析构，list包含p
            }
            auto q     = new DLNode(key, value);
            cache[key] = q;
            list.push_back(q);
        } else {
            auto p = cache[key];
            list.move2back(p);
            p->val = value;
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