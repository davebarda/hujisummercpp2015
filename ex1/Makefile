.DEFAULT_GOAL := IntMatrixMainDriver
.PHONY: all clean tar IntMatrix

IntMatrixMainDriver: IntMatrixDriver.o IntMatrix.o
	g++ -std=c++11 -Wall -Wextra IntMatrixDriver.o IntMatrix.o -o IntMatrixMainDriver

IntMatrix.o: IntMatrix.cpp IntMatrix.h
	g++ -std=c++11 -Wall -Wextra -c IntMatrix.cpp

IntMatrixDriver.o: IntMatrixDriver.cpp IntMatrix.h
	g++ -std=c++11 -Wall -Wextra -c IntMatrixDriver.cpp

IntMatrix: IntMatrix.o

all: IntMatrixMainDriver tar

tar:
	tar cvf ex1.tar Makefile IntMatrix.cpp IntMatrix.h IntMatrixDriver.cpp
clean:
	rm -rf *.o IntMatrixMainDriver ex1.tar
