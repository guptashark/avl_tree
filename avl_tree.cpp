#include <iostream>

#include "avl_tree.h"

// node ctor
avl_tree::node::node(int key):
key(key), left(nullptr), right(nullptr), parent(nullptr) {}

void avl_tree::node::print_structure(int indent) {

	std::cout << "(P: ";
	std::cout << key << std::endl;

	indent += 2;

	{
		for ( int i = 0; i < indent; i++) {
			std::cout << " ";
		}

		std::cout << "(L: ";

		if ( left != nullptr ) {
			left->print_structure(indent);
		} else {
			std::cout << "-";
		}

		std::cout << ")" << std::endl;
	}

	{
		for ( int i = 0; i < indent; i++) {
			std::cout << " ";
		}

		std::cout << "(R: ";

		if ( right != nullptr ) {
			right->print_structure(indent);
		} else {
			std::cout << "-";
		}

		std::cout << ")";
	}

	std::cout << ")";
}

avl_tree::avl_tree(void): num_nodes(0), root(nullptr) {}

bool avl_tree::empty(void) const {
	return num_nodes == 0;
}

int avl_tree::size(void) const {
	return num_nodes;
}

void avl_tree::insert(int key) {

	node * new_node = new node(key);

	if ( root == nullptr ) {
		root = new_node;
		num_nodes++;
		return;
	}

	node * curr = root;

	bool node_inserted = false;

	while ( node_inserted == false ) {

		if ( new_node->key > curr->key ) {

			if ( curr->right != nullptr ) {
				curr = curr->right;
			} else {
				curr->right = new_node;
				new_node->parent = curr;
				node_inserted = true;
			}
		} else {
			if ( curr->left != nullptr ) {
				curr = curr->left;
			} else {
				curr->left = new_node;
				new_node->parent = curr;
				node_inserted = true;
			}
		}
	}

	num_nodes++;
}

void avl_tree::print_structure(void) {

	root->print_structure(0);

	std::cout << std::endl;
}
