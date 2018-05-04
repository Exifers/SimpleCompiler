CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++17 -I .

fls = $(shell find . -type f -name "*.cc")

debug : CXXFLAGS += -g

all:
	$(CXX) $(CXXFLAGS) $(fls) -o main
debug:
	$(CXX) $(CXXFLAGS) $(fls) -o main
