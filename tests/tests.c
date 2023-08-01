#include "tests.h"

int main() {
  int failed = 0;
  Suite *calc_tests[] = {test_smart_calc(), test_credit_calculator(),
                         test_deposit_calculator(), NULL};
  for (int i = 0; calc_tests[i]; i++) {
    SRunner *sr = srunner_create(calc_tests[i]);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
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
END_TEST

START_TEST(incorrect_expression_test) {
  double result = 0;
  int status = smart_calc(test_incorrect_expression[_i], 0, &result);
  ck_assert_int_eq(status, INCORRECT_EXPRESSION);
}
END_TEST

START_TEST(calculation_error_test) {
  double result = 0;
  int status = smart_calc(test_calculation_error[_i], 0, &result);
  ck_assert_double_nan(result);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(division_by_zero_test) {
  double result = 0;
  char test[][100] = {"12/0", "12%0"};
  int status = smart_calc(test[0], 0, &result);
  ck_assert_int_eq(status, DIVISION_BY_ZERO);
  status = smart_calc(test[1], 0, &result);
  ck_assert_int_eq(status, DIVISION_BY_ZERO);
}
END_TEST

START_TEST(credit_annuity) {
  CreditValue data = {1000, 10.0 / 12 / 100, 3, 0};
  char *expected =
      "Monthly payment: 338.90\nOverpayment on Credit: 16.71\nTotal payment: "
      "1016.71\n";
  char *result = calculate_credit(data);
  ck_assert_str_eq(expected, result);
  if (result) free(result);
}
END_TEST

START_TEST(credit_differentiated) {
  CreditValue data = {1000.0, 10.0 / 12 / 100, 3, 1};
  char *expected =
      "Monthly payments:\n1) 341.67\n2) 338.89\n3) 336.11\nOverpayment on "
      "Credit: 16.67\nTotal payment: 1016.67\n";
  char *result = calculate_credit(data);
  ck_assert_str_eq(result, expected);
  if (result) free(result);
}
END_TEST

START_TEST(deposit_not_capitalized) {
  DepositValue data = {{0}, {0}, 75000, 5, 13, 24, 0, 0};
  double interest = 0, taxes = 0;
  calculate_deposit(&data, &interest, &taxes);
  ck_assert_double_eq_tol(data.deposit_amount, 81525.00, 1e-07);
  ck_assert_double_eq_tol(interest, 7500.00, 1e-07);
  ck_assert_double_eq_tol(taxes, 975.00, 1e-07);
}
END_TEST

START_TEST(deposit_capitalized_monthly) {
  DepositValue data = {{0}, {0}, 75000, 5, 13, 24, 1, 0};
  double interest = 0, taxes = 0;
  calculate_deposit(&data, &interest, &taxes);
  ck_assert_double_eq_tol(data.deposit_amount, 81847.4, 1e-07);
  ck_assert_double_eq_tol(interest, 7870.6, 1e-07);
  ck_assert_double_eq_tol(taxes, 1023.1, 1e-07);
}
END_TEST

START_TEST(deposit_capitalized_quaterly) {
  DepositValue data = {{0}, {0}, 75000, 5, 13, 24, 1, 1};
  double interest = 0, taxes = 0;
  calculate_deposit(&data, &interest, &taxes);
  ck_assert_double_eq_tol(data.deposit_amount, 81806.68, 1e-07);
  ck_assert_double_eq_tol(interest, 7823.77, 1e-07);
  ck_assert_double_eq_tol(taxes, 1017.09, 1e-07);
}
END_TEST

START_TEST(deposit_capitalized_half_yearly) {
  DepositValue data = {{0}, {0}, 75000, 5, 13, 24, 1, 2};
  double interest = 0, taxes = 0;
  calculate_deposit(&data, &interest, &taxes);
  ck_assert_double_eq_tol(data.deposit_amount, 81779.89, 1e-07);
  ck_assert_double_eq_tol(interest, 7792.98, 1e-07);
  ck_assert_double_eq_tol(taxes, 1013.09, 1e-07);
}
END_TEST

START_TEST(deposit_capitalized_yearly) {
  DepositValue data = {{0}, {0}, 75000, 5, 13, 24, 1, 3};
  double interest = 0, taxes = 0;
  calculate_deposit(&data, &interest, &taxes);
  ck_assert_double_eq_tol(data.deposit_amount, 81701.21, 1e-07);
  ck_assert_double_eq_tol(interest, 7702.54, 1e-07);
  ck_assert_double_eq_tol(taxes, 1001.33, 1e-07);
}
END_TEST

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

Suite *test_credit_calculator() {
  Suite *s = suite_create("\033[42m-=CREDIT_CALCULATOR_TESTS=-\033[0m");
  TCase *tc = tcase_create("CREDIT_CALCULATOR_TESTS");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, credit_annuity);
  tcase_add_test(tc, credit_differentiated);
  return s;
}

Suite *test_deposit_calculator() {
  Suite *s = suite_create("\033[42m-=DEPOSIT_CALCULATOR_TESTS=-\033[0m");
  TCase *tc = tcase_create("DEPOSIT_CALCULATOR_TESTS");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, deposit_not_capitalized);
  tcase_add_test(tc, deposit_capitalized_monthly);
  tcase_add_test(tc, deposit_capitalized_quaterly);
  tcase_add_test(tc, deposit_capitalized_half_yearly);
  tcase_add_test(tc, deposit_capitalized_yearly);
  return s;
}