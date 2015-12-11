.PHONY: clean tar Test
CXX=g++

CXX_CFLAGS=-std=c++11 -g -Wall -Wextra -pthread -Wvla

HEADERS = Matrix.hpp

TAR_FILES = $(HEADERS) Makefile README

Test: Matrix GenericMatrixDriver Tester

Tester: Tester.cpp Matrix.hpp Complex.o
	$(CXX) $(CXX_CFLAGS) -lboost_filesystem -lboost_system $^ -o $@

GenericMatrixDriver: Complex.o GenericMatrixDriver.cpp
	$(CXX) $(CXX_CFLAGS) $^ -o $@

Complex.o: Complex.cpp Complex.h
	$(CXX) $(CXX_CFLAGS) -c Complex.cpp

Matrix: Matrix.hpp
	$(CXX) $(CXX_CFLAGS) -c $^

tar:
	tar cvf ex3.tar $(TAR_FILES)
clean:
	rm -rf *.o GenericMatrixDriver Test ex3.tar
