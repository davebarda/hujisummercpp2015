#include <string>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <chrono>
#include "Complex.h"
#include "Matrix.hpp"

std::stack<std::chrono::time_point<std::chrono::system_clock>> tictoc_stack;

void tic() {
	tictoc_stack.push(std::chrono::system_clock::now());
}

void toc() {
	std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
	std::cout << "Time elapsed: " << elapsed_seconds.count() << "sec\n";
	tictoc_stack.pop();
}

Matrix<Complex> readComplexMatrix(const std::string &FileName)
{
	std::ifstream instream(FileName.c_str());
	if (!instream.is_open())
	{
		std::cerr << "Error! Can't open file: "<< FileName << "." << std::endl;
	}

	int rowsNum, colsNum;
	
	instream >> rowsNum >> colsNum;
	std::vector<Complex> cells(rowsNum * colsNum);

	unsigned int i=0;
	double real, img;
	
	while(instream.good())
	{
		instream >> real >> img;
		if (!instream.eof()) {
			if (i >= cells.size()) {
				break;
			}
			cells[i]=(Complex(real,img));
			i++;
		}
	}
	instream.close();
	return Matrix<Complex>(rowsNum, colsNum, cells);
}

Matrix<Complex> doPlus(const Matrix<Complex>& A, const Matrix<Complex>& B) {
	return (A + B);
}

Matrix<Complex> doMult(const Matrix<Complex>& A, const Matrix<Complex>& B) {
	return (A * B);
}

int main(int argc, char *argv[])
{
	
	if (argc != 2)
	{
		std::cerr<<"Usage: ParalelChecker <matrix_file>"<<std::endl;
		exit(-1);
	}
	Matrix<Complex>::setParallel(false);

	std::string matrix(argv[1]);

	Matrix<Complex> A = readComplexMatrix(matrix);
	Matrix<Complex> B = A.trans();
	Matrix<Complex> Ra,Rm,Pa,Pm;

	// Sequential

	std::cout << "=====================" << std::endl;
	
	Matrix<Complex>::setParallel(false);
	
	std::cout <<  "Sequential timing:" << std::endl;
	
	std::cout << "( A  + A ): " << std::flush;
	tic();
	Ra = doPlus(A,A);
	toc();

	std::cout << "( A' * A ): " << std::flush;
	tic();
	Rm = doMult(B,A);
	toc();

	// parallel

	std::cout << "=====================" << std::endl;

	Matrix<Complex>::setParallel(true);
	
	std::cout << "Parallel timing:" << std::endl;

	std::cout << "( A  + A ): " << std::flush;
	tic();
	Pa = doPlus(A,A);
	toc();

	std::cout << "( A' * A ): " << std::flush;
	tic();
	Pm = doMult(B,A);
	toc();


	std::cout << std::endl << ">>>>>>>>>>>>>>>>>>>>>" << std::endl;
	std::cout << "Checking that the resulting matrices are the same..." << std::endl;
	std::cout << std::endl;

	if (Pa == Ra) {
		std::cout << "Hurrah! The plus operation results are the same :)" << std::endl;
	} else {
		std::cout << "Warning! It seems your sequential and parallel results differ for operator+(...). Please check your implementation." << std::endl;
	}

	if (Pm == Rm) {
		std::cout << "Hurrah! The multiplication operation results are the same :)" << std::endl;
	} else {
		std::cout << "Warning! It seems your sequential and parallel results differ for operator*(...). Please check your implementation." << std::endl;
	}
	
	//std::cout << std::endl << ">>>>>>>>>>>>>>>>>>>>>" << std::endl;
	//std::cout << "plus:" << std::endl << Ra << std::endl;
	//std::cout << "mult:" << std::endl << Rm << std::endl;

	return 0;
}
