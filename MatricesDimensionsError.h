#ifndef MATRICES_DIMENSIONS_ERROR_H_
#define MATRICES_DIMENSIONS_ERROR_H_

#include <exception>

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
