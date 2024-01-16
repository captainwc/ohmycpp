#include <algorithm>
#include <iostream>

#include "BList.h"

int main() {
    BList<int> list;

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            list.push_back(i);
        } else {
            list.push_front(i);
        }
    }

    std::for_each(list.begin(), list.end(), [](BLNode<int> node) {
        std::cout << node.val << " ";
    });

    std::sort(list.begin(), list.end());

    list.print();

    auto it = list.begin();

    std::cout << it->val << std::endl;
    std::cout << (it++)->val << std::endl;
    it = it + 2;
    it = it - 1;
    std::cout << (it + 2)->val << std::endl;
    std::cout << (it - 2)->val << std::endl;
}