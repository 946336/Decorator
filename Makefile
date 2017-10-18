
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -g -std=c++11

LDLIBS = -lpthread

all: sample

sample: sample.o decorator.hpp
	$(CXX) $(CXXFLAGS) sample.o -o $@ $(LDLIBS)

runsample: sample
	./sample

.PHONY:
clean:
	rm -f *.o sample

