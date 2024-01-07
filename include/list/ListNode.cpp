/**
 * Create by shuaikai 2024/01/07 13:01:03
 *
 * Copyright (c) shuaikai. All rights reserved.
 */

#include "ListNode.h"

LinkList::LinkList() {
    head_ = new ListNode();
    tail_ = head_;
    size_ = 0;
}

LinkList::LinkList(ListNode* head, int size) {
    head_ = head;
    size_ = size;
}

bool LinkList::empty() const {
    return size_ == 0;
}

int LinkList::size() const {
    return size_;
}

void LinkList::push_back(int val) {
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

void LinkList::push_front(int val) {
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

void LinkList::pop_back() {
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

void LinkList::pop_front() {
    if (empty()) {
        return;
    }
    auto node = head_->next;
    head_->next = node->next;
    delete node;
    size_--;
}

ListNode* LinkList::head() const {
    return head_->next;
}

ListNode* LinkList::front() const {
    if (empty()) {
        return nullptr;
    }
    return head_->next;
}

ListNode* LinkList::back() const {
    if (empty()) {
        return nullptr;
    }
    return tail_;
}

std::string LinkList::dump() const {
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

LinkList::Iterator::Iterator(pointer p) {
    this->curr_ = p;
}

LinkList::Iterator& LinkList::Iterator::operator=(const Iterator& it) {
    this->curr_ = it.curr_;
    return *this;
}

bool LinkList::Iterator::operator==(const Iterator& it) const {
    return this->curr_ == it.curr_;
}

bool LinkList::Iterator::operator!=(const Iterator& it) const {
    return this->curr_ != it.curr_;
}

LinkList::Iterator& LinkList::Iterator::operator++() {
    curr_ = curr_->next;
    return *this;
}

// 用到了 tmp，因此后加不返回引用
LinkList::Iterator LinkList::Iterator::operator++(int) {
    LinkList::Iterator tmp = *this;
    curr_ = curr_->next;
    return tmp;
}

LinkList::Iterator::value_type& LinkList::Iterator::operator*() {
    return *curr_;
}

LinkList::Iterator LinkList::begin() const {
    return Iterator(front());
}

LinkList::Iterator LinkList::end() const {
    return Iterator(back()->next);
}

const LinkList::Iterator LinkList::cbegin() const {
    return Iterator(front());
}

const LinkList::Iterator LinkList::cend() const {
    return Iterator(back());
}
