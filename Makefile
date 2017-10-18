
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -g -std=c++14

LDLIBS = -lpthread

all: test

test: test.o decorator.hpp
	$(CXX) $(CXXFLAGS) test.o -o $@ $(LDLIBS)

.PHONY:
clean:
	rm -f *.o test

