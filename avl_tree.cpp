#include <iostream>

#include "avl_tree.h"

// node ctor
// indent the member initializer list for easy reading.
avl_tree::node::node(int key, const std::string & val):
	key(key),
	val(val),
	left(nullptr),
	right(nullptr),
	parent(nullptr),
	height(1) {}

void avl_tree::node::print_structure(int indent) {

	std::cout << "(P: " << key;
	std::cout << " (h: " << height << ")";
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

int avl_tree::get_node_balance(avl_tree::node * n) {
	int left_height = get_node_height(n->left);
	int right_height = get_node_height(n->right);
	int balance = right_height - left_height;

	return balance;
}

int avl_tree::get_node_height(avl_tree::node * n) {
	if ( n == nullptr ) {
		return 0;
	} else {
		return n->height;
	}
}

bool avl_tree::equality_check_helper
(avl_tree::node * a, avl_tree::node * b) {

	// check either both are null, or both not null.
	if ( (a == nullptr) && (b == nullptr)) return true;
	if ( (a == nullptr) || (b == nullptr)) return false;

	// check key and height
	if ( a->key != b->key) return false;
	if ( a->height != b->height ) return false;

	// check that the key of the parent is the same.
	{
		node * p_a = a->parent;
		node * p_b = b->parent;

		if ( (p_a == nullptr) && (p_b != nullptr)) return false;
		if ( (p_a != nullptr) && (p_b == nullptr)) return false;

		if ( p_a != nullptr ) {
			if ( p_a->key != p_b->key) {
				return false;
			}
		}
	}

	// recursively check the children
	bool left_match = equality_check_helper(a->left, b->left);
	bool right_match = equality_check_helper(a->right, b->right);

	return ( left_match && right_match );
}

avl_tree::node *
avl_tree::insert_helper
(int key, const std::string & val) {

	node * new_node = new node(key, val);

	node * current = root;
	node * par = nullptr;

	while ( current != nullptr ) {
		par = current;
		if ( key > current->key) {
			current = current->right;
		} else {
			current = current->left;
		}
	}

	if ( par == nullptr ) {
		root = new_node;
	} else {
		if ( key > par->key ) {
			par->right = new_node;
		} else {
			par->left = new_node;
		}

		new_node->parent = par;
	}

	num_nodes++;

	return new_node;
}

void avl_tree::insert(int key) {
	insert(key, "");
}

void avl_tree::insert(int key, const std::string & val) {

	node * added_node = insert_helper(key, val);
	rebalance(added_node);
}

void avl_tree::rebalance(avl_tree::node * added_node) {

	node * unblanaced_subtree = update_balances(added_node);

	if ( unblanaced_subtree != nullptr ) {
		execute_rotations ( unblanaced_subtree );
	}
}

avl_tree::node *
avl_tree::update_balances
(avl_tree::node * added_node) {

	node * curr = added_node->parent;

	// checks to see if the node height was updated.
	// if it wasn't, then none of the parent heights
	// will be updated, so we can exit.
	bool updated = true;

	while ( curr != nullptr && updated ) {

		int new_height = 0;
		int current_balance = 0;

		int left_height = get_node_height(curr->left);
		int right_height = get_node_height(curr->right);

		if ( left_height > right_height ) {
			new_height = left_height + 1;
		} else {
			new_height = right_height + 1;
		}

		if ( curr->height == new_height ) {
			updated = false;
		} else {
			curr->height = new_height;
			current_balance = right_height - left_height;
		}

		if ( current_balance == -2 || current_balance == 2) {
			// need to return, as this is the node
			// where a rotation needs to happen.
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

	if ( get_node_balance(x) == 2 ) {
		z = x->right;
		if ( get_node_balance(z) == -1) {
			y = z->left;
			single_rotation(z, y, 'R');
			single_rotation(x, y, 'L');
		} else {
			single_rotation(x, z, 'L');
		}
	} else {
		z = x->left;
		if ( get_node_balance(z) == 1) {
			y = z->right;
			single_rotation(z, y, 'L');
			single_rotation(x, y, 'R');
		} else {
			single_rotation(x, z, 'R');
		}
	}
}

void avl_tree::single_rotation
(avl_tree::node *x, avl_tree::node *z, char direction) {

	node * par = x->parent;
	z->parent = par;

	// update so that z is the root of the subtree.
	if ( par != nullptr) {
		if ( par->left == x) {
			par->left = z;
		} else {
			par->right = z;
		}
	} else {
		root = z;
	}

	if ( direction == 'R' ) {
		x->left = z->right;
		if ( x->left != nullptr) {
			x->left->parent = x;
		}

		z->right = x;
		x->parent = z;
	} else {
		x->right = z->left;
		if ( x->right != nullptr) {
			x->right->parent = x;
		}

		z->left = x;
		x->parent = z;
	}

	// recalculate the heights.
	{
		int left_height = get_node_height(x->left);
		int right_height = get_node_height(x->right);

		if ( left_height > right_height ) {
			x->height = left_height + 1;
		} else {
			x->height = right_height + 1;
		}
	}

	{
		int left_height = get_node_height(z->left);
		int right_height = get_node_height(z->right);

		if ( left_height > right_height ) {
			z->height = left_height + 1;
		} else {
			z->height = right_height + 1;
		}
	}
}


bool avl_tree::equality_check(const avl_tree & other) {

	return equality_check_helper(root, other.root);
}

int avl_tree::get_min(void) {

	// TODO: situation when the tree is empty?

	node * current = root;

	while ( current->left != nullptr ) {
		current = current->left;
	}

	return current->key;
}

int avl_tree::get_max(void) {

	// TODO: situation when the tree is empty?

	node * current = root;

	while ( current->right != nullptr ) {
		current = current->right;
	}

	return current->key;
}

std::string avl_tree::find(int key) {

	// what if the tree doesn't contain the key...
	// return an empty string?
	node * current = root;

	while ( current != nullptr ) {

		if ( current->key == key) {
			return current->val;
		} else {
			if ( key > current->key ) {
				current = current->right;
			} else {
				current = current->left;
			}
		}
	}

	// key doesn't exist in tree.
	std::string empty;
	return empty;
}

void avl_tree::print_structure(void) {

	root->print_structure(0);

	std::cout << std::endl;
}
