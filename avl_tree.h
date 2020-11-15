#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>


class avl_tree {

private:

	class avl_tree_impl;
	avl_tree_impl * impl;

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
