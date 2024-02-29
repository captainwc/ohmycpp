#include "leetcode/lc.h"

int main() {
    // list
    auto list = getList("1,2, 3 ,4, 5");
    auto str  = list2string(list.get());
    std::cout << "print list: " << str << std::endl;

    // tree;
    auto tree = deSerializeTreeByLevelOrder("3,9,20,null,null,15,7");
    cout << "inorder travsal: ";
    inorderTravsal(tree.get(), std::function<void(TreeNode*)>([](TreeNode* node) {
                       if (node != nullptr) {
                           cout << node->val << " ";
                       }
                   }));
    cout << endl;
    print(serializeTreeByPreorder(tree.get()), "preorder serialization:");
    showTree(tree.get());

    // tree serialization
    print(serializeTreeByLevelOrder(tree.get()), "levelorder serialization:");
};
