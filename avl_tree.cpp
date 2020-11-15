#include <iostream>

#include "avl_tree.h"


class node {
public:
	int key;
	std::string val;
	node * left;
	node * right;
	node * parent;

	int height;

	node(int key, const std::string & val);

	void print_structure(int indent);
};

// node ctor
// indent the member initializer list for easy reading.
node::node(int key, const std::string & val):
	key(key),
	val(val),
	left(nullptr),
	right(nullptr),
	parent(nullptr),
	height(1) {}

void node::print_structure(int indent) {

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

class avl_tree_impl {

private:
	// number of nodes
	int num_nodes;

	node * root;

	// private member functions
	int get_node_balance(node * n);
	int get_node_height(node * n);
	bool equality_check_helper(node * a, node * b);

	node * insert_helper(int key, const std::string & val);
	void rebalance(node * added_node);
	node * update_balances(node * added_node);

	void execute_rotations(node * unblanaced_subtree);
	void single_rotation(node *x, node *z, char direction);

public:
	avl_tree_impl(void);

	bool empty(void) const;
	int size(void) const;

	// insert with an empty string.
	void insert(int key);
	void insert(int key, const std::string & val);

	bool equality_check(const avl_tree_impl * other);

	int get_min(void);
	int get_max(void);

	std::string find(int key);

	void print_structure();

};

avl_tree_impl::avl_tree_impl
(void): num_nodes(0), root(nullptr) {}

bool avl_tree_impl::empty(void) const {
	return num_nodes == 0;
}

int avl_tree_impl::size(void) const {
	return num_nodes;
}

int avl_tree_impl::get_node_balance(node * n) {
	int left_height = get_node_height(n->left);
	int right_height = get_node_height(n->right);
	int balance = right_height - left_height;

	return balance;
}

int avl_tree_impl::get_node_height(node * n) {
	if ( n == nullptr ) {
		return 0;
	} else {
		return n->height;
	}
}

bool avl_tree_impl::equality_check_helper
(node * a, node * b) {

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

node *
avl_tree_impl::insert_helper
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

void avl_tree_impl::insert(int key) {
	insert(key, "");
}

void avl_tree_impl::insert(int key, const std::string & val) {

	node * added_node = insert_helper(key, val);
	rebalance(added_node);
}

void avl_tree_impl::rebalance(node * added_node) {

	node * unblanaced_subtree = update_balances(added_node);

	if ( unblanaced_subtree != nullptr ) {
		execute_rotations ( unblanaced_subtree );
	}
}

node *
avl_tree_impl::update_balances
(node * added_node) {

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

void avl_tree_impl::execute_rotations(node * unbalanced_subtree) {

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

void avl_tree_impl::single_rotation
(node *x, node *z, char direction) {

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


bool avl_tree_impl::equality_check
(const avl_tree_impl * other) {

	return equality_check_helper(root, other->root);
}

int avl_tree_impl::get_min(void) {

	// TODO: situation when the tree is empty?

	node * current = root;

	while ( current->left != nullptr ) {
		current = current->left;
	}

	return current->key;
}

int avl_tree_impl::get_max(void) {

	// TODO: situation when the tree is empty?

	node * current = root;

	while ( current->right != nullptr ) {
		current = current->right;
	}

	return current->key;
}

std::string avl_tree_impl::find(int key) {

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

void avl_tree_impl::print_structure(void) {

	root->print_structure(0);

	std::cout << std::endl;
}


// the interface avl_tree class member functions.
avl_tree::avl_tree(void) {
	impl = new avl_tree_impl();
}

bool avl_tree::empty(void) const {
	avl_tree_impl * p = static_cast<avl_tree_impl *>(impl);
	return p->empty();
}

int avl_tree::size(void) const {
	avl_tree_impl * p = static_cast<avl_tree_impl *>(impl);
	return p->size();
}

void avl_tree::insert(int key) {
	avl_tree_impl * p = static_cast<avl_tree_impl *>(impl);
	return p->insert(key);
}

void avl_tree::insert(int key, const std::string & val) {
	avl_tree_impl * p = static_cast<avl_tree_impl *>(impl);
	return p->insert(key, val);
}

bool avl_tree::equality_check(const avl_tree & other) {
	avl_tree_impl * p = nullptr;
	avl_tree_impl * other_p = nullptr;

	p = static_cast<avl_tree_impl *>(impl);
	other_p = static_cast<avl_tree_impl *>(other.impl);

	return p->equality_check( other_p );
}

int avl_tree::get_min(void) {
	avl_tree_impl * p = static_cast<avl_tree_impl *>(impl);
	return p->get_min();
}

int avl_tree::get_max(void) {
	avl_tree_impl * p = static_cast<avl_tree_impl *>(impl);
	return p->get_max();
}

std::string avl_tree::find(int key) {
	avl_tree_impl * p = static_cast<avl_tree_impl *>(impl);
	return p->find(key);
}

void avl_tree::print_structure(void) {
	avl_tree_impl * p = static_cast<avl_tree_impl *>(impl);
	return p->print_structure();
}
