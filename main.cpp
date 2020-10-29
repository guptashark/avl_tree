#include <iostream>
#include <cassert>

#include "avl_tree.h"

void test_empty(void);
void test_size(void);

int main(int argc, char * argv[]) {

	(void)argc;
	(void)argv;

	std::cout << "AVL Tree test" << std::endl;

	test_empty();
	test_size();

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
