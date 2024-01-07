/**
 * Create by shuaikai 2023/10/23 20:11:06
 *
 * @brief for leetcode
 *
 * Copyright (c) shuaikai. All rights reserved.
 */

#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <iterator>
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
    LinkList();
    LinkList(ListNode* head, int size);

    bool empty() const;
    int size() const;

    void push_back(int);
    void push_front(int);
    void pop_back();
    void pop_front();

    ListNode* head() const;
    ListNode* front() const;
    ListNode* back() const;

    std::string dump() const;

    class Iterator;
    Iterator begin() const;
    Iterator end() const;
    const Iterator cbegin() const;
    const Iterator cend() const;

private:
    int size_;
    ListNode* head_;
    ListNode* tail_;
};

class LinkList::Iterator {
public:
    // 定义一些别名方便复制粘贴
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = ListNode;        // 迭代器指向的类型
    using reference = const ListNode&;  // 迭代器指向类型的引用
    using pointer = ListNode*;          // 迭代器指向类型的指针

    Iterator() = default;
    Iterator(pointer);

    Iterator& operator=(const Iterator&);
    bool operator==(const Iterator&) const;
    bool operator!=(const Iterator&) const;

    //? 参数 int 不会被使用，只是用做区分。带 int 的是后置
    //! 后置不返回引用。原因参见实现，因为需要用到local临时变量，返回引用的话就会返回一个栈变量的引用，不行
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);

    value_type& operator*();

private:
    pointer curr_;
};

#endif  // LIST_NODE_H