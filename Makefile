CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++11

all:
	$(CXX) $(CXXFLAGS) main.cpp avl_tree.cpp -o avl_test
	./avl_test
