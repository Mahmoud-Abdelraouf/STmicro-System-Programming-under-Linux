/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 14 Mar 2024                *****************/
/******* Version   : 1.0.0                      *****************/
/******* File Name : mylib.h                    *****************/
/****************************************************************/
#ifndef MYLIB_H_ 
#define MYLIB_H_

/**
 * @file mylib.h
 * @brief Declarations of arithmetic functions.
 */

/**
 * @brief Adds two numbers.
 * @param a The first number.
 * @param b The second number.
 * @return The sum of a and b.
 */
double myadd(double, double);

/**
 * @brief Subtracts one number from another.
 * @param a The number to be subtracted from (minuend).
 * @param b The number to subtract (subtrahend).
 * @return The result of subtracting b from a.
 */
double mysub(double, double);

/**
 * @brief Multiplies two numbers.
 * @param a The first number.
 * @param b The second number.
 * @return The product of a and b.
 */
double mymul(double, double);

/**
 * @brief Divides two numbers.
 * @param a The numerator.
 * @param b The denominator.
 * @return The result of a divided by b, or 0 if b is 0.
 */
double mydiv(double, double);

#endif /**< End of include guard MYLIB_H_ */
