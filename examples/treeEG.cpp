#include "common.h"

int main() {
    auto tree = Tree();
    tree.create("4,1,8,a,3,6,a,a,a,2,a,5,7");
    tree.print();
    std::cout << tree.preOrderS() << std::endl;
    std::cout << tree.inOrderS() << std::endl;

    return 0;
}