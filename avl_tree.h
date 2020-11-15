#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>

class avl_tree {

private:
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
	avl_tree(void);

	bool empty(void) const;
	int size(void) const;

	// insert with an empty string.
	void insert(int key);
	void insert(int key, const std::string & val);

	bool equality_check(const avl_tree & other);

	int get_min(void);
	int get_max(void);

	std::string find(int key);

	void print_structure();
};

#endif
