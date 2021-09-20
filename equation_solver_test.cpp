//
// Created by vsvood on 9/21/21.
//

#include <cstdio>
#include <cmath>

#include "equation_solver_test.h"
#include "utils.h"

const char* kCheckResultDescription[] {
  "Ok, result and roots are equal to ground truth",
  "Error, result differs from ground truth",
  "Error, roots differ from ground truth"
};

CheckResult Check(double a, double b, double c, Result rightResult, double rightX1, double rightX2, const char* name) {
  puts(name);
  printf("Running test: a=%E b=%E c=%E \n", a, b, c);

  double x1, x2;
  Result result = SolveSqrEquation(a, b, c, &x1, &x2);
  CheckResult check_result;

  if (result == rightResult)
    switch (result) {
      case Result::kSolvedOneRoot:
        if (Equal(x1, rightX1)) {
          printf("OK: one root\n");
          check_result =  CheckResult::kOk;
        }
        else {
          printf("FAIL: x1=%E (%E expected)\n", x1, rightX1);
          check_result =  CheckResult::kWrongRoots;
        }
        break;
      case Result::kSolvedTwoRoots:
        if (Equal(x1, rightX1) && Equal(x2, rightX2)) {
          printf("OK: two roots\n");
          check_result =  CheckResult::kOk;
        }
        else {
          printf("FAIL: x1=%E (%E expected), x2=%E (%E expected)\n",
                 x1, rightX1, x2, rightX2);
          check_result =  CheckResult::kWrongRoots;
        }
        break;
      case Result::kSolvedNoRoots:
      case Result::kSolvedAnyNumber:
      case Result::kCantSolve:
      case Result::kErrorAInfinite:
      case Result::kErrorBInfinite:
      case Result::kErrorCInfinite:
      case Result::kErrorNullptrX1:
      case Result::kErrorNullptrX2:
      case Result::kErrorEqualPtr:
        printf("OK\n");
        check_result =  CheckResult::kOk;
        break;
      default:
        printf("It seems I forgot some cases\n");
        break;
    }
  else {
    printf("FAIL: result = %s (%s expected)\n",
           kResultDescription[(int)result], kResultDescription[(int)rightResult]);
    check_result = CheckResult::kWrongResult;
  }
  printf("----------------------------------------------------------------\n\n");

  return check_result;
}

void SolveSqrEquationTest() {

  Check(1, 2, 1, Result::kSolvedOneRoot, -1, 0, "Simple test");
  Check(0, 0, 0, Result::kSolvedAnyNumber, -1, 0, "Many roots test");
  Check(0, 0, 1, Result::kSolvedNoRoots, -1, 0, "No roots test");
  Check(1e-150, 2e-150, 7.5e-151, Result::kSolvedTwoRoots, -1.5, -0.5, "Little test");
  Check(1e+150, 2e+150, 7.5e+149, Result::kSolvedTwoRoots, -1.5, -0.5, "Big test");
  Check(INFINITY, 2, 1, Result::kErrorAInfinite, -1.5, -0.5, "Infinity test");
  Check(1, 2, 1, Result::kSolvedTwoRoots, -1.5, -0.5, "Fail test");
}
