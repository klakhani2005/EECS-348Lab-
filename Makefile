CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: string_calculator

string_calculator: main.o string_calculator.o
	$(CXX) $(CXXFLAGS) -o string_calculator main.o string_calculator.o

main.o: main.cpp string_calculator.h
	$(CXX) $(CXXFLAGS) -c main.cpp

string_calculator.o: string_calculator.cpp string_calculator.h
	$(CXX) $(CXXFLAGS) -c string_calculator.cpp

clean:
	rm -f *.o string_calculator
