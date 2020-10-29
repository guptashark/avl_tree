#include <iostream>

#include "avl_tree.h"

// node ctor
// indent the member initializer list for easy reading.
avl_tree::node::node(int key):
	key(key),
	left(nullptr),
	right(nullptr),
	parent(nullptr),
	height(1),
	balance(0) {}

void avl_tree::node::print_structure(int indent) {

	std::cout << "(P: " << key;
	std::cout << " (h: " << height << ")";
	std::cout << " (b: " << balance << ")";
	std::cout << std::endl;

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

avl_tree::node * avl_tree::insert_helper(int key) {

	node * new_node = new node(key);

	if ( root == nullptr ) {
		root = new_node;
		num_nodes++;
		return new_node;
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

	return new_node;
}

void avl_tree::insert(int key) {

	node * added_node = insert_helper(key);
	std::cout << "Before rebalance" << std::endl;
	print_structure();

	rebalance(added_node);

	std::cout << "After rebalance" << std::endl;
	print_structure();
}

void avl_tree::rebalance(avl_tree::node * added_node) {

	node * unblanaced_subtree = update_balances(added_node);

	if ( unblanaced_subtree != nullptr ) {
		execute_rotations ( unblanaced_subtree );
	}
}

avl_tree::node * avl_tree::update_balances(avl_tree::node * added_node) {

	node * curr = added_node->parent;

	// checks to see if the node height was updated.
	// if it wasn't, then none of the parent heights
	// will be updated, so we can exit.
	bool updated = true;

	while ( curr != nullptr && updated ) {

		int left_height = 0;
		int right_height = 0;
		int new_height = 0;

		if ( curr->left != nullptr ) {
			left_height = curr->left->height;
		}

		if ( curr->right != nullptr ) {
			right_height = curr->right->height;
		}

		if ( left_height > right_height ) {
			new_height = left_height + 1;
		} else {
			new_height = right_height + 1;
		}

		if ( curr->height == new_height ) {
			updated = false;
		} else {
			curr->height = new_height;
			curr->balance = right_height - left_height;
		}

		if ( curr->balance == -2 || curr->balance == 2) {
			return curr;
		}

		curr = curr->parent;
	}

	// either there were no updates so the tree is
	// balanced, or we reached the root and it's still
	// balanced. Return null.

	return nullptr;
}

void avl_tree::execute_rotations(avl_tree::node * unbalanced_subtree) {

	node * x = unbalanced_subtree;
	node * z = nullptr;
	node * y = nullptr;

	if ( x->balance == 2 ) {
		z = x->right;
		if ( z->balance == -1) {
			y = z->left;
			rotate_right(z, y);
			rotate_left(x, y);
		} else {
			rotate_left(x, z);
		}
	} else {
		z = x->left;
		if ( z->balance == 1) {
			y = z->right;
			rotate_left(z, y);
			rotate_right(x, y);
		} else {
			rotate_right(x, z);
		}
	}
}

void avl_tree::rotate_left(avl_tree::node *x, avl_tree::node *z) {

	node * par = nullptr;
	z->parent = x->parent;

	// update so that z is the root of the subtree.
	if ( x->parent != nullptr) {

		par = x->parent;

		if ( par->left == x) {
			par->left = z;
		} else {
			par->right = z;
		}
	} else {
		root = z;
	}

	x->right = z->left;
	z->left = x;

	x->balance = 0;
	z->balance = 0;
}

void avl_tree::rotate_right(avl_tree::node *x, avl_tree::node *z) {

	node * par = nullptr;
	z->parent = x->parent;

	// update so that z is the root of the subtree.
	if ( x->parent != nullptr) {

		par = x->parent;

		if ( par->left == x) {
			par->left = z;
		} else {
			par->right = z;
		}
	} else {
		root = z;
	}

	x->left = z->right;
	z->right = x;

	x->balance = 0;
	z->balance = 0;
}

void avl_tree::print_structure(void) {

	root->print_structure(0);

	std::cout << std::endl;
}
