// for leetcode

#ifndef TREENODE_H
#define TREENODE_H

#include <exception>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

enum COLOR {
    RED,
    BLACK
};

struct TreeNode {
    int val;
    COLOR color;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    explicit TreeNode(int v, TreeNode* l = nullptr, TreeNode* r = nullptr, TreeNode* p = nullptr, COLOR c = RED)
        : val(v), left(l), right(r), parent(p), color(c) {
    }

    TreeNode(int val, TreeNode* p) : val(val), left(nullptr), right(nullptr), parent(p), color(RED) {
    }

    ~TreeNode() {
        delete left;
        delete right;
        delete parent;
    }
};

//=--------------------------= Build Tree =-----------------------------
inline TreeNode* buildNode(const std::vector<int>& vals, int idx) {
    if ((idx > vals.size() - 1) || (vals[idx] == -1))
        return nullptr;
    // 堆上创建
    auto node = new TreeNode(vals[idx]);
    if (idx <= (vals.size() - 1) / 2) {
        node->left = buildNode(vals, idx * 2);
        node->right = buildNode(vals, idx * 2 + 1);
    }
    return node;
}

inline TreeNode* createTree(const std::vector<int>& vals) {
    if (vals.empty())
        return nullptr;
    return buildNode(vals, 1);
}

inline std::vector<int>* handleString(const std::string& str) {
    std::stringstream ss(str);
    auto ret = new std::vector<int>();
    ret->push_back(-1);
    std::string buf;
    while (std::getline(ss, buf, ',')) {
        char* endptr;
        int x = strtol(buf.c_str(), &endptr, 10);
        if (endptr == buf.c_str())
            x = -1;
        ret->push_back(x);
    }
    return ret;
}

inline TreeNode* createTree(const std::string& str) {
    auto vals = handleString(str);
    return createTree(*vals);
}

//=--------------------------= Travsal Tree =---------------------------

inline std::vector<TreeNode*> preOrderTravsal(TreeNode* root) {
    auto ret = std::vector<TreeNode*>();
    auto st = std::stack<TreeNode*>();

    auto p = root;
    while (p != nullptr || !st.empty()) {
        if (p != nullptr) {
            ret.push_back(p);
            st.push(p);
            p = p->left;
        } else {
            p = st.top();
            st.pop();
            p = p->right;
        }
    }
    return ret;
}

inline std::vector<TreeNode*> inOrderTravsal(TreeNode* root) {
    auto ret = std::vector<TreeNode*>();
    auto st = std::stack<TreeNode*>();

    auto p = root;
    while (p != nullptr || !st.empty()) {
        if (p != nullptr) {
            st.push(p);
            p = p->left;
        } else {
            p = st.top();
            ret.push_back(p);
            st.pop();
            p = p->right;
        }
    }

    return ret;
}

inline std::vector<TreeNode*> postOrderTravsal(TreeNode* root,
                                               void (*func)(TreeNode* pNode, std::vector<TreeNode*>& frame)) {
    auto ret = std::vector<TreeNode*>();
    auto st = std::vector<TreeNode*>();

    auto p = root;
    TreeNode* visited = nullptr;

    while (p != nullptr || !st.empty()) {
        if (p != nullptr) {
            st.push_back(p);
            p = p->left;
        } else {
            p = st.back();
            if (p->right != nullptr && visited != p->right) {
                // 注意这里不要再入栈了，因为 p->right 会由下一轮 while
                // 负责入栈。这里入了就重复了
                p = p->right;
            } else {
                ret.push_back(p);
                if (func != nullptr)
                    func(p, st);
                st.pop_back();
                visited = p;
                p = nullptr;
            }
        }
    }
    return ret;
}

inline std::string listToString(const std::vector<TreeNode*>& list) {
    int len = list.size();
    std::string ret = "[";
    for (int i = 0; i < len - 1; i++)
        ret.append(std::to_string(list[i]->val) + ", ");
    ret.append(std::to_string(list[len - 1]->val) + "]");
    return ret;
}

inline std::string preOrderTravsalS(TreeNode* root) {
    std::string str = listToString(preOrderTravsal(root));
    return str;
}

inline std::string inOrderTravsalS(TreeNode* root) {
    std::string str = listToString(inOrderTravsal(root));
    return str;
}

inline std::string postOrderTravsalS(TreeNode* root) {
    std::string str = listToString(postOrderTravsal(root, nullptr));
    return str;
}

//=--------------------------= Print Tree =-----------------------------

struct Trunk {
    Trunk* prev;
    std::string str;

    Trunk(Trunk* prev, std::string str) {
        this->prev = prev;
        this->str = std::move(str);
    }
};

// Helper function to print branches of the binary tree
inline void showTrunks(Trunk* p) {
    if (p == nullptr) {
        return;
    }

    showTrunks(p->prev);
    std::cout << p->str;
}

inline void printTree(TreeNode* root, Trunk* prev, bool isLeft) {
    if (root == nullptr) {
        return;
    }

    std::string prev_str = "    ";
    auto trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev) {
        trunk->str = "----";
    } else if (isLeft) {
        trunk->str = ".----";
        prev_str = "   |";
    } else {
        trunk->str = "`----";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    std::cout << " " << root->val << std::endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->left, trunk, false);
}

inline void dumpTree(TreeNode* root) {
    printTree(root, nullptr, false);
}

/////////////////////////////////////////////////////////////////////////////////
// Binary Tree Implement
////////////////////////////////////////////////////////////////////////////////

class Tree {
public:
    TreeNode* root;

    explicit Tree(TreeNode* node = nullptr) : root(node) {
    }

    void create(const std::vector<int>& vals) {
        root = createTree(vals);
    }

    void create(const std::string& str) {
        root = createTree(str);
    }

    void print() const {
        dumpTree(root);
    }

    std::vector<TreeNode*> preOrder() const {
        return preOrderTravsal(root);
    }

    std::string preOrderS() const {
        return preOrderTravsalS(root);
    }

    std::vector<TreeNode*> inOrder() const {
        return inOrderTravsal(root);
    }

    std::string inOrderS() const {
        return inOrderTravsalS(root);
    }

    std::vector<TreeNode*> postOrder() const {
        return postOrderTravsal(root, nullptr);
    }

    std::vector<TreeNode*> postOrder(void (*func)(TreeNode* pNode, std::vector<TreeNode*>& frame)) {
        return postOrderTravsal(root, func);
    }

    std::string postOrderS() const {
        return postOrderTravsalS(root);
    }

    ~Tree() {
        delete root;
    }
};

#endif  // TREENODE_H
