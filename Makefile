.PHONY=clean

test: tests/test.cpp hpp/algorithms.hpp
	clang++ -Wall -Wextra -std=c++20 -Ihpp $< -o $@ -lgtest -lpthread -g -O0


clean:
	@rm -f test

