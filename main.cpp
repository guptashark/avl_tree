#include <iostream>
#include <cassert>

#include "avl_tree.h"

void test_empty(void);
void test_size(void);
void test_insert(void);

int main(int argc, char * argv[]) {

	(void)argc;
	(void)argv;

	std::cout << "AVL Tree test" << std::endl;

	test_empty();
	test_size();
	test_insert();

	return 0;
}

void test_empty(void) {

	avl_tree tree;

	assert( tree.empty() );
}

void test_size(void) {

	avl_tree tree;

	assert( tree.size() == 0 );
}

void test_insert(void) {

	avl_tree tree;

	tree.insert(100);
	assert( tree.size() == 1 );

	tree.insert(200);
	assert( tree.size() == 2 );

	tree.insert(300);

	//tree.print_structure();
}
