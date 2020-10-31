#include <iostream>
#include <cassert>

#include "avl_tree.h"

#include "avl_tree_tests.h"

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

void test_right_rotation(void) {

	avl_tree expected_tree;

	expected_tree.insert(200);
	expected_tree.insert(100);
	expected_tree.insert(300);

	avl_tree actual_tree;

	actual_tree.insert(300);
	actual_tree.insert(200);
	actual_tree.insert(100);

	bool result = actual_tree.equality_check(expected_tree);

	if ( result == false ) {
		std::cout << "Right rotation test failed" << std::endl;
	}
}

void run_all_avl_tests(void) {

	test_empty();
	test_size();
	test_insert();
	test_left_rotation();
	test_right_rotation();
}
