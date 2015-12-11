.PHONY: all clean tar IntMatrix
CXX=g++

CPPFLAGS=-std=c++11 -g -Wall -Wextra

HEADERS=Parser.h Scorer.h Song.h Instrumental.h Vocal.h
SRC=MIR.cpp Parser.cpp Scorer.cpp Song.cpp Instrumental.cpp Vocal.cpp
OBJ = $(SRC:.cpp=.o)

TAR_FILES = $(HEADERS) $(SRC) Makefile README

MIR: $(OBJ)
	$(CXX) $(CPPFLAGS) $^ -o $@

%.o: %.cpp %.h
	$(CXX) -c $(CPPFLAGS) $<

tar:
	tar cvf ex2.tar $(TAR_FILES)

clean:
	rm -rf *.o MIR ex2.tar
