#include <cstdio>
#include <cmath>

enum class Result;
enum class CheckResult;

/**
 * \brief Checks if a and b are equal.
 *
 * a and b are equal iff a = b or
 * relative difference is less then kEps
 *
 * @param[in] a - first value
 * @param[in] b - second value
 *
 * @return 1 - if a and b are equal, 0 - otherwise.
 */

int Equal(double a, double b);

/**
 * \brief Solves equation ax2+bx+c=0
 *
 * @param[in] a - a coefficient
 * @param[in] b - b coefficient
 * @param[in] c - c coefficient
 * @param[out] x1 - first root (specified when equation has 1 or 2 roots)
 * @param[out] x2 - second root (specified when equation has 2 roots)
 *
 * @return member of enum Result:\n
 * kSolvedNoRoots - solved, no roots was found\n
 * kSolvedOneRoot - solved, one root was found\n
 * kSolvedTwoRoots - solved, two roots were found\n
 * kSolvedAnyNumber - solved, any number is root\n
 * kCantSolve - can`t solve, overflow while calculating ans\n
 * kErrorAInfinite - error, a coefficient is infinite\n
 * kErrorBInfinite - error, b coefficient is infinite\n
 * kErrorCInfinite - error, c coefficient is infinite\n
 * kErrorNullptrX1 - error, nullptr is given for x1 output\n
 * kErrorNullptrX2 - error, nullptr is given for x2 output\n
 * kErrorEqualPtr - error, same pointers were given for x1 and x2
 */

Result SolveSqrEquation(double a, double b, double c, double* x1, double* x2);

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

//////////////////////////// End of definition section ///////////////////////////

const double kEps = ldexp(1, -20);

enum class Result {
    kSolvedNoRoots,
    kSolvedOneRoot,
    kSolvedTwoRoots,
    kSolvedAnyNumber,
    kCantSolve,
    kErrorAInfinite,
    kErrorBInfinite,
    kErrorCInfinite,
    kErrorNullptrX1,
    kErrorNullptrX2,
    kErrorEqualPtr
};

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

enum class CheckResult {
    kOk,
    kWrongResult,
    kWrongRoots
};

const char* kCheckResultDescription[] {
        "Ok, result and roots are equal to ground truth",
        "Error, result differs from ground truth",
        "Error, roots differ from ground truth"
};

int Equal(double a, double b) {
    if (a > b) {
        double tmp = a;
        a = b;
        b = tmp;
    }

    int b_exp;
    frexp(b, &b_exp);
    b = ldexp(b, 1-b_exp);
    a = ldexp(a, 1-b_exp);
    return ((a < kEps && -a < kEps) == (b < kEps && -b < kEps)) && (b - a < kEps) && (a - b < kEps);
}

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

int main() {
    SolveSqrEquationTest();
    printf("Your test\n");
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
    }
    return 0;
}
