//
// Created by vsvood on 9/21/21.
//

#ifndef SQREQUATIONSOLVER_EQUATION_SOLVER_H
#define SQREQUATIONSOLVER_EQUATION_SOLVER_H

enum class Result {
    kSolvedNoRoots,
    kSolvedOneRoot,
    kSolvedTwoRoots,
    kSolvedAnyNumber,
    kCantSolve,
    kErrorAInfinite,
    kErrorBInfinite,
    kErrorCInfinite,
    kErrorNullptrX1,
    kErrorNullptrX2,
    kErrorEqualPtr
};

extern const char* kResultDescription[];

/**
 * \brief Solves equation ax2+bx+c=0
 *
 * @param[in] a - a coefficient
 * @param[in] b - b coefficient
 * @param[in] c - c coefficient
 * @param[out] x1 - first root (specified when equation has 1 or 2 roots)
 * @param[out] x2 - second root (specified when equation has 2 roots)
 *
 * @return member of enum Result:\n
 * kSolvedNoRoots - solved, no roots was found\n
 * kSolvedOneRoot - solved, one root was found\n
 * kSolvedTwoRoots - solved, two roots were found\n
 * kSolvedAnyNumber - solved, any number is root\n
 * kCantSolve - can`t solve, overflow while calculating ans\n
 * kErrorAInfinite - error, a coefficient is infinite\n
 * kErrorBInfinite - error, b coefficient is infinite\n
 * kErrorCInfinite - error, c coefficient is infinite\n
 * kErrorNullptrX1 - error, nullptr is given for x1 output\n
 * kErrorNullptrX2 - error, nullptr is given for x2 output\n
 * kErrorEqualPtr - error, same pointers were given for x1 and x2
 */

Result SolveSqrEquation(double a, double b, double c, double* x1, double* x2);

#endif //SQREQUATIONSOLVER_EQUATION_SOLVER_H
