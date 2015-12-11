#ifndef NOT_SQUARE_MATRIX_TRACE_H_
#define NOT_SQUARE_MATRIX_TRACE_H_

#include <string>
#include <stdexcept>

/**
 * A class that represents an exception is thrown when trying to execute trace operation over a
 * matrix that is not square.
 */
class NotSquareMatrixTrace : public std::invalid_argument
{
	public:
		/**
		 * Default constructor.
		 * @param errorMessage the error message to print.
		 */
		explicit NotSquareMatrixTrace(std::string errorMessage) : 
									  std::invalid_argument(errorMessage)
		{
		}

	private:
};
#endif
