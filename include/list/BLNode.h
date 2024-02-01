//
// Created by j50036120 on 2023/9/8.
//

#ifndef CPP_PROJECT_LIST_H
#define CPP_PROJECT_LIST_H

#include <exception>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
struct BLNode {
    T       val;
    BLNode* next;
    BLNode* prev;

    BLNode() = default;

    explicit BLNode(T v, BLNode* n = nullptr, BLNode* p = nullptr) : val(v), next(n), prev(p) {
    }

    friend std::ostream& operator<<(std::ostream& out, const BLNode<T> node) {
        out << node.val << ' ';
        return out;
    }

    friend bool operator>(const BLNode<T>& a, const BLNode<T>& b) {
        return a.val > b.val;
    }

    friend bool operator<(const BLNode<T>& a, const BLNode<T>& b) {
        return a.val < b.val;
    }

    friend bool operator==(const BLNode<T>& a, const BLNode<T>& b) {
        return a.val == b.val;
    }

    friend bool operator!=(const BLNode<T>& a, const BLNode<T>& b) {
        return a.val != b.val;
    }

    friend bool operator>=(const BLNode<T>& a, const BLNode<T>& b) {
        return a.val >= b.val;
    }

    friend bool operator<=(const BLNode<T>& a, const BLNode<T>& b) {
        return a.val <= b.val;
    }

    BLNode<T>& operator=(const BLNode<T>& other) {
        if (this != &other) {
            this->val = other.val;
            this->next = other.next;
            this->prev = other.prev;
        }
        return *this;
    }
};

#endif  // CPP_PROJECT_LIST_H
