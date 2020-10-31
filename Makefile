CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++11

all:
	$(CXX) $(CXXFLAGS) main.cpp avl_tree.cpp avl_tree_tests.cpp -o avl_test
	./avl_test
