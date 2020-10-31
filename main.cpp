#include <iostream>

#include "avl_tree_tests.h"

int main(int argc, char * argv[]) {

	(void)argc;
	(void)argv;

	std::cout << "AVL Tree test" << std::endl;

	run_all_avl_tests();

	return 0;
}
