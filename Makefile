CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++17 -I .

fls = $(shell find . -type f -name "*.cc")

all:
	$(CXX) $(CXXFLAGS) $(fls) -o main
