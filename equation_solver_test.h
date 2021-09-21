//
// Created by vsvood on 9/21/21.
//

#ifndef SQREQUATIONSOLVER_EQUATION_SOLVER_TEST_H
#define SQREQUATIONSOLVER_EQUATION_SOLVER_TEST_H

#include "equation_solver.h"

enum class CheckStatus {
    kOk,
    kWrongStatus,
    kWrongNRoots,
    kWrongRoots,
};

extern const char *kCheckStatusDescription[];

struct Test {
    double a, b, c;
    NRoots *n_roots_ans;
    double *x1_ans, *x2_ans;
    CustomStatus status_truth;
    NRoots n_roots_truth;
    double x1_truth, x2_truth;
};

/**
 * @brief Run SolveSqrEquation on specified test
 *
 * @param test - test for SolveSqrEquation
 *
 * @return member of CheckStatus:\n
 * kOk - test passed\n
 * kWrongStatus - solver return wrong status\n
 * kWrongNRoots - solver return wrong number of roots\n
 * kWrongRoots - solver return wrong roots
 */

CheckStatus Check(Test test);

/**
 * @brief Tests SolveSqrEquation with several presets
 *
 * @return CheckStatus::kOk if all tests passed, status of first failed test otherwise
 */

CheckStatus SolveSqrEquationTest();

#endif //SQREQUATIONSOLVER_EQUATION_SOLVER_TEST_H
