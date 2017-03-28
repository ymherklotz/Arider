# Make g++ the default compiler
CC := g++

# Add the compilation arguments
CFLAGS := -g -Wall -Wextra -Wpedantic -std=c++14

# Source files to be compiled
SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%,build/%,$(SRCS:.cpp=.o))
INCL := -Iinclude/

# Executable name
EXEC := bin/arider

# Rules
.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $^

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# Cleans up the directories
.PHONY: clean
clean:
	rm -rf build/
	rm -rf bin/

# Make necessary directories if they aren't there yet
$(shell mkdir -p bin/ build/)
