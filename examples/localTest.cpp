#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode *prev;

    ListNode() = default;
    ListNode(int v, ListNode *n = nullptr, ListNode *p = nullptr) : val(v), next(n), prev(p) {}
};

int main()
{
    ListNode *head = new ListNode(-1);
    ListNode *p = head;
    for (int i = 3; i < 10; i++)
    {
        p->next = new ListNode(i);
        auto q = p->next;
        q->prev = p;
        p = q;
    }
    std::cout << head->next->val << std::endl;

    return 0;
}