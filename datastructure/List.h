#ifndef OH_MY_CPP_LIST_H
#define OH_MY_CPP_LIST_H

#include <memory>

template <typename T>
struct ListNode {
    T         data;
    ListNode* prev;
    ListNode* after;

    explicit ListNode(T data, ListNode* prev = nullptr, ListNode* after = nullptr)
        : data(data), prev(prev), after(after) {
    }

    ~ListNode() {
        delete after;
    }
};

template <typename T>
class List {
private:
    std::unique_ptr<ListNode> dummy_;
    int                       size_;

public:
    bool empty() const;
    int  size() const;
};

#endif  // OH_MY_CPP_LIST_H