//
// Created by vsvood on 9/21/21.
//

#include <cstdio>
#include <cmath>

#include "equation_solver_test.h"
#include "utils.h"

const char *kCheckStatusDescription[] = {
  "ok, test passed",
  "solver return wrong status",
  "solver return wrong number of roots",
  "solver return wrong roots"
};

CheckStatus Check(Test test) {
  CustomStatus status = SolveSqrEquation(test.a, test.b, test.c,
                                         test.n_roots_ans, test.x1_ans, test.x2_ans);

  if (status == test.status_truth) {
    if (status != CustomStatus::kOk) { return CheckStatus::kOk; }  // Error occurred and correctly treated

    if (*(test.n_roots_ans) == test.n_roots_truth) {  // Equation solved, checking answers
      if ((test.n_roots_truth == NRoots::kNoRoots) ||
          (test.n_roots_truth ==NRoots::kAnyNumber)) {  // Zero or inf roots cases
        return CheckStatus::kOk;
      }

      if (test.n_roots_truth == NRoots::kOneRoot) {  // One root case
        if (Equal(*(test.x1_ans), test.x1_truth)) { return CheckStatus::kOk; }

        return CheckStatus::kWrongRoots;
      }

      if (test.n_roots_truth == NRoots::kTwoRoots) {  // Two roots case
        if (Equal(*(test.x1_ans), test.x1_truth) &&
            Equal(*(test.x2_ans), test.x2_truth)) { return CheckStatus::kOk; }

        return CheckStatus::kWrongRoots;
      }
    }
    return CheckStatus::kWrongNRoots;
  }
  return CheckStatus::kWrongStatus;
}

CheckStatus SolveSqrEquationTest() {
  const int kNumTests = 7;

  NRoots n_roots = NRoots::kNoRoots;
  double x1 = NAN;
  double x2 = NAN;

  Test test[kNumTests] = {
    //simple test
    {1, 2, 1, &n_roots, &x1, &x2,
     CustomStatus::kOk, NRoots::kOneRoot, -1},
     // any number is root test
    {0, 0, 0, &n_roots, &x1, &x2,
     CustomStatus::kOk, NRoots::kAnyNumber},
     // no roots test
    {0, 0, 1, &n_roots, &x1, &x2,
     CustomStatus::kOk, NRoots::kNoRoots},
     // little test
    {1e-150, 2e-150, 7.5e-151, &n_roots, &x1, &x2,
     CustomStatus::kOk, NRoots::kTwoRoots, -1.5, -0.5},
     // big test
    {1e150, 2e150, 7.5e149, &n_roots, &x1, &x2,
     CustomStatus::kOk, NRoots::kTwoRoots, -1.5, -0.5},
     // inf input params test
    {INFINITY, 2, 1, &n_roots, &x1, &x2,
     CustomStatus::kWrongInputParams},
     // nullptr for output test
    {1, 2, 1, nullptr, &x1, &x2,
     CustomStatus::kWrongOutputParams},
  };

  CheckStatus status = CheckStatus::kOk;
  for (int i = 0; i < kNumTests; ++i) {
    status = Check(test[i]);
    if (status != CheckStatus::kOk) {
      printf("Test %d failed with '%s' error\n", i, kCheckStatusDescription[(int)status]);
      return status;
    }
  }

  printf("All tests passed\n");

  return status;
}
