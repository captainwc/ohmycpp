#ifndef MODERNCPP_LC_H
#define MODERNCPP_LC_H

#include <bits/stdc++.h>

#include "utils.h"

using namespace std;

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

std::vector<std::string> serializeTreeByInorder(TreeNode *node) {
    std::vector<std::string> ret;
    inorderTravsal(node, std::function<void(TreeNode *)>([&ret](TreeNode *p) {
                       ret.emplace_back(std::to_string(p->val));
                   }));
    return ret;
}

/**
 * @brief 层次遍历顺序创建二叉树。创建树就跟遍历树一样，用遍历的思想和模板去遍历数组就好了
 * @example 3,9,20,null,null,15,7
 */
std::unique_ptr<TreeNode> deSerializeTreeByLevelOrder(std::string str, std::string null = "null", char delim = ',') {
    auto elems = split(str, delim);
    if (elems.empty() || elems[0] == null) {
        return nullptr;
    }
    auto              root = std::make_unique<TreeNode>(std::stoi(elems[0]));
    queue<TreeNode *> q;
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

#endif  // MODERNCPP_LC_H
