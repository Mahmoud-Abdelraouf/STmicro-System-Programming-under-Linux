/**
 * @file main.c
 * @brief A program to perform arithmetic operations on two numbers.
 */

#include <stdio.h>
#include "./mylib/mylib.h"

/**
 * @brief The main function.
 * @return 0 on success.
 */
int main() {
    /**< Input numbers */
    double x, y;
    /**< Results of arithmetic operations */
    double ans1, ans2, ans3, ans4;

    /**< Prompt user to enter the first number */
    printf("Enter first number: ");
    scanf("%lf", &x);

    /**< Prompt user to enter the second number */
    printf("Enter second number: ");
    scanf("%lf", &y);

    /**< Perform arithmetic operations */
    ans1 = myadd(x, y); /**< Addition */
    ans2 = mysub(x, y); /**< Subtraction */
    ans3 = mymul(x, y); /**< Multiplication */
    ans4 = mydiv(x, y); /**< Division */

    /**< Display the results */
    printf("a + b = %7.2lf\n", ans1); /**< Addition result */
    printf("a - b = %7.2lf\n", ans2); /**< Subtraction result */
    printf("a * b = %7.2lf\n", ans3); /**< Multiplication result */
    printf("a / b = %7.2lf\n", ans4); /**< Division result */

    return 0; /**< Return success */
}
