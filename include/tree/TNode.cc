/**
 * Create by shuaikai 2023/10/23 14:45:27
 *
 * Copyright (c) shuaikai. All rights reserved.
 */

#ifndef TNODE_H
#define TNODE_H

#include <algorithm>
#include <memory>
#include <vector>

#include <iostream>

enum TCOLOR { RED, BLACK };

template <typename T> struct TNode {
	T val;
	TCOLOR color;
	std::unique_ptr<TNode<T>> left;
	std::unique_ptr<TNode<T>> right;
	std::unique_ptr<TNode<T>> parent;

	TNode() = default;
	explicit TNode(T v, std::unique_ptr<TNode<T>> l = nullptr, std::unique_ptr<TNode<T>> r = nullptr, std::unique_ptr<TNode<T>> p = nullptr, TCOLOR c = RED)
		: val(v), left(std::move(l)), right(std::move(r)), parent(std::move(p)), color(c) {}
	TNode(T v, std::unique_ptr<TNode<T>> p) : val(v), left(nullptr), right(nullptr), parent(std::move(p)), color(RED) {}
};

//==--------------------------= Build Tree =-----------------------------
template <typename T> std::unique_ptr<TNode<T>> buildHelper(const std::vector<T>& vals, int idx) {
	if (idx > vals.size() - 1) {
		return nullptr;
	}
	auto node = std::make_unique<TNode<T>>(vals[idx]);
	if (idx <= (vals.size() - 1) / 2) {
		node->left	= buildHelper(vals, idx * 2);
		node->right = buildHelper(vals, idx * 2 + 1);
	}
	return node;
}

template <typename T> std::unique_ptr<TNode<T>> createTree(const std::vector<T>& vals) {
	if (vals.empty()) {
		return nullptr;
	}
	return buildHelper(vals, 1);
}

int main() {
	auto vals = std::vector<int>{ -1, 1, 2, 3, 4, 5, 6, 7 };
	auto root = createTree<int>(vals);
	std::cout << root->val << std::endl;
}

#endif // TNODE_H