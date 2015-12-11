#ifndef MATRICES_DIMENSIONS_ERROR_H_
#define MATRICES_DIMENSIONS_ERROR_H_

#include <string>
#include <stdexcept>

/**
 * A class that represents an exception that is thrown when an operation cannot be executed because
 * the matrices dimensions does not match the operation requirements.
 */
class MatricesDimensionsError : public std::invalid_argument
{
	public:
		/**
		 * Default constructor.
		 * @param errorMessage the error message to print.
		 */
		explicit MatricesDimensionsError(std::string errorMessage) : std::invalid_argument(
																	 errorMessage)
		{
		}

	private:
};
#endif
