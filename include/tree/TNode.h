/**
 * Create by shuaikai 2023/10/23 14:45:27
 *
 * Copyright (c) shuaikai. All rights reserved.
 */

#ifndef TNODE_H
#define TNODE_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

enum TCOLOR { RED, BLACK };

template <typename T> struct TNode {
	T val;
	TCOLOR color;
	std::shared_ptr<TNode<T>> parent;
	std::shared_ptr<TNode<T>> left;
	std::shared_ptr<TNode<T>> right;

	TNode() = default;
	explicit TNode(T val, std::shared_ptr<TNode<T>> left = nullptr, std::shared_ptr<TNode<T>> right = nullptr, std::shared_ptr<TNode<T>> parent = nullptr, TCOLOR color = RED)
		: val(val), left(left), right(right), parent(parent), color(color) {}
	TNode(T val, std::shared_ptr<TNode<T>> parent) : val(val), parent(parent) {}
};

//==--------------------------== Build Full Binary Tree ==-----------------------------==//
template <typename T> std::shared_ptr<TNode<T>> buildHelper(const std::vector<T>& vals, int idx) {
	if (idx > vals.size() - 1) {
		return nullptr;
	}
	auto node = std::make_shared<TNode<T>>(vals[idx]);
	if (idx <= (vals.size() - 1) / 2) {
		node->left			= buildHelper(vals, idx * 2);
		node->left->parent	= node;
		node->right			= buildHelper(vals, idx * 2 + 1);
		node->right->parent = node;
	}
	return node;
}

template <typename T> std::shared_ptr<TNode<T>> createTree(const std::vector<T>& vals) {
	if (vals.empty()) {
		return nullptr;
	}
	return buildHelper(vals, 1);
}

#endif // TNODE_H