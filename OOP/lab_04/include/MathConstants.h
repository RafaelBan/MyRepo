#ifndef MATH_CONSTANTS_H_
#define MATH_CONSTANTS_H_

static const double EPSILON = 1e-7;

static inline bool isEval(double num1, double num2) { return (num1 - num2) < +EPSILON && (num1 - num2) > -EPSILON; }

#endif // MATH_CONSTANTS_H_

