#ifndef MODERNCPP_LC_H
#define MODERNCPP_LC_H

#include <algorithm>
#include <memory>
#include <string>

#include "utils.h"

struct ListNode {
    int       val;
    ListNode *prev;
    ListNode *next;

    explicit ListNode(int v = 0, ListNode *n = nullptr, ListNode *p = nullptr) : val(v), prev(p), next(n) {
    }

    ~ListNode() {
        delete next;
    }
};

std::unique_ptr<ListNode> getList(const std::string &str) {
    auto tokens = split(str, ',');
    auto head   = std::make_unique<ListNode>(std::stoi(tokens.front()));
    auto p      = head.get();
    std::for_each(tokens.begin() + 1, tokens.end(), [&p](const std::string &token) {
        p->next = new ListNode(std::stoi(token), nullptr, p);
        p       = p->next;
    });
    return head;
}

std::string list2string(const ListNode *list) {
    auto        p = list;
    std::string ret;
    while (p->next != nullptr) {
        ret.append(std::to_string(p->val)).append(", ");
        p = p->next;
    }
    ret.append(std::to_string(p->val));
    return ret;
}

#endif  // MODERNCPP_LC_H
