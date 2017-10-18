
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -g -std=c++11

LDLIBS = -lpthread

all: sample example

run: runsample runexample

sample: sample.o decorator.hpp
	$(CXX) $(CXXFLAGS) sample.o -o $@ $(LDLIBS)

runsample: sample
	./sample

example: sample_examples.cpp decorator.hpp memoize.hpp
	$(CXX) $(CXXFLAGS) sample_examples.cpp -o $@ $(LDLIBS) -DDEBUG

silent_example: sample_examples.cpp decorator.hpp memoize.hpp
	$(CXX) $(CXXFLAGS) sample_examples.cpp -o $@ $(LDLIBS)

runexample:
	./example

.PHONY:
clean:
	rm -f *.o sample example silent_example

