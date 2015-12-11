#include "IntMatrix.h"
#include <cassert>

#define MATRIX_ROW_CELLS_SEPERATOR " "

/*
 * ------------------------------------------------------------
 * This file contains the implementation of the class IntMatrix
 * ------------------------------------------------------------
 */

// -----Constructors & Destructor-----

/**
 * @see IntMatrix()
 */
IntMatrix::IntMatrix() : _numOfRows(0), _numOfCols(0), _matrix(nullptr)
{
}

/**
 * @see IntMatrix::IntMatrix(const int numOfRows, const int numOfCols)
 */
IntMatrix::IntMatrix(const int numOfRows, const int numOfCols) : IntMatrix()
{
	setMatrixSize(numOfRows, numOfCols);
}


/**
 * @see IntMatrix::IntMatrix(const IntMatrix& matrix)
 */
IntMatrix::IntMatrix(const IntMatrix& matrix) : IntMatrix()
{
	*this = matrix;
}

/**
 * @see IntMatrix::~IntMatrix()
 */
IntMatrix::~IntMatrix()
{
	delete[] _matrix;
}

// -----Access methods-----
/**
 * @see IntMatrix::setMatrixSize(const int numOfRows, const int numOfCols)
 */
void IntMatrix::setMatrixSize(const int numOfRows, const int numOfCols)
{
	delete[] _matrix;
	this->_numOfRows = numOfRows;
	this->_numOfCols = numOfCols;
	_matrix = new int[(numOfRows * numOfCols)];
}

/**
 * @see IntMatrix::setMatrixCell(const int row, const in col, const int value)
 */
void IntMatrix::setMatrixCell(const int row, const int col, const int value) const
{
	_matrix[(_numOfCols * row) + col] = value;
}

/**
 * @see IntMatrix::getNumOfRows()
 */
int IntMatrix::getNumOfRows() const
{
	return _numOfRows;
}

/**
 * @see IntMatrix::getNumOfCols()
 */
int IntMatrix::getNumOfCols() const
{
	return _numOfCols;
}


/**
 * @see IntMatrix::getMatrixCell(const int row, const int col)
 */
int IntMatrix::getMatrixCell(const int row, const int col) const
{
	return _matrix[(row * _numOfCols) + col];
}

// -----Other methods-----

/**
 * @see IntMatrix::operator=(const IntMatrix& other)
 */
IntMatrix& IntMatrix::operator=(const IntMatrix& other)
{
	// Case this == &other nothing need to be done
	if (this == &other) 
	{
		return *this;
	}

	_numOfRows = other._numOfRows;
	_numOfCols = other._numOfCols;
	delete[] _matrix;
	_matrix = new int[_numOfRows * _numOfCols];
	std::copy(other._matrix, other._matrix + (_numOfRows * _numOfCols), _matrix);
	return *this;
}

/**
 * @see IntMatrix::operator+=(const IntMatrix& other)
 */
IntMatrix& IntMatrix::operator+=(const IntMatrix& other)
{
	assert(_numOfRows == other._numOfRows);
	assert(_numOfCols == other._numOfCols);

	for (int i = 0; i < _numOfRows; i++)
	{
		for (int j = 0; j < _numOfCols; j++) 
		{
			setMatrixCell(i, j, getMatrixCell(i, j) + other.getMatrixCell(i, j));
		}
	}
	return *this;
}

/**
 * @see const IntMatrix::operator+(const IntMatrix& other)
 */
const IntMatrix IntMatrix::operator+(const IntMatrix& other) const
{
	assert(_numOfRows == other._numOfRows);
	assert(_numOfCols == other._numOfCols);

	/* Copy the "this" IntMatrix using the ctor and then use the += operator 
	to add the other IntMatrix. */
	return IntMatrix(*this) += other;
}

/**
 * @see IntMatrix::operator-=(const IntMatrix& other)
 */
IntMatrix& IntMatrix::operator-=(const IntMatrix& other)
{
	assert(_numOfRows == other._numOfRows);
	assert(_numOfCols == other._numOfCols);

	for (int i = 0; i < _numOfRows; i++)
	{
		for (int j = 0; j < _numOfCols; j++) 
		{
			setMatrixCell(i, j, getMatrixCell(i, j) - other.getMatrixCell(i, j));
		}
	}
	return *this;	

}

/**
 * @see IntMatrix::operator-(const IntMatrix& other)
 */
const IntMatrix IntMatrix::operator-(const IntMatrix& other) const
{
	assert(_numOfRows == other._numOfRows);
	assert(_numOfCols == other._numOfCols);

	/* Copy the "this" IntMatrix using the ctor and then use the -= operator 
	to sub the other IntMatrix. */
	return IntMatrix(*this) -= other;
}

/**
 * @see IntMatrix::operator*=(const IntMatrix& other)
 */
IntMatrix& IntMatrix::operator*=(const IntMatrix& other)
{
	assert(_numOfCols == other._numOfRows);

	// Set this to be equal to the the multipication of the calling matrix with the other matrix
	return *this = ((*this) * other);
}

/**
 * @see IntMatrix::operator*(const IntMatrix& other)
 * Using simple multipication algorithm such that 
 * result[i,j] equals to the sum from k=0 to lefthand.numOfCols(=righthand.numOfRows in legal
 * multiplication) of left-handed-matrix[i,k] * right-hand-matrix[k,j]
 */
const IntMatrix IntMatrix::operator*(const IntMatrix& other) const
{
	assert(_numOfCols == other._numOfRows);

	IntMatrix resMatrix(_numOfRows, other._numOfCols);
	int tempSum = 0;

	/* ResultMatrix[i,j] is the sum from 0 to k-1 of right-handed matrix[i,k] * left-handed
	 * matrix[k,j] */
	for (int i = 0; i < resMatrix._numOfRows; i++)
	{
		for (int j = 0; j < resMatrix._numOfCols; j++) 
		{
			for (int k = 0; k < _numOfCols; k++)
			{
				tempSum += getMatrixCell(i, k) * other.getMatrixCell(k, j);
			}
			resMatrix.setMatrixCell(i, j, tempSum);
			tempSum = 0;
		}
	}
	return resMatrix;
}

/**
 * @see IntMatrix::trans()
 */
IntMatrix IntMatrix::trans() const
{
	IntMatrix resMatrix(_numOfCols, _numOfRows);
	for (int i = 0; i < _numOfRows; i++)
	{
		for (int j = 0; j < _numOfCols; j++) 
		{
			resMatrix.setMatrixCell(j, i, getMatrixCell(i, j));
		}
	}
	return resMatrix;
}


/**
 * @see IntMatrix::trace()
 */
int IntMatrix::trace() const
{
	assert(_numOfRows == _numOfCols);
	int traceResult = 0;
	// Sum the values at the main diagonal to get the trace of the matrix
	for (int i = 0; i < _numOfCols; i++) 
	{
		traceResult += getMatrixCell(i, i);
	}	
	return traceResult;
}

/**
 * @see operator<<(std::ostream& output, const IntMatrix& matrix)
 */
std::ostream& operator<<(std::ostream& output, const IntMatrix& matrix)
{
	for (int i = 0; i < (matrix._numOfRows * matrix._numOfCols); i++) 
	{
		output << matrix._matrix[i];
		if (((i + 1) % matrix._numOfCols) == 0)
		{
			// Skip the new line in the last line
			if ((i + 1) != (matrix._numOfRows * matrix._numOfCols))
			{	
				output << std::endl;
			}
		}
		else 
		{
			output << MATRIX_ROW_CELLS_SEPERATOR;
		}
	}
	return output;
}
