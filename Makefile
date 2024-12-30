CXX=g++
CXXFLAGS=-std=c++17 #-O3 -Wall -Wextra -Werror -pedantic
OBJS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

.PHONY: all clean depend format

all: nslcc

depend:
	$(CXX) -MM *.cpp > Makefile.deps

-include Makefile.deps

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

nslcc: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f nslcc $(OBJS)

format:
	clang-format-14 -i *.cpp *.hpp
