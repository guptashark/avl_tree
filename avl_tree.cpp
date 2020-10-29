#include "avl_tree.h"

// node ctor
avl_tree::node::node(int key):
key(key), left(nullptr), right(nullptr), parent(nullptr) {}

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
