#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <utility>

template <typename K, typename V>
class binary_tree {

	struct node {
		std::pair<K, V> data;
		node* 			left  = nullptr;
		node* 			right = nullptr;

		node (std::pair<K, V> d, node* l, node* r) 
		: data	(d)
		, left	(l)
		, right	(r)
		{}

		const K& key() { return data.first ; }
		const V& val() { return data.second; }
	};

	node* root = nullptr;
	size_t m_size = 0;

public:
	bool insert (std::pair<K, V> item) {
		node* z = new node(item, nullptr, nullptr);
		node* x = root;
		node* y = nullptr;

		while (x != nullptr) {
			if (z->key() == x->key()) {
				delete(z);
				return false;
			}

			y = x;
			if (z->key() < x->key())
				x = x->left;
			else
				x = x->right;
		}

		m_size += 1;

		if (y == nullptr)
			root = z;
		else if (z->key() < y->key())
			y->left = z;
		else
			y->right = z;

		return true;
	}

	node* find (K key) {
		return find(key, root);
	}

	node* find (K key, node* n) {
		if (n == nullptr || key == n->key())
			return n;
		else if (key < n->key())
			return find(key, n->left);
		else
			return find(key, n->right);
	}

	void print () {
		inorder_walk(root);
		std::cout << std::endl;
	}

	void inorder_walk (node* n) {
		if (n != nullptr) {
			inorder_walk(n->left);
			std::cout << n->key() << " ";
			inorder_walk(n->right);
		}
	}

	nullptr_t not_found() { return nullptr; }

	size_t size() { return m_size*(sizeof(node)); }
};

#endif
