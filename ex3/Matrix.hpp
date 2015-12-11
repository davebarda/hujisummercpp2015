#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <iostream>
#include <algorithm>
#include <exception>
#include <vector>
#include <iterator>
#include <thread>
#include "Complex.h"
#include "MatricesDimensionsError.h"
#include "NotSquareMatrixTrace.h"

const int ZERO_ELEMENT_CTOR_INPUT = 0;
const char MATRIX_ROW_CELLS_SEPERATOR = '\t';
const int DEFAULT_CTOR_ROWS = 1;
const int DEFAULT_CTOR_COLS = 1;

/**
 * A template class represents a Generic matrix implementation.
 */
template<typename T>
class Matrix
{	
	private:
		typedef void (Matrix<T>::*parallelCalcMethod) (const Matrix<T>&, Matrix<T>&, unsigned int) 
													   const; /**<A typedef defines a pointer to 
																function that used for 
																parallel calculation. */
		std::vector<T> _matrix; /**< A vector contains the matrix data*/
		unsigned int _numOfRows; /**< The number of rows */
		unsigned int _numOfCols; /**< The number of cols */
		static bool _isParallel; /**< A static member that is used to decide wheter to use parallel
								   * computation or not */

		/**
		 * A method that is used to calc the sum of the calling object row with a given other row
		 * and save it to the same row at sol.
		 * @param other the matrix to sum the row with.
		 * @param sol the matrix to save the solution at.
		 * @param row the row to sum.
		 */
		void _calcRowSum(const Matrix<T> &other, Matrix<T> &sol, unsigned int row) const noexcept
		{
			for (unsigned int i = 0; i < _numOfCols; i++)
			{
				sol(row, i) = (*this)(row, i) + other(row, i);
			}
		}

		/**
		 * A method that is used to calc the multipication of the calling object row with 
		 * a given other column and save it to the sol.
		 * done by the multipication iteration method.
		 * @param other the matrix to multiply with its column.
		 * @param sol the matrix to save the solution at.
		 * @param row the row of the solution.
		 */
		void _calcRowMul(const Matrix<T> &other, Matrix<T> &sol, unsigned int row) const noexcept
		{
			T tempSum(ZERO_ELEMENT_CTOR_INPUT);
			for (unsigned int i = 0; i < sol._numOfCols; i++)
			{
				for (unsigned int j = 0; j < other._numOfCols; j++)
				{
					tempSum += ((*this)(row, j) * other(j, i));
				}
				sol(row, i) = tempSum;
				tempSum = T(ZERO_ELEMENT_CTOR_INPUT);
			}
		}

		/**
		 * A method used to calculate parallel computations.
		 * @param other the right hand matrix of the operation.
		 * @param resMatrix the matrix to fill the row at.
		 * @param calcRow a pointer to a function used to calculate the computation
		 * given by the typedef parallelCalcMethod.
		 * @throws std::bad_alloc
		 */
		void _calculateParallel(const Matrix<T> &other, 
							    Matrix<T> &resMatrix, parallelCalcMethod calcRow) const
		{
				std::vector<std::thread> threads;
				for (unsigned int i = 0; i < _numOfRows; i++)
				{
					threads.push_back(std::thread(calcRow, this, other, std::ref(resMatrix), i));
				}

				// Join the threads after the loop so all the threads will run parallel and not
				// sequential.
				for (std::vector<std::thread>::iterator it = threads.begin(); 
					 it != threads.end(); it++)
				{
					it->join();
				}	
		}

	public:
	

		typedef typename std::vector<T>::const_iterator const_iterator;  /**< A typedef defines 
																		   the const_iterator 
																		   type */
		/**
		 * A method that is used to determine whether the + and * operator will be calculated
		 * parallel or not.
		 * @param setParallel a variable determines if the next sum and multiply operations executed
		 * by the + and * operators will be calculated parallel.
		 */
		static void setParallel(bool setParallel) noexcept
		{
			if (_isParallel != setParallel)
			{
				if(setParallel)
				{
					std::cout << "Generic Matrix mode changed to parallel mode."  << std::endl;
				}
				else
				{
					std::cout << "Generic Matrix mode changed to non-parallel mode." << std::endl;
				}
			}
			_isParallel = setParallel;
		}

		/**
		 * The default ctor creates a matrix with DEFAULT_CTOR_ROWS rows and 
		 * DEFAULT_CTOR_COLS columns contains the value T(0).
		 * @throws std::bad_alloc.
		 */
		// Delegate to Matrix(rows, cols) ctor
		Matrix() : Matrix(DEFAULT_CTOR_ROWS, DEFAULT_CTOR_COLS) 
		{
		}

		/**
		 * A ctor used to create a matrix with a given number of rows and columns.
		 * @param rows the number of rows.
		 * @param cols the number of columns.
		 * @throws std::bad_alloc.
		 * @throws std::invalid_argument.
		 */
		Matrix(unsigned int rows, unsigned int cols): 
			   _matrix((rows * cols), T(ZERO_ELEMENT_CTOR_INPUT)), _numOfRows(rows), 
			   _numOfCols(cols)
		{
			// Case only one of the row / cols equal to 0
			if ((rows == 0 || cols == 0) && (rows != cols))
			{
				throw std::invalid_argument("Cannot create matrix with row or "
											 "col > 0 and the other parameter > 0");
			}
		}

		/**
		 * A ctor used to create a matrix with a given number of rows and a given number of columns
		 * that its values will be taken from a given container.
		 * @param rows the number of rows.
		 * @param cols the number of cols.
		 * @param cells the vector to take the values from.
		 * @throws std::bad_alloc.
		 * @throws std::invalid_argument.
		 */
		Matrix(unsigned int rows, unsigned int cols, const std::vector<T>& cells)
			   : _numOfRows(rows), _numOfCols(cols)
		{
			// Case only one of the row / cols equal to 0
			if ((rows == 0 || cols == 0) && (rows != cols))
			{
				throw std::invalid_argument("Cannot create matrix with row or "
											 "col > 0 and the other parameter > 0");
			}
			
			// Case the vector given is not in the given size.
			if (cells.size() != (rows * cols))
			{
				throw std::invalid_argument("Rows or cols didn't match the size of "
											"the given container");
			}
			_matrix = cells;
		}

		/**
		 * The copy ctor used to create an independant copy of a given matrix.
		 * @param other the matrix to copy.
		 * @throws std::bad_alloc.
		 */
		Matrix(const Matrix<T> &other) : _matrix(other._matrix), _numOfRows(other._numOfRows), 
			   _numOfCols(other._numOfCols)
		{
		}

		/**
		 * Move ctor.
		 */
		Matrix(Matrix<T> && other) noexcept : _matrix(std::move(other._matrix)), 
											  _numOfRows(std::move(other._numOfRows)), 
											  _numOfCols(std::move(other._numOfCols))
		{
			other._numOfRows = 0;
			other._numOfCols = 0;
		}

		/**
		 * The default destructor.
		 */
		~Matrix() noexcept
		{
		}
			
		/**
		 * A method that overload the = operator.
		 * @param other the matrix(from the same type) to be assigned with.
		 * @return a reference to the calling object (assigned with the other matrix).
		 */
		Matrix<T>& operator=(Matrix<T> other) noexcept
		{
			swap(*this, other);
			return *this;
		}

		/**
		 * A method that overload the () operator.
		 * @param row the row of the cell.
		 * @param col the column of the cell.
		 * @return matrix[i,j] which reference to the matrix.
		 * @throws std::out_of_range exception.
		 */
		T& operator()(unsigned int row, unsigned int col)
		{
			try
			{
				return _matrix.at((row * _numOfCols) + col);	
			}
			catch (std::out_of_range&)
			{
				throw std::out_of_range("Matrix indices are out of range");
			}
		}
			
		/**
		 * A method that overload the () operator.
		 * @param row the row of the cell.
		 * @param col the column of the cell.
		 * @return a copy of the cell matrix[i,j].
		 * @throws std::out_of_range exception.
		 */
		const T& operator()(unsigned int row, unsigned int col) const
		{	
			try
			{
				return _matrix.at((row * _numOfCols) + col);	
			}
			catch (std::out_of_range &ex)
			{
				throw std::out_of_range("Matrix indices are out of range");
			}
		}

		/**
		 * A method that overload the + operator.
		 * @param other the matrix to be added, should be of the same dimensions as the
		 * calling object.
		 * @return a new matrix, the sum of the calling object
		 * with the other matrix given by "other".
		 * @throws MatricesDimensionsError.
		 * @throws std::system_error
		 * @throws std::bad_malloc
		 */
		const Matrix<T> operator+(const Matrix<T> &other) const
		{
			if (_numOfRows != other._numOfRows || _numOfCols != other._numOfCols)
			{
				throw MatricesDimensionsError("Cannot sum matrices from different dimensions");
			}

			Matrix<T> resMatrix(_numOfRows, _numOfCols);

			// Case the matrix is in "parallel mode".
			if (_isParallel) 
			{
				_calculateParallel(other, resMatrix, &Matrix<T>::_calcRowSum);
			}
			// Case the matrix is in "sequential mode"
			else
			{
				for (unsigned int i = 0; i < (_numOfRows * _numOfCols); i++)
				{
					resMatrix._matrix.at(i) = this->_matrix.at(i) + other._matrix.at(i);
				}
			}
			return resMatrix;
		}

		/**
		 * A method that overload the - operator.
		 * @param other the matrix to be substracted, should be of the same dimensions as the
		 * calling object.
		 * @return a new matrix, the substract of the other matrix given by "other"
		 * from the calling object.
		 */
		const Matrix<T> operator-(const Matrix<T> &other) const
		{
			if (_numOfRows != other._numOfRows || _numOfCols != other._numOfCols)
			{
				throw MatricesDimensionsError("Cannot substract matrices"
											  "from different dimesnions");
			}
			Matrix<T> resMatrix(_numOfRows, _numOfCols);
			for (unsigned int i = 0; i < _matrix.size(); i++)
			{
				resMatrix._matrix.at(i) = _matrix.at(i) - other._marix.at(i);
			}
			return resMatrix;
		}

		/**
		 * A method that overload the * operator.
		 * @param other the matrix to be multiplied by, the number of its rows should be equal to
		 * the calling object number of columns.
		 * @return a new matrix, the multipication of the calling object with the other matrix given
		 * by "other".
		 * @throws MatricesDimensionsError.
		 * @throws std::system_error
		 * @throws std::bad_malloc
		 */
		const Matrix<T> operator*(const Matrix<T> &other) const
		{
			if (_numOfCols != other._numOfRows)
			{
				throw MatricesDimensionsError("Cannot multiply matrices "
											  "that the left hand matrix columns "
											  "is not equal to the right hand matrix rows");
			}

			Matrix<T> resMatrix(_numOfRows, other._numOfCols);

			// Case the matrix is in "parallel mode"
			if (_isParallel) 
			{
				_calculateParallel(other, resMatrix, &Matrix<T>::_calcRowMul);
			}
			// Case the matrix is in "sequential mode"
			else
			{
				T tempSum(ZERO_ELEMENT_CTOR_INPUT);
				/* ResultMatrix[i,j] is the sum from 0 to k-1 of right-handed matrix[i,k] * left-handed
				 * matrix[k,j] */
				for (unsigned int i = 0; i < resMatrix._numOfRows; i++)
				{
					for (unsigned int j = 0; j < resMatrix._numOfCols; j++) 
					{
						for (unsigned int k = 0; k < _numOfCols; k++)
						{
							tempSum += ((*this)(i, k) * other(k, j));
						}
						resMatrix(i, j) = tempSum;
						tempSum = T(ZERO_ELEMENT_CTOR_INPUT);
					}
				}
			}
			return resMatrix;
		}
		
		/**
		 * A method that overload the == operator.
		 * @param other the matrix to check if the calling object is equal to.
		 * @return true iff the matrices cells are equal and the number of rows and columns of 
		 * the matrices are equal.
		 */
		bool operator==(Matrix<T> &other) const noexcept
		{
			return ((_matrix == other._matrix) && (_numOfRows == other._numOfRows) 
					&& (_numOfCols == other._numOfCols));
		}

		/**
		 * A method that overload the != operator.
		 * @param other the matrix to check if the calling object is not equal to.
		 * @return true iff the matrices are not equal by the operator==.
		 */
		bool operator!=(Matrix<T> &other) const noexcept
		{
			return !(*this == other);
		}

		/**
		 * A method that returns a transpose of the matrix.
		 * @return a new object that is transposed to the calling object.
		 * @throws std::bad_malloc
		 */
		Matrix<T> trans() const
		{
			Matrix<T> resMatrix(_numOfCols, _numOfRows);

			/* newMatrix[j,i] = oldMatrix[i,j] for every i < oldMatrix.numOfRows, 
			 * j < oldMatrix.numOfCols */
			for (unsigned int i = 0; i < _numOfRows; i++)
			{
				for (unsigned int j = 0; j < _numOfCols; j++) 
				{
					resMatrix(j, i) = (*this)(i, j);
				}
			}

			return resMatrix;
		}

		/**
		 * A method that returns the trace of the matrix.
		 *
		 * @return the trace of the calling object.
		 * @throws NotSquareMatrixTrace.
		 */
		const T trace() const
		{
			if (!isSquareMatrix())
			{
				throw NotSquareMatrixTrace("Tried to trace a matrix that is not square");
			}

			T traceResult(ZERO_ELEMENT_CTOR_INPUT);

			// Sum the values at the main diagonal to get the trace of the matrix
			for (unsigned int i = 0; i < _numOfCols; i++) 
			{
				traceResult += (*this)(i, i);
			}	
			return traceResult;
		}
		
		/**
		 * A method that returns the number of rows of the matrix.
		 * @return the numbers of rows of the matrix.
		 */
		int rows() const noexcept
		{
			return _numOfRows;
		}

		/**
		 * A method that returns the number of cols of the matrix.
		 * @return the numbers of cols of the matrix.
		 */
		int cols() const noexcept
		{
			return _numOfCols;
		}

		/**
		 * A friend function that swap the data between two matrices.
		 * @param first the first matrix to swap.
		 * @param second the matrix to swap.
		 */
		friend void swap(Matrix<T> &first, Matrix<T> &second) noexcept
		{
			std::swap(first._matrix, second._matrix);
			std::swap(first._numOfRows, second._numOfRows);
			std::swap(first._numOfCols, second._numOfCols);
		}

		/**
		 * A method that returns true iff the matrix is square(The number of rows equal to the
		 * number of columns).
		 * @return true iff the matrix is square.
		 */
		bool isSquareMatrix() const noexcept
		{
			return (_numOfRows == _numOfCols);
		}

		/**
		 * A method that returns an iterator to the beginning of the matrix.
		 * @return a const iterator to the first cell(top to the left) of the matrix.
		 */
		const_iterator begin() const noexcept
		{
			return _matrix.begin();
		}		

		/**
		 * A method that returns a const iterator to the end of the matrix.
		 * @return iterator a const iterator to the past the end of the matrix.
		 */
		const_iterator end() const noexcept
		{
			return _matrix.end();
		}

		/**
		 * Set the operator<< for output stream as a friend function.
		 * @param output the stream.
		 * @param matrix the matrix to set to the output stream.
		 * throws std::ios_base::failure.
		 */
		friend std::ostream& operator<<(std::ostream &output, const Matrix<T> &matrix)
		{
			for (unsigned int i = 0; i < (matrix._numOfRows * matrix._numOfCols); i++) 
			{
				output << matrix._matrix[i];
				output << MATRIX_ROW_CELLS_SEPERATOR;

				// Write a new line character in every end of line
				if (((i + 1) % matrix._numOfCols) == 0)
				{
					output << std::endl;
				}
			}
			return output;
		}
};

// Initialization of static members.
template<typename T>
bool Matrix<T>::_isParallel = false;

// Methods specializations.

/**
 * A method that returns the conjugate transpose of the matrix.
 * @return a new object the conjugate transposed to the calling object.
 * @throws std::bad_malloc
 */
template<>
Matrix<Complex> Matrix<Complex>::trans() const
{
	Matrix<Complex> resMatrix(_numOfCols, _numOfRows);

	/* newMatrix[j,i] = oldMatrix[i,j] for every i < oldMatrix.numOfRows, 
	 * j < oldMatrix.numOfCols */
	for (unsigned int i = 0; i < _numOfRows; i++)
	{
		for (unsigned int j = 0; j < _numOfCols; j++) 
		{
			resMatrix(j, i) = (*this)(i, j).conj();
		}
	}

	return resMatrix;
}
#endif // MATRIX_HPP_
