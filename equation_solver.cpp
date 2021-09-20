//
// Created by vsvood on 9/21/21.
//

#include "equation_solver.h"

#include <cmath>

#include "utils.h"

const char* kResultDescription[] = {
  "'No roots'",
  "'One root'",
  "'Two roots'",
  "'Any number is root'",
  "'Can't solve'",
  "'a is infinite'",
  "'b is infinite'",
  "'c is infinite'",
  "'x1 is nullptr'",
  "'x2 is nullptr'",
  "'x1 and x2 are equal ptr'"
};

Result SolveSqrEquation(double a, double b, double c, double* x1, double* x2) {
  if (std::isinf(a))
    return Result::kErrorAInfinite;
  if (std::isinf(b))
    return Result::kErrorBInfinite;
  if (std::isinf(c))
    return Result::kErrorCInfinite;
  if (x1 == nullptr)
    return Result::kErrorNullptrX1;
  if (x2 == nullptr)
    return Result::kErrorNullptrX2;
  if (x1 == x2)
    return Result::kErrorEqualPtr;

  if (Equal(a, 0))  // linear equation case
    if (Equal(b, 0))
      if (Equal(c, 0))  // 0x = 0 - any number is root
        return Result::kSolvedAnyNumber;
      else  // 0x <> 0 - no roots
        return Result::kSolvedNoRoots;
    else {  // bx + c = 0, b <> 0, c <> 0
      *x1 = -c / b;
      if (std::isinf(*x1))
        return Result::kCantSolve;
      return Result::kSolvedOneRoot;
    }
  else {  // ax2 + bx + c = 0, a <> 0
    double D = b*b - 4*a*c;
    if (std::isinf(D))
      return Result::kCantSolve;
    if (D < 0)
      return Result::kSolvedNoRoots;
    else if (Equal(D, 0)) {
      *x1 = -b/2/a;
      if (std::isinf(*x1))
        return Result::kCantSolve;
      return Result::kSolvedOneRoot;
    }
    else {
      double sqrtD = sqrt(D);
      *x1 = (-b-sqrtD)/2/a;
      *x2 = (-b+sqrtD)/2/a;
      if (std::isinf(*x1))
        return Result::kCantSolve;
      if (std::isinf(*x2))
        return Result::kCantSolve;
      if (Equal(*x1, *x2))  // check if roots are equal
        return Result::kSolvedOneRoot;
      else
        return Result::kSolvedTwoRoots;
    }
  }
}
