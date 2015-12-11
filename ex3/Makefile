.PHONY: clean tar Matrix
CXX=g++

CXX_CFLAGS=-std=c++11 -g -Wall -Wextra -pthread -Wvla

HEADERS = Matrix.hpp NotSquareMatrixTrace.h MatricesDimensionsError.h Complex.h

TAR_FILES = Matrix.hpp NotSquareMatrixTrace.h MatricesDimensionsError.h Makefile README

Matrix: Matrix.hpp.gch

Matrix.hpp.gch: Matrix.hpp $(HEADERS)
	$(CXX) $(CXX_CFLAGS) -c Matrix.hpp

tar:
	tar cvf ex3.tar $(TAR_FILES)
clean:
	rm -rf ex3.tar Matrix.hpp.gch
