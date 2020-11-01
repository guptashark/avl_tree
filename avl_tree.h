#ifndef AVL_TREE_H
#define AVL_TREE_H

class avl_tree {

private:
	class node {
	public:
		int key;
		node * left;
		node * right;
		node * parent;

		int height;

		node(int key);

		void print_structure(int indent);
	};

	// number of nodes
	int num_nodes;

	node * root;

	// private member functions
	int get_node_balance(node * n);
	int get_node_height(node * n);
	bool equality_check_helper(node * a, node * b);

	node * insert_helper(int key);
	void rebalance(node * added_node);
	node * update_balances(node * added_node);

	void execute_rotations(node * unblanaced_subtree);
	void rotate_left(node * x, node * z);
	void rotate_right(node * x, node * z);

public:
	avl_tree(void);

	bool empty(void) const;
	int size(void) const;

	void insert(int key);

	bool equality_check(const avl_tree & other);

	int get_min(void);
	int get_max(void);

	void print_structure();
};

#endif
