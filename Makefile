
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -g -std=c++11

LDLIBS = -lpthread

all: test

test: test.o decorator.hpp
	$(CXX) $(CXXFLAGS) test.o -o $@ $(LDLIBS)

runtest: test
	./test

.PHONY:
clean:
	rm -f *.o test

