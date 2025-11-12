# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -O2 -Iinclude

# Source files
SRC := $(wildcard src/*.c)
TESTS := $(wildcard tests/*.c)
OBJS := $(SRC:.c=.o) $(TESTS:.c=.o)

# Output binary
TARGET := dsa_test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

# Run a specific test, e.g. make test TEST=stack
test: $(TARGET)
	./$(TARGET) $(TEST)

.PHONY: all clean run test
