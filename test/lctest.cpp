#include "lc.h"

int main() {
    auto list = getList("1,2, 3 ,4, 5");
    auto str  = list2string(list.get());
    std::cout << str << std::endl;

    auto tree = deSerializeTreeByLevelOrder("3,9,20,null,null,15,7");
    inorderTravsal(tree.get(), std::function<void(TreeNode*)>([](TreeNode* node) {
                       if (node != nullptr) {
                           cout << node->val << " ";
                       }
                   }));
    cout << endl;
    print(serializeTreeByInorder(tree.get()));
    showTree(tree.get());
};
