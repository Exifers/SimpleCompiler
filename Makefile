CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++17 -I .

fls = $(shell find . -type f -name "*.cc")
bas = $(basename $(fls))
obj = $(addsuffix .o, $(bas))
bin = main

debug : CXXFLAGS += -g

all: $(obj)
	$(CXX) $(CXXFLAGS) $^ -o $(bin)
debug:
	$(CXX) $(CXXFLAGS) $(fls) -o main
clean:
	$(RM) $(obj) $(bin)
