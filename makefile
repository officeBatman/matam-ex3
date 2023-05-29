ex3_test: *.cpp *.h
	g++ --std=c++11 -o ex3_test -Wall -pedantic-errors -Werror -DNDEBUG *.cpp -g
