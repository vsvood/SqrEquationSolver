#include <cstdio>
#include <cmath>

#include "equation_solver_test.h"

int main() {
    SolveSqrEquationTest();

    printf("Your test\n");

    double a = NAN;
    double b = NAN;
    double c = NAN;
    printf("Enter a, b, c coefficients (ax2+bx+c=0)\n");
    int n_params = scanf("%lf %lf %lf", &a, &b, &c);

    if (n_params != 3) {
      printf("%d values on input, 3 expected\n", n_params);
    }

    NRoots n_roots = NRoots::kNoRoots;
    double x1 = NAN;
    double x2 = NAN;
    CustomStatus status = SolveSqrEquation(a, b, c, &n_roots, &x1, &x2);

    if (status == CustomStatus::kOk) {
      printf("Solved:\n");

      if (n_roots == NRoots::kNoRoots) { printf("No roots\n"); }

      if (n_roots == NRoots::kAnyNumber) { printf("Any number is root\n"); }

      if (n_roots == NRoots::kOneRoot) {
        printf("One root\nx1 = %E", x1);
      }

      if (n_roots == NRoots::kTwoRoots) {
        printf("Two roots\nx1 = %E\nx2= %E", x1, x2);
      }

    } else {
      printf("Error '%s'\n", kCustomStatusDescription[(int)status]);
    }
    return 0;
}
