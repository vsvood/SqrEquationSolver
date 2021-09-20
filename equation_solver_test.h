//
// Created by vsvood on 9/21/21.
//

#ifndef SQREQUATIONSOLVER_EQUATION_SOLVER_TEST_H
#define SQREQUATIONSOLVER_EQUATION_SOLVER_TEST_H

#include "equation_solver.h"

enum class CheckResult {
    kOk,
    kWrongResult,
    kWrongRoots
};

extern const char* kCheckResultDescription[];

/**
 * \brief Checks SolveSqrEquation with current params
 * @param[in] a - a coefficient
 * @param[in] b - b coefficient
 * @param[in] c - c coefficient
 * @param[in] kEps - minimum relative difference of different values
 * @param[in] rightNRoots - right number of roots
 * @param[in] rightX1 - right fst root (can be any if result = 0 or INFINITY)
 * @param[in] rightX2 - right snd root (can be any if result = 0 or 1 or INFINITY)
 * @param[in] name - name of test
 *
 * @return member of enum CheckResult:\n
 * kOk - ok, result and roots are equal to ground truth\n
 * kWrongResult - error, result differs from ground truth\n
 * kWrongRoots - error, roots differ from ground truth
 */

CheckResult Check(double a, double b, double c, Result rightResult, double rightX1, double rightX2, const char* name);

/**
 * \brief Tests SolveSqrEquation with several presets
 */

void SolveSqrEquationTest();

#endif //SQREQUATIONSOLVER_EQUATION_SOLVER_TEST_H
