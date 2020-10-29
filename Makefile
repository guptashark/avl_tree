CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++11

all:
	$(CXX) $(CXXFLAGS) main.cpp -o avl_test
	./avl_test
