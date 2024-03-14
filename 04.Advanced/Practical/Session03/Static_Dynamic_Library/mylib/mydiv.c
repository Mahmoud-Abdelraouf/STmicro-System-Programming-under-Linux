/**
 * @file mylib.c
 * @brief Contains arithmetic functions.
 */

/**
 * @brief Divides two numbers.
 * @param a The numerator.
 * @param b The denominator.
 * @return The result of a divided by b, or 0 if b is 0.
 */
double mydiv(double a, double b){
    /**< Check if the denominator is not zero */
	if (b != 0)
   		return a / b; /**< Return the result of the division */
	return 0; /**< Return 0 if division by zero is attempted */
}
