//
// Created by vsvood on 9/21/21.
//

#include "utils.h"

#include <cmath>

const double kEps = ldexp(1, -20);

bool Equal(double a, double b) {
  if (a > b) {
    double tmp = a;
    a = b;
    b = tmp;
  }

  int b_exp = 0;
  frexp(b, &b_exp);
  b = ldexp(b, 1-b_exp);
  a = ldexp(a, 1-b_exp);
  return ((a < kEps && -a < kEps) == (b < kEps && -b < kEps)) && (b - a < kEps) && (a - b < kEps);
}
