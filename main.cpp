#include <iostream>
#include <cassert>

#include "avl_tree.h"

void test_empty(void);
void test_size(void);
void test_insert(void);
void test_left_rotation(void);

int main(int argc, char * argv[]) {

	(void)argc;
	(void)argv;

	std::cout << "AVL Tree test" << std::endl;

	test_empty();
	test_size();
	test_insert();
	test_left_rotation();

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

	tree.insert(150);
}

void test_left_rotation(void) {

	avl_tree expected_tree;

	expected_tree.insert(200);
	expected_tree.insert(100);
	expected_tree.insert(300);

	avl_tree actual_tree;

	actual_tree.insert(100);
	actual_tree.insert(200);
	actual_tree.insert(300);

	bool result = actual_tree.equality_check(expected_tree);

	if ( result == false ) {
		std::cout << "Left rotation test failed" << std::endl;
	}
}
