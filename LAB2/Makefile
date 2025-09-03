# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Executable name
TARGET = main

# Source and object files
SRCS = main.c isOdd.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
