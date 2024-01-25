/**
 * Create by shuaikai 2024/01/08 21:39:46
 *
 * Ref: https://www.cnblogs.com/wengle520/p/12492708.html
 *
 * Copyright (c) shuaikai. All rights reserved.
 */

#ifndef B_LIST_H
#define B_LIST_H

#include <string>

#include "BLNode.h"

template <typename T>
class BList {
private:
    int        _size;
    BLNode<T>* _head;
    BLNode<T>* _tail;

public:
    BList();

    BLNode<T>& operator[](int idx);

    class Iterator;

    Iterator        begin() const;
    Iterator        end() const;
    const Iterator& cbegin() const;
    const Iterator& cend() const;

    void push_front(T val);
    void push_back(T val);

    BLNode<T>* pop_front();
    BLNode<T>* pop_back();

    BLNode<T>* find(T val) const;

    void remove(BLNode<T>* pNode);
    void remove(T val);
    void insert(BLNode<T>* pNode, T val);

    std::vector<BLNode<T>*> toVector() const;
    std::string             dump() const;

    void print() const {
        std::cout << this->dump() << std::endl;
    }

    bool empty() const {
        return _size == 0;
    }

    bool inList(BLNode<T>* p) const {
        return !((p == nullptr) || (p->prev == nullptr && p->next == nullptr));
    }

    int size() const {
        return _size;
    }

    BLNode<T>& front() const {
        return _head;
    }

    BLNode<T>* back() const {
        return _tail;
    }
};

//==------------------------ Iterator --------------------------==//

template <typename T>
class BList<T>::Iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = BLNode<T>;        // 迭代器指向的类型
    using reference = const BLNode<T>&;  // 迭代器指向类型的引用
    using pointer = BLNode<T>*;          // 迭代器指向类型的指针

    Iterator() = default;
    Iterator(pointer);

    bool isNull() const {
        return curr_ == nullptr;
    }

    Iterator& operator=(const Iterator&);

    bool operator==(const Iterator&) const;
    bool operator!=(const Iterator&) const;
    bool operator>(const Iterator&) const;
    bool operator<(const Iterator&) const;
    bool operator>=(const Iterator&) const;
    bool operator<=(const Iterator&) const;

    Iterator& operator++();
    Iterator  operator++(int);
    Iterator& operator--();
    Iterator  operator--(int);

    Iterator& operator+(int);
    Iterator& operator-(int);
    int       operator-(const Iterator&) const;

    value_type& operator*();
    pointer     operator->();

    // TODO 友元模板重载，到底应该怎么写？
    // friend typename BList<T>::Iterator& operator+(const Iterator& a, int b);
    // friend Iterator& operator-(const Iterator& a, int b);
    // friend Iterator& operator+(int a, const Iterator& b);
    // friend Iterator& operator-(int a, const Iterator& b);
    // friend Iterator& operator+(const Iterator& a, int b);
    // friend Iterator& operator-(const Iterator& a, int b);

private:
    pointer curr_;
};

//==---------------------- BList Implemention ------------------------==//

template <typename T>
BList<T>::BList() {
    _head = new BLNode<T>();
    _tail = _head;
    _size = 0;
}

template <typename T>
void BList<T>::push_front(T val) {
    auto node = new BLNode<T>(val);
    if (empty()) {
        _head->next = node;
        node->prev = _head;
        _tail = node;
    } else {
        node->next = _head->next;
        _head->next->prev = node;
        _head->next = node;
        node->prev = _head;
    }
    _size++;
}

template <typename T>
void BList<T>::push_back(T val) {
    auto node = new BLNode<T>(val);
    if (empty()) {
        _head->next = node;
        node->prev = _head;
        _tail = node;
    } else {
        _tail->next = node;
        node->prev = _tail;
        _tail = node;
    }
    _size++;
}

template <typename T>
BLNode<T>* BList<T>::pop_front() {
    if (empty()) {
        return nullptr;
    }
    auto pNode = _head->next;
    _head->next = pNode->next;
    pNode->next->prev = _head;
    pNode->next = nullptr;
    pNode->prev = nullptr;
    _size--;
    return pNode;
}

template <typename T>
BLNode<T>* BList<T>::pop_back() {
    if (empty()) {
        return nullptr;
    }
    auto pNode = _tail;
    _tail = _tail->prev;
    _tail->next = nullptr;
    pNode->prev = nullptr;
    _size--;
    return pNode;
}

template <typename T>
void BList<T>::remove(BLNode<T>* pNode) {
    if (!inList(pNode))
        return;
    if (pNode == _head)
        return;
    if (pNode == _head->next)
        pop_front();
    else if (pNode == _tail)
        pop_back();
    else {
        pNode->prev->next = pNode->next;
        pNode->next->prev = pNode->prev;
        _size--;
    }
}

template <typename T>
BLNode<T>* BList<T>::find(T val) const {
    auto p = _head->next;
    while (p != nullptr) {
        if (p->val == val)
            return p;
        p = p->next;
    }
    return nullptr;
}

template <typename T>
void BList<T>::remove(T val) {
    auto p = find(val);
    do {
        remove(p);
        p = find(val);
    } while (p != nullptr);
}

template <typename T>
void BList<T>::insert(BLNode<T>* pNode, T val) {
    if (!inList(pNode))
        return;
    if (pNode == _tail)
        push_back(val);
    else {
        auto node = new BLNode<T>(val);
        pNode->next->prev = node;
        node->next = pNode->next;
        node->prev = pNode;
        pNode->next = node;
        _size++;
    }
}

template <typename T>
std::vector<BLNode<T>*> BList<T>::toVector() const {
    auto ret = new std::vector<T>();
    auto p = _head->next;
    while (p != nullptr) {
        ret->push_back(p);
        p = p->next;
    }
    return ret;
}

template <typename T>
std::string BList<T>::dump() const {
    auto        p = _head->next;
    std::string str = "[";
    while (p->next != nullptr) {
        str.append(std::to_string(p->val)).append(", ");
        p = p->next;
    }
    return str.append(std::to_string(p->val)).append("]");
}

template <typename T>
BLNode<T>& BList<T>::operator[](int idx) {
    if (idx < 0)
        throw std::out_of_range("idx shouldn't be negative!");
    int  cnt = 0;
    auto p = _head->next;
    while (cnt < idx && p != nullptr) {
        cnt++;
        p = p->next;
    }
    if (cnt < idx || p == nullptr)
        throw std::out_of_range("idx out of range!");
    return *p;
}

//==----------------------- BList Iterator Implement ------------------------==/
template <typename T>
BList<T>::Iterator::Iterator(pointer p) {
    this->curr_ = p;
}

template <typename T>
typename BList<T>::Iterator& BList<T>::Iterator::operator=(const Iterator& it) {
    this->curr_ = it.curr_;
    return *this;
}

template <typename T>
bool BList<T>::Iterator::operator==(const Iterator& it) const {
    return this->curr_ == it.curr_;
}

template <typename T>
bool BList<T>::Iterator::operator!=(const Iterator& it) const {
    return this->curr_ != it.curr_;
}

template <typename T>
bool BList<T>::Iterator::operator>(const Iterator& it) const {
    auto p = it.curr_->next;
    while (p != nullptr) {
        if (p == this->curr_) {
            return true;
        }
        p = p->next;
    }
    return false;
}

template <typename T>
bool BList<T>::Iterator::operator<(const Iterator& it) const {
    if (!isNull()) {
        auto p = this->curr_->next;
        while (p != nullptr) {
            if (p == it.curr_) {
                return true;
            }
            p = p->next;
        }
    }
    return false;
}

template <typename T>
bool BList<T>::Iterator::operator>=(const Iterator& it) const {
    return *this > it || *this == it;
}

template <typename T>
bool BList<T>::Iterator::operator<=(const Iterator& it) const {
    return *this < it || *this == it;
}

template <typename T>
typename BList<T>::Iterator& BList<T>::Iterator::operator++() {
    curr_ = curr_->next;
    return *this;
}

template <typename T>
typename BList<T>::Iterator BList<T>::Iterator::operator++(int) {
    BList<T>::Iterator tmp = *this;
    curr_ = curr_->next;
    return tmp;
}

template <typename T>
typename BList<T>::Iterator& BList<T>::Iterator::operator--() {
    curr_ = curr_->prev;
    return *this;
}

template <typename T>
typename BList<T>::Iterator BList<T>::Iterator::operator--(int) {
    BList<T>::Iterator tmp = *this;
    curr_ = curr_->prev;
    return tmp;
}

template <typename T>
typename BList<T>::Iterator& BList<T>::Iterator::operator+(int a) {
    while (a--) {
        curr_ = curr_->next;
    }
    return *this;
}

template <typename T>
typename BList<T>::Iterator& BList<T>::Iterator::operator-(int a) {
    while (a--) {
        curr_ = curr_->prev;
    }
    return *this;
}

template <typename T>
int BList<T>::Iterator::operator-(const typename BList<T>::Iterator& it) const {
    int cnt = 0;
    if (*this < it) {
        return it - *this;
    }
    auto p = it.curr_;
    while (p != curr_) {
        cnt++;
        p = p->next;
    }
    return cnt;
}

template <typename T>
typename BList<T>::Iterator& operator+(int a, const typename BList<T>::Iterator& b) {
    auto tmp = b;
    while (a--) {
        tmp++;
    }
    return tmp;
}

template <typename T>
typename BList<T>::Iterator& operator-(int a, const typename BList<T>::Iterator& b) {
    auto tmp = b;
    while (a--) {
        tmp--;
    }
    return tmp;
}

template <typename T>
typename BList<T>::Iterator& operator+(const typename BList<T>::Iterator& a, int b) {
    auto tmp = a;
    while (b--) {
        tmp++;
    }
    return tmp;
}

template <typename T>
typename BList<T>::Iterator& operator-(const typename BList<T>::Iterator& a, int b) {
    auto tmp = a;
    while (b--) {
        tmp--;
    }
    return tmp;
}

template <typename T>
typename BList<T>::Iterator::value_type& BList<T>::Iterator::operator*() {
    return *curr_;
}

template <typename T>
typename BList<T>::Iterator::pointer BList<T>::Iterator::operator->() {
    return curr_;
}

template <typename T>
typename BList<T>::Iterator BList<T>::begin() const {
    return Iterator(front());
}

template <typename T>
typename BList<T>::Iterator BList<T>::end() const {
    return Iterator(back()->next);
}

template <typename T>
const typename BList<T>::Iterator& BList<T>::cbegin() const {
    return Iterator(front());
}

template <typename T>
const typename BList<T>::Iterator& BList<T>::cend() const {
    return Iterator(back());
}

#endif  // B_LIST_H