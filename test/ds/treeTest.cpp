#define GTEST
#include "common.h"
 
class TreeTestSuite : public testing::Test {
protected:
    static Tree tree;

    static int cnt;

    static int toNum(const std::vector<TreeNode*>& st){
        int n = st.size();
        std::string str;
        for(auto p : st){
            str.append(std::to_string(p->val));
        }
        return std::strtol(str.c_str(), nullptr, 10);
    }

    static void foo(TreeNode *p, std::vector<TreeNode *> &frame) {
        if (p == nullptr || p->left != nullptr || p->right != nullptr)
            return;
        printf("Leaf%d's frame: ", cnt);
        cnt++;
        for (auto p: frame) {
            std::cout << p->val << " ";
        }
        printf(" totaly : %d\n", toNum(frame));
    }

/**
 *                     4
 *                /        \
 *               1          8
 *             /  \       /   \
 *            #    3     6     #
 *          / \   / \   / \  /  \
 *         #  #  2  #  5  7 #   #
 */
    void SetUp() override {
        tree.create("4,1,8,a,3,6,a,a,a,2,a,5,7");
    }

    void TearDown() override {
        tree.~Tree();
    }
};

Tree TreeTestSuite::tree = Tree();
int TreeTestSuite::cnt = 0;

TEST_F(TreeTestSuite, travsal) {
    EXPECT_EQ(tree.preOrderS(), "[4, 1, 3, 2, 8, 6, 5, 7]");
    EXPECT_EQ(tree.inOrderS(), "[1, 2, 3, 4, 5, 6, 7, 8]");
    EXPECT_EQ(tree.postOrderS(), "[2, 3, 1, 5, 7, 6, 8, 4]") << "FAIL: postOrder";

    EXPECT_EQ(tree.preOrder().size(), 8);
    EXPECT_EQ(tree.inOrder()[7]->val, 8);

    tree.postOrder(foo);
}

int main(int argc, char **argv) {
    printf("Start TreeTestSuit in file %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
