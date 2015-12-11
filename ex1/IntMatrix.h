// IntMatrix.h
#ifndef INTMATRIX_H_
#define INTMATRIX_H_

#include <iostream>

/**
 *	A Matrix of ints class.
 *	This class represents a matrix and contain matrix operations
 *	methods.
 */
class IntMatrix
{
	public:
		/**
		 * The default constructor.
		 */
		IntMatrix();

		/**
		 * A constructor.
		 * A constructor that is used to create a matrix with a given number of rows and columns.
		 * @param numOfRows the matrix number of rows.
		 * @param numOfCols the matrix number of columns.
		 */
		IntMatrix(const int numOfRows, const int numOfCols);

		/**
		 * A copy constructor.
		 * A constructor that is used to create a copy of a given matrix.
		 * @param matrix the matrix to be copied.
		 */
		IntMatrix(const IntMatrix& matrix); 

		/**
		 * A destructor.
		 */
		~IntMatrix();

		/**
		 * A function that is used to set the matrix size.
		 *
		 * @param numOfRows the matrix number of rows.
		 * @param numOfCols the matrix number of columns.
		 */
		void setMatrixSize(const int numOfRows, const int numOfCols);

		/**
		 * A function that is used to get the matrix number of rows.
		 * 
		 * @return the number of rows in the matrix.
		 */
		int getNumOfRows() const;

		/**
		 * A function that is used to get the matrix number of columns.
		 * 
		 * @returns the number of columns in the matrix.
		 */
		int getNumOfCols() const;


		/**
		 * A function that set a matrix cell.
		 *
		 * @param row the row of the cell.
		 * @param col the column of the cell.
		 * @param value the value to be assigned.
		 */
		void setMatrixCell(const int row, const int col, const int value) const;

		/**
		 * A function that returns a required matrix cell.
		 *
		 * @param row the row of the cell.
		 * @param col the column of the cell.
		 */
		int getMatrixCell(const int row, const int col) const;

		/**
		 * A function that define the = operator.
		 *
		 * @param other the matrix to be assigned with.
		 * @return a reference to the calling object (assigned with the other matrix).
		 */
		IntMatrix& operator=(const IntMatrix& other);

		/**
		 * A function that define the + operator.
		 * 
		 * @param other the matrix to be added.
		 * @return a new IntMatrix object represents a matrix of the sum of the calling object
		 * with the other matrix given by "other".
		 */
		const IntMatrix operator+(const IntMatrix& other) const;

		/**
		 * A function that define the += operator.
		 * 
		 * @param other the matrix to be added.
		 * @return a reference to the calling object (added with the other matrix).
		 */
		IntMatrix& operator+=(const IntMatrix& other);

		/**
		 * A function that define the - operator.
		 *
		 * @param other the matrix to be substracted.
		 * @return a new IntMatrix object represents a matrix of the substraction of the other
		 * matrix given by "other" from the calling object.
		 */
		const IntMatrix operator-(const IntMatrix& other) const;

		/**
		 * A function the define the -= operator'.
		 * 
		 * @param other the matrix to be substracted.
		 * @return a reference to the calling object (substracted by the other matrix).
		 */
		IntMatrix& operator-=(const IntMatrix& other);

		/**
		 * A function that define the * operator.
		 *
		 * @param other the matrix to be multiplied by.
		 * @return a new IntMatrix object represents a matrix of the multiplication of the calling
		 * object by the other matrix given by "other".
		 */
		const IntMatrix operator*(const IntMatrix& other) const;

		/**
		 * A function that define the *= operator.
		 * 
		 * @param other the matrix to be multiplied by.
		 * @return a reference to the calling object (multiplied by the other matrix).
		 */
		IntMatrix& operator*=(const IntMatrix& other);

		/**
		 * A function that returns a transpose of the matrix.
		 *
		 * @return a new object that is transposed to the calling object.
		 */
		IntMatrix trans() const;

		/**
		 * A function that returns the trace of the matrix.
		 *
		 * @return the trace of the calling object.
		 */
		int trace() const;

		/**
		 * set the operator<< as a friend function
		 */
		friend std::ostream& operator<<(std::ostream &output, const IntMatrix& matrix);

	private:	
		int _numOfRows; /**< the matrix number of rows */
		int _numOfCols; /**< the matrix number of columns */
		int *_matrix;  /**< a pointer to the class inner data structure */

};
#endif /* INTMATRIX_H_ */
