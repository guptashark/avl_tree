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
	};

	// number of nodes
	int num_nodes;

	node * root;

public:
	avl_tree(void);

};
#endif
