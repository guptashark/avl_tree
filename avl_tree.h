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

		node(int key);

		void print_structure(int indent);
	};

	// number of nodes
	int num_nodes;

	node * root;

	// private member functions

public:
	avl_tree(void);

	bool empty(void) const;
	int size(void) const;

	void insert(int key);

	void print_structure();
};

#endif
