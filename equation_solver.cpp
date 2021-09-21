//
// Created by vsvood on 9/21/21.
//

#include "equation_solver.h"

#include <cmath>

#include "utils.h"

CustomStatus SolveSqrEquation(double a, double b, double c, NRoots *n_roots, double *x1, double *x2) {
  if (std::isinf(a) || std::isinf(b) || std::isinf(c)) {
    return CustomStatus::kWrongInputParams;
  }

  if ((n_roots == nullptr) ||
      (x1 == nullptr) || (x2 == nullptr) || (x1 == x2)) {
    return CustomStatus::kWrongOutputParams;
  }

  if (Equal(a, 0)) {  // linear equation case
    return SolveLinearEquation(b, c, n_roots, x1);
  }

  // ax2 + bx + c = 0, a <> 0
  double D = b * b - 4 * a * c;
  if (std::isinf(D)) { return CustomStatus::kRuntimeError; }

  if (D < 0) {
    *n_roots = NRoots::kNoRoots;
    return CustomStatus::kOk;
  }

  if (Equal(D, 0)) {
    *x1 = -b / 2 / a;
    if (std::isinf(*x1)) { return CustomStatus::kRuntimeError; }

    *n_roots = NRoots::kOneRoot;
    return CustomStatus::kOk;
  }

  double sqrtD = sqrt(D);
  *x1 = (-b-sqrtD)/2/a;
  *x2 = (-b+sqrtD)/2/a;
  if (std::isinf(*x1) || std::isinf(*x2)) {
    return CustomStatus::kRuntimeError;
  }

  if (Equal(*x1, *x2)) {  // check if roots are equal
    *n_roots = NRoots::kOneRoot;
    return CustomStatus::kOk;
  }

  *n_roots = NRoots::kTwoRoots;
  return CustomStatus::kOk;
}

CustomStatus SolveLinearEquation(double a, double b, NRoots *n_roots, double *x1) {
  if (std::isinf(a) || std::isinf(b)) {
    return CustomStatus::kWrongInputParams;
  }

  if ((n_roots == nullptr) || (x1 == nullptr)) {
    return CustomStatus::kWrongOutputParams;
  }


  if (Equal(a, 0)) {
    if (Equal(b, 0)) {  // 0x = 0 - any number is root
      *n_roots = NRoots::kAnyNumber;
      return CustomStatus::kOk;
    }

    // 0x <> 0 - no roots
    *n_roots = NRoots::kNoRoots;
    return CustomStatus::kOk;
  }

  // ax + b = 0, a <> 0
  *x1 = -b / a;
  if (std::isinf(*x1)) { return CustomStatus::kRuntimeError; }

  *n_roots = NRoots::kOneRoot;
  return CustomStatus::kOk;
}
