#ifndef NOT_SQUARE_MATRIX_TRACE_H_
#define NOT_SQUARE_MATRIX_TRACE_H_

#include <exception>

class NotSquareMatrixTrace : public std::invalid_argument
{
	public:
		/**
		 * Default constructor.
		 * @param errorMessage the error message to print.
		 */
		explicit NotSquareMatrixTrace(std::string errorMessage) : std::invalid_argument(errorMessage)
		{
		}

	private:
};
#endif
