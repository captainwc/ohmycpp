#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <cstdint>
#include <fstream>
#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "string_utils.h"

const std::string NULL_NODE = "null";
const char        DELIM     = ',';

struct TreeNode {
    int       val;
    TreeNode *left;
    TreeNode *right;

    explicit TreeNode(int val = 0, TreeNode *left = nullptr, TreeNode *right = nullptr)
        : val(val), left(left), right(right) {
    }

    ~TreeNode() {
        delete left;
        delete right;
    }
};

template <typename... Args>
void inorderTravsal(TreeNode *node, std::function<void(TreeNode *, Args...)> visitor, Args &&...args) {
    if (node != nullptr) {
        inorderTravsal(node->left, visitor, std::forward<Args>(args)...);
        std::invoke(visitor, node, std::forward<Args>(args)...);
        inorderTravsal(node->right, visitor, std::forward<Args>(args)...);
    }
}

void _serializeTreeByPreorderHelper(TreeNode *node, std::vector<std::string> &ret) {
    if (node == nullptr) {
        ret.emplace_back(NULL_NODE);
    } else {
        ret.emplace_back(std::to_string(node->val));
        _serializeTreeByPreorderHelper(node->left, ret);
        _serializeTreeByPreorderHelper(node->right, ret);
    }
}

std::vector<std::string> serializeTreeByPreorder(TreeNode *node) {
    std::vector<std::string> ret;
    _serializeTreeByPreorderHelper(node, ret);
    return ret;
}

std::vector<std::string> serializeTreeByLevelOrder(TreeNode *node, std::string null = NULL_NODE, char delim = DELIM) {
    if (node == nullptr) {
        return {};
    }
    std::vector<std::string> ret;
    std::queue<TreeNode *>   q;
    std::vector<TreeNode *>  to_delete;
    q.push(node);
    while (!q.empty()) {
        auto pNode = q.front();
        q.pop();
        if (pNode->val == INT32_MIN) {
            ret.emplace_back(null);
            continue;
        } else {
            ret.emplace_back(std::to_string(pNode->val));
        }

        if (pNode->left == nullptr) {
            TreeNode *marked_null = new TreeNode(INT32_MIN);
            to_delete.push_back(marked_null);
            q.push(marked_null);
        } else {
            q.push(pNode->left);
        }

        if (pNode->right == nullptr) {
            TreeNode *marked_null = new TreeNode(INT32_MIN);
            to_delete.push_back(marked_null);
            q.push(marked_null);
        } else {
            q.push(pNode->right);
        }
    }
    for (auto p : to_delete) {
        delete p;
    }
    return ret;
}

/**
 * @brief 层次遍历顺序创建二叉树。创建树就跟遍历树一样，用遍历的思想和模板去遍历数组就好了
 * @example 3,9,20,null,null,15,7
 */
std::unique_ptr<TreeNode> deSerializeTreeByLevelOrder(std::string str, std::string null = NULL_NODE,
                                                      char delim = DELIM) {
    auto elems = split(str, delim);
    if (elems.empty() || elems[0] == null) {
        return nullptr;
    }
    auto                   root = std::make_unique<TreeNode>(std::stoi(elems[0]));
    std::queue<TreeNode *> q;
    q.push(root.get());
    int idx = 1;
    while (!q.empty()) {
        auto pNode = q.front();
        q.pop();

        if (idx < elems.size() && elems[idx] != null) {
            pNode->left = new TreeNode(std::stoi(elems[idx]));
            q.push(pNode->left);
        }
        idx++;

        if (idx < elems.size() && elems[idx] != null) {
            pNode->right = new TreeNode(std::stoi(elems[idx]));
            q.push(pNode->right);
        }
        idx++;
    }
    return root;
}

// 将树展示为png

void _showTreeHelper(std::ofstream &file, TreeNode *node, int nodeidx, int &cnt) {
    if (node == nullptr) {
        return;
    }
    int leftidx  = -1;
    int rightidx = -1;
    if (node->left != nullptr) {
        leftidx = cnt;
        file << "node_" << leftidx << " [label=\"" << node->left->val << "\"];\n";
        file << "node_" << nodeidx << " -> "
             << "node_" << leftidx << ";\n";
        cnt++;
    }
    if (node->right != nullptr) {
        rightidx = cnt;
        file << "node_" << rightidx << " [label=\"" << node->right->val << "\"];\n";
        file << "node_" << nodeidx << " -> "
             << "node_" << rightidx << ";\n";
        cnt++;
    }
    if (leftidx != -1) {
        _showTreeHelper(file, node->left, leftidx, cnt);
    }
    if (rightidx != -1) {
        _showTreeHelper(file, node->right, rightidx, cnt);
    }
}

void showTree(TreeNode *tree, std::string fileName = "tree") {
    if (tree == nullptr) {
        return;
    }
    std::string   dotFileName = fileName + ".dot";
    std::ofstream dotFile(dotFileName);
    int           cnt = 0;
    dotFile << "digraph G {\n";
    dotFile << "node_" << cnt++ << " [label=\"" << tree->val << "\"];\n";
    _showTreeHelper(dotFile, tree, cnt - 1, cnt);
    dotFile << "}";
    dotFile.close();

    std::string command = "dot -Tpng " + dotFileName + " -o " + fileName + ".png";
    system(command.c_str());

    std::remove(dotFileName.c_str());
}
#endif  // TREE_NODE_H
