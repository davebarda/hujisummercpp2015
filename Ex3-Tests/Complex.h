/**
 * Complex - class to represent a complex number 
 * 
 */
#ifndef COMPLEX_H
#define COMPLEX_H

#include <iosfwd>


class Complex
{
public:
	/**
	* Constructors geting double or default which is set to 0
	*/
	Complex(const double  &value = 0);
	/**
	* Constructors geting real and imaginary part
	*/
	Complex(const double  &real, const double &imaginary);
	/**
	* Returns the conjugate of this complex number
	*/
	const Complex conj() const;
	/**
	 * Returns the real part
	 */
	double getReal() const;
	/**
	 * Returns the imaginary part
	 */
	 double getImaginary() const;
	/**
	 * Summing two Complexs
	 */
	const Complex operator+(const Complex &other) const;

	/**
	 * Summing two Complexs
	 */
	Complex operator+=(const Complex &other);
	/**
	 * Multiplying operator for Complex
	 */
	/**
	 * subtraction OF two Complexs
	 */
	Complex operator-=(const Complex &other);
		/**
	 * subtraction of two Complexs
	 */
	const Complex operator-(const Complex &other) const;
		const Complex operator*(const Complex &other) const;
	/**
	 * operator<< for stream insertion
	 * The format is <real> + <img>i
	 */
	friend std::ostream& operator<<(std::ostream &os, const Complex &number);
	/**
	 * operator== and operator!= for comparing complex numbers
	 */
	 bool operator==(const Complex &other) const;
	 bool operator!=(const Complex &other) const;

private:
	double _real;
	double _imaginary;
};

#endif
