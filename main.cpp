#include "equation_solver_test.h"

int main() {
    SolveSqrEquationTest();
    /*printf("Your test\n");
    double a, b, c;
    printf("Enter a, b, c coefficients (ax2+bx+c=0)\n");
    scanf("%lf %lf %lf", &a, &b, &c);
    double x1, x2;
    Result result = SolveSqrEquation(a, b, c, &x1, &x2);
    switch (result) {
        case Result::kSolvedNoRoots:
            printf("No roots\n");
            break;
        case Result::kSolvedOneRoot:
            printf("One root:\nx1=%.E\n", x1);
            break;
        case Result::kSolvedTwoRoots:
            printf("Two roots:\nx1=%E\nx2=%E\n", x1, x2);
            break;
        case Result::kSolvedAnyNumber:
            printf("Any number is root\n");
            break;
        case Result::kCantSolve:
        case Result::kErrorAInfinite:
        case Result::kErrorBInfinite:
        case Result::kErrorCInfinite:
        case Result::kErrorNullptrX1:
        case Result::kErrorNullptrX2:
        case Result::kErrorEqualPtr:
        default:
            printf("Error: %s\n", kResultDescription[(int)result]);
            break;
    }*/
    return 0;
}
