//
// Created by j50036120 on 2023/9/8.
//

#ifndef CPP_PROJECT_LIST_H
#define CPP_PROJECT_LIST_H

#include <exception>
#include <iostream>
#include <string>
#include <vector>

template <typename T> struct ListNode {
  T val;
  ListNode *next;
  ListNode *prev;

  ListNode() = default;

  explicit ListNode(T v, ListNode *n = nullptr, ListNode *p = nullptr)
      : val(v), next(n), prev(p) {}

  friend std::ostream &operator<<(std::ostream &out, const ListNode<T> node) {
    out << node.val << ' ';
    return out;
  }

  friend bool operator>(ListNode<T> a, ListNode<T> b) { return a.val > b.val; }
  friend bool operator<(ListNode<T> a, ListNode<T> b) { return a.val < b.val; }
  friend bool operator==(ListNode<T> a, ListNode<T> b) {
    return a.val == b.val;
  }
  friend bool operator!=(ListNode<T> a, ListNode<T> b) {
    return a.val != b.val;
  }
  friend bool operator>=(ListNode<T> a, ListNode<T> b) {
    return a.val >= b.val;
  }
  friend bool operator<=(ListNode<T> a, ListNode<T> b) {
    return a.val <= b.val;
  }

  ListNode &operator=(const ListNode &other) {
    if (this != &other) {
      this->val = other.val;
      this->next = other.next;
      this->prev = other.prev;
    }
    return *this;
  }
};

template <typename T> class List {
private:
  int _size;

public:
  ListNode<T> *head;
  ListNode<T> *tail;

  // have an empty head
  List() {
    head = new ListNode<T>();
    tail = head;
    _size = 0;
  }

  bool empty() {
    // remove(head) || clear()
    return _size == 0;
  }

  bool inList(ListNode<T> *p) {
    return !((p == nullptr) || (p->prev == nullptr && p->next == nullptr));
  }

  int size() { return _size; }

  void push_front(T val) {
    auto node = new ListNode<T>(val);
    if (empty()) {
      head->next = node;
      node->prev = head;
      tail = node;
    } else {
      node->next = head->next;
      head->next->prev = node;
      head->next = node;
      node->prev = head;
    }
    _size++;
  }

  void push_back(T val) {
    auto node = new ListNode<T>(val);
    if (empty()) {
      head->next = node;
      node->prev = head;
      tail = node;
    } else {
      tail->next = node;
      node->prev = tail;
      tail = node;
    }
    _size++;
  }

  ListNode<T> *pop_front() {
    auto pNode = head->next;
    head->next = pNode->next;
    pNode->next->prev = head;
    pNode->next = nullptr;
    pNode->prev = nullptr;
    _size--;
    return pNode;
  }

  ListNode<T> *pop_back() {
    auto pNode = tail;
    tail = tail->prev;
    tail->next = nullptr;
    pNode->prev = nullptr;
    _size--;
    return pNode;
  }

  void remove(ListNode<T> *pNode) {
    if (!inList(pNode))
      return;
    if (pNode == head)
      return;
    if (pNode == head->next)
      pop_front();
    else if (pNode == tail)
      pop_back();
    else {
      pNode->prev->next = pNode->next;
      pNode->next->prev = pNode->prev;
      _size--;
    }
  }

  ListNode<T> *find(T val) {
    auto p = head->next;
    while (p != nullptr) {
      if (p->val == val)
        return p;
      p = p->next;
    }
    return nullptr;
  }

  void remove(T val) {
    auto p = find(val);
    do {
      remove(p);
      p = find(val);
    } while (p != nullptr);
  }

  void insert(ListNode<T> *pNode, T val) {
    if (!inList(pNode))
      return;
    if (pNode == tail)
      push_back(val);
    else {
      auto node = new ListNode<T>(val);
      pNode->next->prev = node;
      node->next = pNode->next;
      node->prev = pNode;
      pNode->next = node;
      _size++;
    }
  }

  std::vector<ListNode<T> *> toVector() {
    auto ret = new std::vector<T>();
    auto p = head->next;
    while (p != nullptr) {
      ret->push_back(p);
      p = p->next;
    }
    return ret;
  }

  std::string dump() {
    auto p = head->next;
    std::string str = "[";
    while (p->next != nullptr) {
      str.append(std::to_string(p->val)).append(", ");
      p = p->next;
    }
    return str.append(std::to_string(p->val)).append("]");
  }

  void print() { std::cout << this->dump() << std::endl; }

  ListNode<T> &operator[](int idx) {
    if (idx < 0)
      throw std::out_of_range("idx shouldn't be negative!");
    int cnt = 0;
    auto p = head->next;
    while (cnt < idx && p != nullptr) {
      cnt++;
      p = p->next;
    }
    if (cnt < idx || p == nullptr)
      throw std::out_of_range("idx out of range!");
    return *p;
  }
};

#endif // CPP_PROJECT_LIST_H
