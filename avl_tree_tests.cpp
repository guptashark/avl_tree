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

void test_left_right_rotation(void) {

	avl_tree expected_tree;

	expected_tree.insert(200);
	expected_tree.insert(100);
	expected_tree.insert(300);

	avl_tree actual_tree;

	actual_tree.insert(300);
	actual_tree.insert(100);
	actual_tree.insert(200);

	bool result = actual_tree.equality_check(expected_tree);

	if ( result == false ) {
		std::cout << "Left Right rotation test failed" << std::endl;
	}
}

void test_right_left_rotation(void) {

	avl_tree expected_tree;

	expected_tree.insert(200);
	expected_tree.insert(100);
	expected_tree.insert(300);

	avl_tree actual_tree;

	actual_tree.insert(100);
	actual_tree.insert(300);
	actual_tree.insert(200);

	bool result = actual_tree.equality_check(expected_tree);

	if ( result == false ) {
		std::cout << "Left Right rotation test failed" << std::endl;
	}
}

void test_get_min(void) {

	{
		avl_tree actual_tree;

		actual_tree.insert(100);
		actual_tree.insert(200);
		actual_tree.insert(300);

		int min_val = actual_tree.get_min();

		if ( min_val != 100 ) {
			std::cout << "Get min failed" << std::endl;
		}
	}

	{
		avl_tree actual_tree;

		actual_tree.insert(300);
		actual_tree.insert(200);
		actual_tree.insert(100);

		int min_val = actual_tree.get_min();

		if ( min_val != 100 ) {
			std::cout << "Get min failed" << std::endl;
		}
	}
}

void test_get_max(void) {

	{
		avl_tree actual_tree;

		actual_tree.insert(300);
		actual_tree.insert(200);
		actual_tree.insert(100);

		int max_val = actual_tree.get_max();

		if ( max_val != 300 ) {
			std::cout << "Get max failed" << std::endl;
		}
	}

	{
		avl_tree actual_tree;

		actual_tree.insert(100);
		actual_tree.insert(200);
		actual_tree.insert(300);

		int max_val = actual_tree.get_max();

		if ( max_val != 300 ) {
			std::cout << "Get max failed" << std::endl;
		}
	}
}

void run_all_avl_tests(void) {

	test_empty();
	test_size();
	test_insert();
	test_left_rotation();
	test_right_rotation();

	test_left_right_rotation();
	test_right_left_rotation();

	test_get_min();
	test_get_max();
}
