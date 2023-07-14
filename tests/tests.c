#include "tests.h"

int main() {
  int failed = 0;
  SRunner *sr = srunner_create(test_smart_calc());
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);
  printf("Failed %d", failed);
  return 0;
}

START_TEST(binary_calculation_test) {
  double result = 0;
  int status = smart_calc(test_binary_calculation[_i], 0, &result);
  ck_assert_double_eq_tol(result, binary_calculation_result[_i], 1e-5);
  ck_assert_int_eq(status, OK);
}
END_TEST

START_TEST(function_calculation_test) {
  double result = 0;
  int status = smart_calc(test_function_calculation[_i], 0, &result);
  ck_assert_double_eq_tol(result, function_calculation_result[_i], 1e-5);
  ck_assert_int_eq(status, OK);
}

START_TEST(incorrect_expression_test) {
  double result = 0;
  int status = smart_calc(test_incorrect_expression[_i], 0, &result);
  ck_assert_int_eq(status, INCORRECT_EXPRESSION);
}

START_TEST(calculation_error_test) {
  double result = 0;
  int status = smart_calc(test_calculation_error[_i], 0, &result);
  ck_assert_double_nan(result);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}

START_TEST(division_by_zero_test) {
  double result = 0;
  char test[][100] = {"12/0", "12%0"};
  int status = smart_calc(test[0], 0, &result);
  ck_assert_int_eq(status, DIVISION_BY_ZERO);
  status = smart_calc(test[1], 0, &result);
  ck_assert_int_eq(status, DIVISION_BY_ZERO);
}

Suite *test_smart_calc() {
  Suite *s = suite_create("\033[42m-=SMART_CALC_TESTS=-\033[0m");
  TCase *tc = tcase_create("SMART_CALC_TESTS");
  suite_add_tcase(s, tc);
  tcase_add_loop_test(tc, binary_calculation_test, 0, 10);
  tcase_add_loop_test(tc, function_calculation_test, 0, 10);
  tcase_add_loop_test(tc, incorrect_expression_test, 0, 10);
  tcase_add_loop_test(tc, calculation_error_test, 0, 10);
  tcase_add_test(tc, division_by_zero_test);
  return s;
}