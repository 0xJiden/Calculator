#include <unity.h>
#include "calc_logic.h"

/* Required by calc_logic.h */
CalcState calc;

/* ── Runs before each test ─────────────────────────── */
void setUp(void) {
    memset(&calc, 0, sizeof(CalcState));
}

/* ── Runs after each test ──────────────────────────── */
void tearDown(void) {}

/* ════════════════════════════════════════════════════
 *  Calc_Evaluate Tests
 * ════════════════════════════════════════════════════ */
void test_addition(void) {
    TEST_ASSERT_EQUAL_FLOAT(7.0,  Calc_Evaluate(3.0, 4.0,  '+'));
    TEST_ASSERT_EQUAL_FLOAT(0.0,  Calc_Evaluate(-5.0, 5.0, '+'));
    TEST_ASSERT_EQUAL_FLOAT(-3.0, Calc_Evaluate(-1.0, -2.0,'+'));
}

void test_subtraction(void) {
    TEST_ASSERT_EQUAL_FLOAT(1.0,  Calc_Evaluate(5.0, 4.0,  '-'));
    TEST_ASSERT_EQUAL_FLOAT(-9.0, Calc_Evaluate(-4.0, 5.0, '-'));
}

void test_multiplication(void) {
    TEST_ASSERT_EQUAL_FLOAT(12.0, Calc_Evaluate(3.0, 4.0,  '*'));
    TEST_ASSERT_EQUAL_FLOAT(-6.0, Calc_Evaluate(-2.0, 3.0, '*'));
    TEST_ASSERT_EQUAL_FLOAT(0.0,  Calc_Evaluate(0.0, 99.0, '*'));
}

void test_division(void) {
    TEST_ASSERT_EQUAL_FLOAT(2.5,  Calc_Evaluate(5.0, 2.0,  '/'));
    TEST_ASSERT_EQUAL_FLOAT(-2.0, Calc_Evaluate(-6.0, 3.0, '/'));
}

void test_division_by_zero(void) {
    Calc_Evaluate(5.0, 0.0, '/');
    TEST_ASSERT_TRUE(calc.errorState);
}

/* ════════════════════════════════════════════════════
 *  Calc_FormatNumber Tests
 * ════════════════════════════════════════════════════ */
void test_format_integer(void) {
    char buf[17];
    Calc_FormatNumber(42.0, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("42", buf);
}

void test_format_negative(void) {
    char buf[17];
    Calc_FormatNumber(-7.0, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("-7", buf);
}

void test_format_decimal(void) {
    char buf[17];
    Calc_FormatNumber(3.14, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("3.14", buf);
}

void test_format_overflow(void) {
    char buf[17];
    Calc_FormatNumber(9999999999999.0, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("OVERFLOW", buf);
}

void test_format_trailing_zeros_stripped(void) {
    char buf[17];
    Calc_FormatNumber(1.5, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("1.5", buf);  // not "1.500000"
}

/* ════════════════════════════════════════════════════
 *  Main — runs all tests
 * ════════════════════════════════════════════════════ */
int main(void) {
    UNITY_BEGIN();

    /* Calc_Evaluate */
    RUN_TEST(test_addition);
    RUN_TEST(test_subtraction);
    RUN_TEST(test_multiplication);
    RUN_TEST(test_division);
    RUN_TEST(test_division_by_zero);

    /* Calc_FormatNumber */
    RUN_TEST(test_format_integer);
    RUN_TEST(test_format_negative);
    RUN_TEST(test_format_decimal);
    RUN_TEST(test_format_overflow);
    RUN_TEST(test_format_trailing_zeros_stripped);

    return UNITY_END();
}