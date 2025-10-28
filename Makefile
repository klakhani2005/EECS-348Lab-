# Makefile for EECS 348 - Lab 9 (C++)
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -O2

TARGET := lab9
SRC := main.cpp

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: all
	./$(TARGET) input.txt

clean:
	rm -f $(TARGET)
