// IntMatrixDriver.cpp

/*
 * -----------------------------------------------------------------------------
 * This file contains the main program used to calculate operation over matrices
 * using IntMatrix class.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "IntMatrix.h"
#include <climits>

#define NOT_DEFINED -1
#define MAX_OPERATION_NUM 5
#define MIN_OPERATION_NUM 1
#define BAD_INPUT_EXCEPTION 0

/**
 * An enum represents matrices operations.
 */
enum Operation
{
	ADD,
	SUBSTRACT,
	MULTIPLY,
	TRANSPOSE,
	TRACE
};

// -----Following functions are related to the Operation enum-----

/**
 * A function that is used to check if a operation is binary.
 *
 * @param opr the operation to check if its binary or unary.
 * @return true iff the operation is a binary operation.
 */
bool isBinaryOperation(const Operation opr)
{
	switch(opr)
	{
		case ADD:
		case SUBSTRACT:
		case MULTIPLY:
			return true;
		default:
			return false;
	}
}

/**
 * A function that is used to get a string representation from an Operation.
 *
 * @param opr the operation to get string of.
 * @return a string representation of the operation.
 */
std::string operationToString(const Operation opr)
{
	switch(opr)
	{
		case ADD:
			return "add";
		case SUBSTRACT:
			return "sub";
		case MULTIPLY:
			return "mul";
		case TRANSPOSE:
			return "trans";
		case TRACE:
			return "trace";
		default:
			throw BAD_INPUT_EXCEPTION;
	}	
}
// -----End of functions related to enum-----

/**
 * A function that is used to get a result of an operation over given matrices.
 *
 * @param opr the operation to calculate over the matrices.
 * @matrix1 the first operand.
 * @matrix2 the second operand.
 * @return the result matrix.
 */
IntMatrix calculatedOperation(const Operation opr, const IntMatrix& matrix1, const IntMatrix& matrix2)
{
	switch(opr)
	{
		case ADD:
			return matrix1 + matrix2;
		case SUBSTRACT:
			return matrix1 - matrix2;
		case MULTIPLY:
			return matrix1 * matrix2;
		default:
			throw BAD_INPUT_EXCEPTION;
	}
}

/**
 * A function that is used to check if the matrices meet the operation requirements.
 *
 * @param opr the operation to calculate over the matrices.
 * @matrix1 the first operand.
 * @matrix2 the second operand.
 */
bool isInputLegal(const Operation opr, const IntMatrix& matrix1, const IntMatrix& matrix2) 
{
	switch(opr)
	{
		case ADD:
			// continue to substract as both has same requirements.
		case SUBSTRACT:
			if (matrix1.getNumOfRows() != matrix2.getNumOfRows() ||
				matrix1.getNumOfCols() != matrix2.getNumOfCols())
			{
				return false;
			}
			break;
		case MULTIPLY:
			if (matrix1.getNumOfCols() != matrix2.getNumOfRows()) 
			{
				return false;
			}
			break;
		case TRANSPOSE:
			// transpose has no special requirements.
			return true;
		case TRACE:
			if (matrix1.getNumOfRows() != matrix1.getNumOfCols())
			{
				return false;
			}
			break;
	}
	return true;
}

/**
 * A function that is used to get an operation from the user returns an int represent an operation.
 *
 * @return the operation chosen by the user.
 */
Operation getOperation() 
{
	int operationNum = NOT_DEFINED;
	do
	{
		std::cout << "Choose operation:\n" <<
					  "1. add\n" <<
					  "2. sub\n" <<
					  "3. mul\n" <<
					  "4. trans\n" <<
					  "5. trace" << std::endl;
		std::cin >> operationNum;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	while ((operationNum > MAX_OPERATION_NUM) || (operationNum < MIN_OPERATION_NUM));
	// substract 1 because the enum starts from 0 and values from 1
	return static_cast<Operation>(operationNum - 1);
}

/**
 * A function that returns an IntMatrix given by user input.
 *
 * @return the matrix entered by the user.
 */
IntMatrix getMatrix() 
{
	int rows, cols;
	std::cout << "number of rows:";
	std::cin >> rows;
	std::cout << "number of columns:";
	std::cin >> cols;
	IntMatrix matrix(rows, cols);
	std::cout << "Now insert the values of the matrix, row by row.\n" << 
				 "After each cell add the char ',' (including after the last cell of a row).\n" << 
				 "Each row should be in a separate line." << std::endl;
	
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < cols; j++)
		{
			int userInput;
			std::cin >> userInput;
			std::cin.clear();
			std::cin.ignore();
			matrix.setMatrixCell(i, j, userInput);
		}
	}
	return matrix;
}

/**
 * The main function used to calculate operation over matrices.
 */
int main() 
{
	IntMatrix matrix1, matrix2;
	Operation operation = getOperation();

	// Case binary operation.
	if (isBinaryOperation(operation))
	{
		std::cout << "Operation " << operationToString(operation) << " requires 2 operand matrices."
				  << std::endl;
		std::cout << "Insert first matrix:"  << std::endl;
		matrix1 = getMatrix();
		std::cout << "Insert second matrix:"  << std::endl;
		matrix2 = getMatrix();
		std::cout << "--------\n" << "Got first matrix:\n\n" << matrix1 << "\n" << std::endl;
		std::cout << "--------\n" << "Got second matrix:\n\n" << matrix2 << "\n" << std::endl;

		if (isInputLegal(operation, matrix1, matrix2))
		{
			std::cout << "==========\nResulted matrix:\n" << std::endl;
			std::cout << calculatedOperation(operation, matrix1, matrix2) << "\n" << std::endl;
		}
		// Case the matrices are not legal for the operation.
		else
		{
			std::cout << "Error: " << operationToString(operation);
			std::cout << " failed - different dimensions." << std::endl;
			return 1;
		}
	}
	// Case unary operation.
	else
	{
		std::cout << "Operation " << operationToString(operation) << 
				     " requires 1 operand matrix." << std::endl;
		matrix1 = getMatrix();
		std::cout << "--------\n" << "got matrix:\n\n" << matrix1 << "\n" << std::endl;

		if (operation == Operation::TRACE) 
		{
			if (isInputLegal(operation, matrix1, matrix2))
			{
				std::cout << "The matrix is square and its trace is " << matrix1.trace() << std::endl;
			}
			// Case the matrix isn't square so it is not legal for the trace operation.
			else
			{
				std::cout << "Error: trace failed - The matrix isn't square." << std::endl;
				return 1;
			}
		}
		// Case operation == Operation::transpose.
		else
		{
			std::cout << "==========\nResulted matrix:\n" << std::endl;
			std::cout << matrix1.trans() << "\n" << std::endl;
		}		
	}
	return 0;
}
