#include <cstdio>
#include <cmath>

#include "equation_solver_test.h"

int main() {
    CheckStatus check_status = SolveSqrEquationTest();
    if (check_status != CheckStatus::kOk) {
      printf("Tests failed\n");
      return 1;
    }

    printf("Your test\n");

    double a = NAN;
    double b = NAN;
    double c = NAN;
    printf("Enter a, b, c coefficients (ax2+bx+c=0)\n");
    int n_params = scanf("%lf %lf %lf", &a, &b, &c);

    if (n_params != 3) {
      printf("%d values on input, 3 expected\n", n_params);
      return 2;
    }

    NRoots n_roots = NRoots::kNoRoots;
    double x1 = NAN;
    double x2 = NAN;
    CustomStatus status = SolveSqrEquation(a, b, c, &n_roots, &x1, &x2);

    if (status == CustomStatus::kOk) {
      printf("Solved:\n");

      switch (n_roots) {
        case NRoots::kNoRoots:
          printf("No roots\n");
          break;
        case NRoots::kOneRoot:
          printf("One root\nx1 = %E", x1);
          break;
        case NRoots::kTwoRoots:
          printf("Two roots\nx1 = %E\nx2= %E", x1, x2);
          break;
        case NRoots::kAnyNumber:
          printf("Any number is root\n");
          break;
        default:
          printf("Error: number of roots is uncommon (%d)", (int)n_roots);
          break;
      }
    } else {
      printf("Error: '%s'\n", kCustomStatusDescription[(int)status]);
    }
    return 0;
}
