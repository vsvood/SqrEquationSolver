//
// Created by vsvood on 9/21/21.
//

#ifndef SQREQUATIONSOLVER_EQUATION_SOLVER_H
#define SQREQUATIONSOLVER_EQUATION_SOLVER_H

#include "custom_status_lib.h"

enum class NRoots {
    kNoRoots,
    kOneRoot,
    kTwoRoots,
    kAnyNumber
};

/**
 * @brief Solves equation ax+b=0
 *
 * @param a - a coefficient
 * @param b - b coefficient
 * @param n_roots - number of roots
 * @param x1 - first root (specified when equation has 1 root)
 *
 * @return member of enum CustomStatus:\n
 * kOk - ok, solved\n
 * kWrongInputParams - inf coefficients given\n
 * kWrongOutputParams - nullptr given for output params\n
 * kRuntimeError - overflow occurred, can`t solve
 */

CustomStatus SolveLinearEquation(double a, double b, NRoots *n_roots, double *x1);

/**
 * @brief Solves equation ax2+bx+c=0
 *
 * @param[in] a - a coefficient
 * @param[in] b - b coefficient
 * @param[in] c - c coefficient
 * @param[out] n_roots - number of roots
 * @param[out] x1 - first root (specified when equation has 1 or 2 roots)
 * @param[out] x2 - second root (specified when equation has 2 roots)
 *
 * @return member of enum CustomStatus:\n
 * kOk - ok, solved\n
 * kWrongInputParams - inf coefficients given\n
 * kWrongOutputParams - nullptr or equal ptr given for output params\n
 * kRuntimeError - overflow occurred, can`t solve\n
 */

CustomStatus SolveSqrEquation(double a, double b, double c, NRoots *n_roots, double *x1, double *x2);

#endif //SQREQUATIONSOLVER_EQUATION_SOLVER_H
