#include <check.h>

#include "s21_matrix.h"

void s21_matrix_creator(matrix_t *A, double increase) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++, increase++) {
      A->matrix[i][j] = increase;
    }
  }
}

START_TEST(s21_eq_matrix_test) {
  matrix_t test1;
  matrix_t test2;
  s21_create_matrix(5, 5, &test1);
  s21_create_matrix(5, 5, &test2);
  s21_matrix_creator(&test1, 1.0);
  s21_matrix_creator(&test2, 1.0);
  ck_assert_int_eq(s21_eq_matrix(&test1, &test2), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(s21_eq_matrix_test_2) {
  matrix_t test1;
  matrix_t test2;
  s21_create_matrix(5, 5, &test1);
  s21_create_matrix(1, 5, &test2);
  s21_matrix_creator(&test1, 1.0);
  s21_matrix_creator(&test2, 1.0);
  ck_assert_int_eq(s21_eq_matrix(&test1, &test2), FAILURE);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(s21_eq_matrix_test_3) {
  matrix_t test1;
  matrix_t test2;
  s21_create_matrix(5, 5, &test1);
  s21_create_matrix(5, 5, &test2);
  s21_matrix_creator(&test1, 1.0);
  s21_matrix_creator(&test2, 2.0);
  ck_assert_int_eq(s21_eq_matrix(&test1, &test2), FAILURE);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(s21_sum_matrix_test) {
  matrix_t test1;
  matrix_t test2;
  matrix_t result_by_func;
  s21_create_matrix(2, 2, &test1);
  s21_create_matrix(2, 2, &test2);
  s21_matrix_creator(&test1, 1.0);
  s21_matrix_creator(&test2, 1.0);
  s21_sum_matrix(&test1, &test2, &result_by_func);
  matrix_t result_by_hands;
  s21_create_matrix(2, 2, &result_by_hands);
  result_by_hands.matrix[0][0] = 2.;
  result_by_hands.matrix[0][1] = 4.;
  result_by_hands.matrix[1][0] = 6.;
  result_by_hands.matrix[1][1] = 8.;
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result_by_func);
  s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(s21_sum_matrix_test_2) {
  int correct_error_1 = FAILURE;
  int fun_error_1 = FAILURE;
  int rows1 = 3;
  int columns1 = 2;

  matrix_t A1 = {NULL, 0, 0};
  matrix_t B1 = {NULL, 0, 0};
  matrix_t res = {NULL, 0, 0};

  s21_create_matrix(rows1, columns1, &A1);
  s21_create_matrix(rows1, columns1, &B1);

  A1.matrix[0][0] = 13.0;
  A1.matrix[0][1] = 13.0;
  A1.matrix[1][0] = 13.0;
  A1.matrix[1][1] = 13.0;
  A1.matrix[2][0] = 13.0;
  A1.matrix[2][1] = 13.0;

  B1.matrix[0][0] = 13.0;
  B1.matrix[0][1] = 13.0;
  B1.matrix[1][0] = 13.0;
  B1.matrix[1][1] = 13.0;
  B1.matrix[2][0] = 13.0;
  B1.matrix[2][1] = 13.0;

  fun_error_1 = s21_sum_matrix(&A1, &B1, &res);

  ck_assert_double_eq_tol(res.matrix[0][0], 26.0, s21_EPS);
  ck_assert_double_eq_tol(res.matrix[0][1], 26.0, s21_EPS);
  ck_assert_double_eq_tol(res.matrix[1][0], 26.0, s21_EPS);
  ck_assert_double_eq_tol(res.matrix[1][1], 26.0, s21_EPS);
  ck_assert_double_eq_tol(res.matrix[2][0], 26.0, s21_EPS);
  ck_assert_double_eq_tol(res.matrix[2][1], 26.0, s21_EPS);

  ck_assert_int_eq(correct_error_1, fun_error_1);

  s21_remove_matrix(&A1);
  s21_remove_matrix(&B1);
  s21_remove_matrix(&res);

  int correct_error_2 = CALCULATION_ERROR;
  int fun_error_2 = FAILURE;

  matrix_t A2 = {NULL, 0, 0};
  matrix_t B2 = {NULL, 0, 0};
  matrix_t res2 = {NULL, 0, 0};

  s21_create_matrix(2, 2, &A2);
  s21_create_matrix(3, 3, &B2);

  A2.matrix[0][0] = 13.0;
  A2.matrix[0][1] = 13.0;
  A2.matrix[1][0] = 13.0;
  A2.matrix[1][1] = 13.0;

  B2.matrix[0][0] = 13.0;
  B2.matrix[0][1] = 13.0;
  B2.matrix[0][2] = 13.0;
  B2.matrix[1][0] = 13.0;
  B2.matrix[1][1] = 13.0;
  B2.matrix[1][2] = 13.0;
  B2.matrix[2][0] = 13.0;
  B2.matrix[2][1] = 13.0;
  B2.matrix[2][2] = 13.0;

  fun_error_2 = s21_sum_matrix(&A2, &B2, &res2);

  ck_assert_int_eq(correct_error_2, fun_error_2);

  s21_remove_matrix(&A2);
  s21_remove_matrix(&B2);
  s21_remove_matrix(&res2);
}
END_TEST

START_TEST(s21_sub_matrix_test) {
  matrix_t test1;
  matrix_t test2;
  matrix_t result_by_func;
  s21_create_matrix(2, 2, &test1);
  s21_create_matrix(2, 2, &test2);
  s21_matrix_creator(&test1, 1.0);
  s21_matrix_creator(&test2, 1.0);
  s21_sub_matrix(&test1, &test2, &result_by_func);
  matrix_t result_by_hands;
  s21_create_matrix(2, 2, &result_by_hands);
  result_by_hands.matrix[0][0] = 0.;
  result_by_hands.matrix[0][1] = 0.;
  result_by_hands.matrix[1][0] = 0.;
  result_by_hands.matrix[1][1] = 0.;
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result_by_func);
  s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(s21_mult_number_test) {
  matrix_t test1;
  matrix_t result_by_func;
  s21_create_matrix(3, 3, &test1);
  s21_matrix_creator(&test1, 1.0);
  double number = 2;
  s21_mult_number(&test1, number, &result_by_func);
  matrix_t result_by_hands;
  s21_create_matrix(3, 3, &result_by_hands);
  result_by_hands.matrix[0][0] = 2.;
  result_by_hands.matrix[0][1] = 4.;
  result_by_hands.matrix[0][2] = 6.;
  result_by_hands.matrix[1][0] = 8.;
  result_by_hands.matrix[1][1] = 10.;
  result_by_hands.matrix[1][2] = 12.;
  result_by_hands.matrix[2][0] = 14.;
  result_by_hands.matrix[2][1] = 16.;
  result_by_hands.matrix[2][2] = 18.;
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result_by_func);
  s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(s21_mult_matrix_test) {
  matrix_t test1;
  matrix_t test2;
  matrix_t result_by_func;
  s21_create_matrix(3, 3, &test1);
  s21_create_matrix(3, 3, &test2);
  s21_matrix_creator(&test1, 1.0);
  s21_matrix_creator(&test2, 2.0);
  s21_mult_matrix(&test1, &test2, &result_by_func);
  matrix_t result_by_hands;
  s21_create_matrix(3, 3, &result_by_hands);
  result_by_hands.matrix[0][0] = 36.;
  result_by_hands.matrix[0][1] = 42.;
  result_by_hands.matrix[0][2] = 48.;
  result_by_hands.matrix[1][0] = 81.;
  result_by_hands.matrix[1][1] = 96.;
  result_by_hands.matrix[1][2] = 111.;
  result_by_hands.matrix[2][0] = 126.;
  result_by_hands.matrix[2][1] = 150.;
  result_by_hands.matrix[2][2] = 174.;
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result_by_func);
  s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(s21_mult_matrix_test_2) {
  int correct_error_1 = FAILURE;
  int fun_error_1 = FAILURE;

  matrix_t A1 = {NULL, 0, 0};
  matrix_t B1 = {NULL, 0, 0};
  matrix_t res = {NULL, 0, 0};

  s21_create_matrix(3, 2, &A1);
  s21_create_matrix(2, 3, &B1);

  A1.matrix[0][0] = 1.0;
  A1.matrix[0][1] = 2.0;
  A1.matrix[1][0] = 3.0;
  A1.matrix[1][1] = 4.0;
  A1.matrix[2][0] = 5.0;
  A1.matrix[2][1] = 6.0;

  B1.matrix[0][0] = 13.0;
  B1.matrix[0][1] = 13.0;
  B1.matrix[0][2] = 13.0;
  B1.matrix[1][0] = 13.0;
  B1.matrix[1][1] = 13.0;
  B1.matrix[1][2] = 13.0;

  fun_error_1 = s21_mult_matrix(&A1, &B1, &res);

  ck_assert_double_eq_tol(res.matrix[0][0], 39.0, s21_EPS);
  ck_assert_double_eq_tol(res.matrix[0][1], 39.0, s21_EPS);
  ck_assert_double_eq_tol(res.matrix[0][2], 39.0, s21_EPS);
  ck_assert_double_eq_tol(res.matrix[1][0], 91.0, s21_EPS);
  ck_assert_double_eq_tol(res.matrix[1][1], 91.0, s21_EPS);
  ck_assert_double_eq_tol(res.matrix[1][2], 91.0, s21_EPS);
  ck_assert_double_eq_tol(res.matrix[2][0], 143.0, s21_EPS);
  ck_assert_double_eq_tol(res.matrix[2][1], 143.0, s21_EPS);
  ck_assert_double_eq_tol(res.matrix[2][2], 143.0, s21_EPS);
  ck_assert_int_eq(correct_error_1, fun_error_1);

  s21_remove_matrix(&A1);
  s21_remove_matrix(&B1);
  s21_remove_matrix(&res);

  int correct_error_2 = CALCULATION_ERROR;
  int fun_error_2 = FAILURE;

  matrix_t A2 = {NULL, 0, 0};
  matrix_t B2 = {NULL, 0, 0};
  matrix_t res2 = {NULL, 0, 0};

  s21_create_matrix(2, 2, &A2);
  s21_create_matrix(3, 3, &B2);

  A2.matrix[0][0] = 13.0;
  A2.matrix[0][1] = 13.0;
  A2.matrix[1][0] = 13.0;
  A2.matrix[1][1] = 13.0;

  B2.matrix[0][0] = 13.0;
  B2.matrix[0][1] = 13.0;
  B2.matrix[0][2] = 13.0;
  B2.matrix[1][0] = 13.0;
  B2.matrix[1][1] = 13.0;
  B2.matrix[1][2] = 13.0;
  B2.matrix[2][0] = 13.0;
  B2.matrix[2][1] = 13.0;
  B2.matrix[2][2] = 13.0;

  fun_error_2 = s21_mult_matrix(&A2, &B2, &res2);

  ck_assert_int_eq(correct_error_2, fun_error_2);

  s21_remove_matrix(&A2);
  s21_remove_matrix(&B2);
  s21_remove_matrix(&res2);
}
END_TEST

START_TEST(s21_transpose_test) {
  matrix_t test1;
  matrix_t result_by_func;
  s21_create_matrix(3, 3, &test1);
  s21_matrix_creator(&test1, 1.0);
  s21_transpose(&test1, &result_by_func);
  matrix_t result_by_hands;
  s21_create_matrix(3, 3, &result_by_hands);
  result_by_hands.matrix[0][0] = 1.;
  result_by_hands.matrix[0][1] = 4.;
  result_by_hands.matrix[0][2] = 7.;
  result_by_hands.matrix[1][0] = 2.;
  result_by_hands.matrix[1][1] = 5.;
  result_by_hands.matrix[1][2] = 8.;
  result_by_hands.matrix[2][0] = 3.;
  result_by_hands.matrix[2][1] = 6.;
  result_by_hands.matrix[2][2] = 9.;
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result_by_func);
  s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(s21_transpose_test_2) {
  matrix_t test1;
  matrix_t result_by_func;
  s21_create_matrix(3, 2, &test1);
  s21_matrix_creator(&test1, 1.0);
  s21_transpose(&test1, &result_by_func);
  matrix_t result_by_hands;
  s21_create_matrix(2, 3, &result_by_hands);
  result_by_hands.matrix[0][0] = 1;
  result_by_hands.matrix[0][1] = 3;
  result_by_hands.matrix[0][2] = 5;
  result_by_hands.matrix[1][0] = 2;
  result_by_hands.matrix[1][1] = 4;
  result_by_hands.matrix[1][2] = 6;
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result_by_func);
  s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(s21_calc_complements_test) {
  matrix_t test, result_by_hands, result_by_func;
  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[1][0] = 0;
  test.matrix[1][1] = 4;
  test.matrix[1][2] = 2;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = 2;
  test.matrix[2][2] = 1;
  s21_calc_complements(&test, &result_by_func);
  s21_create_matrix(3, 3, &result_by_hands);
  result_by_hands.matrix[0][0] = 0;
  result_by_hands.matrix[0][1] = 10;
  result_by_hands.matrix[0][2] = -20;
  result_by_hands.matrix[1][0] = 4;
  result_by_hands.matrix[1][1] = -14;
  result_by_hands.matrix[1][2] = 8;
  result_by_hands.matrix[2][0] = -8;
  result_by_hands.matrix[2][1] = -2;
  result_by_hands.matrix[2][2] = 4;
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result_by_hands);
  s21_remove_matrix(&result_by_func);
}
END_TEST

START_TEST(s21_calc_complements_test_2) {
  matrix_t test, result;
  s21_create_matrix(3, 3, &test);
  s21_matrix_creator(&test, 10);
  int result_status = s21_calc_complements(&test, &result);
  ck_assert_int_eq(result_status, 0);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_determinant_test) {
  int correct_error_1 = FAILURE;
  int fun_error_1 = FAILURE;
  matrix_t A1 = {NULL, 0, 0};
  double res = 0.0;

  s21_create_matrix(1, 1, &A1);

  A1.matrix[0][0] = 13.0;

  fun_error_1 = s21_determinant(&A1, &res);

  ck_assert_double_eq_tol(res, 13.0, s21_EPS);
  ck_assert_int_eq(correct_error_1, fun_error_1);

  s21_remove_matrix(&A1);

  int correct_error_2 = FAILURE;
  int fun_error_2 = FAILURE;
  matrix_t A2 = {NULL, 0, 0};
  double res2 = 0.0;

  s21_create_matrix(2, 2, &A2);

  A2.matrix[0][0] = 13.0;
  A2.matrix[0][1] = 2.0;
  A2.matrix[1][0] = 7.0;
  A2.matrix[1][1] = 1.0;

  fun_error_2 = s21_determinant(&A2, &res2);

  ck_assert_double_eq_tol(res2, -1, s21_EPS);
  ck_assert_int_eq(correct_error_2, fun_error_2);

  s21_remove_matrix(&A2);

  int correct_error_3 = FAILURE;
  int fun_error_3 = FAILURE;
  matrix_t A3 = {NULL, 0, 0};
  double res3 = 0.0;

  s21_create_matrix(3, 3, &A3);

  A3.matrix[0][0] = 1.0;
  A3.matrix[0][1] = 2.0;
  A3.matrix[0][2] = 3.0;
  A3.matrix[1][0] = 4.0;
  A3.matrix[1][1] = 5.0;
  A3.matrix[1][2] = 6.0;
  A3.matrix[2][0] = 7.0;
  A3.matrix[2][1] = 8.0;
  A3.matrix[2][2] = 9.0;

  fun_error_3 = s21_determinant(&A3, &res3);

  ck_assert_double_eq_tol(res3, 0.0, s21_EPS);
  ck_assert_int_eq(correct_error_3, fun_error_3);

  s21_remove_matrix(&A3);

  int correct_error_5 = CALCULATION_ERROR;
  int fun_error_5 = FAILURE;
  matrix_t A4 = {NULL, 0, 0};
  double res4 = 0.0;

  s21_create_matrix(1, 2, &A4);

  A4.matrix[0][0] = 13.0;
  A4.matrix[0][1] = 13.0;

  fun_error_5 = s21_determinant(&A4, &res4);

  ck_assert_int_eq(correct_error_5, fun_error_5);

  s21_remove_matrix(&A4);
}
END_TEST

START_TEST(s21_inverse_matrix_test) {
  matrix_t test, result_by_hands, result_by_func;
  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 2;
  test.matrix[0][1] = 4;
  test.matrix[0][2] = 10;
  test.matrix[1][0] = 10;
  test.matrix[1][1] = 8;
  test.matrix[1][2] = 6;
  test.matrix[2][0] = 10;
  test.matrix[2][1] = 6;
  test.matrix[2][2] = 12;
  s21_create_matrix(3, 3, &result_by_hands);
  result_by_hands.matrix[0][0] = -0.1875;
  result_by_hands.matrix[0][1] = -0.0375;
  result_by_hands.matrix[0][2] = 0.175;
  result_by_hands.matrix[1][0] = 0.1875;
  result_by_hands.matrix[1][1] = 0.2375;
  result_by_hands.matrix[1][2] = -0.275;
  result_by_hands.matrix[2][0] = 0.0625;
  result_by_hands.matrix[2][1] = -0.0875;
  result_by_hands.matrix[2][2] = 0.075;
  s21_inverse_matrix(&test, &result_by_func);
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result_by_hands);
  s21_remove_matrix(&result_by_func);
}
END_TEST

START_TEST(s21_inverse_matrix_test_2) {
  matrix_t test, result_by_hands, result_by_func;
  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 2;
  test.matrix[0][1] = 5;
  test.matrix[0][2] = 7;
  test.matrix[1][0] = 6;
  test.matrix[1][1] = 3;
  test.matrix[1][2] = 4;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = -2;
  test.matrix[2][2] = -3;
  s21_create_matrix(3, 3, &result_by_hands);
  result_by_hands.matrix[0][0] = 1.0;
  result_by_hands.matrix[0][1] = -1.0;
  result_by_hands.matrix[0][2] = 1.0;
  result_by_hands.matrix[1][0] = -38.0;
  result_by_hands.matrix[1][1] = 41.0;
  result_by_hands.matrix[1][2] = -34.0;
  result_by_hands.matrix[2][0] = 27.0;
  result_by_hands.matrix[2][1] = -29.0;
  result_by_hands.matrix[2][2] = 24.0;
  s21_inverse_matrix(&test, &result_by_func);
  ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result_by_hands);
  s21_remove_matrix(&result_by_func);
}
END_TEST

int main() {
  Suite *suite = suite_create("S21_TESTS");
  SRunner *srunner = srunner_create(suite);

  TCase *s21_eq_matrix_case = tcase_create("s21_eq_matrix_case");
  suite_add_tcase(suite, s21_eq_matrix_case);
  tcase_add_test(s21_eq_matrix_case, s21_eq_matrix_test);

  TCase *s21_eq_matrix_2_case = tcase_create("s21_eq_matrix_2_case");
  suite_add_tcase(suite, s21_eq_matrix_2_case);
  tcase_add_test(s21_eq_matrix_2_case, s21_eq_matrix_test_2);

  TCase *s21_eq_matrix_3_case = tcase_create("s21_eq_matrix_3_case");
  suite_add_tcase(suite, s21_eq_matrix_3_case);
  tcase_add_test(s21_eq_matrix_3_case, s21_eq_matrix_test_3);

  TCase *s21_sum_matrix_test_case = tcase_create("s21_sum_matrix_test_case");
  suite_add_tcase(suite, s21_sum_matrix_test_case);
  tcase_add_test(s21_sum_matrix_test_case, s21_sum_matrix_test);

  TCase *s21_sum_matrix_test_2_case =
      tcase_create("s21_sum_matrix_test_2_case");
  suite_add_tcase(suite, s21_sum_matrix_test_2_case);
  tcase_add_test(s21_sum_matrix_test_2_case, s21_sum_matrix_test_2);

  TCase *s21_sub_matrix_test_case = tcase_create("s21_sub_matrix_test_case");
  suite_add_tcase(suite, s21_sub_matrix_test_case);
  tcase_add_test(s21_sub_matrix_test_case, s21_sub_matrix_test);

  TCase *s21_mult_number_test_case = tcase_create("s21_mult_number_test_case");
  suite_add_tcase(suite, s21_mult_number_test_case);
  tcase_add_test(s21_mult_number_test_case, s21_mult_number_test);

  TCase *s21_mult_matrix_test_case = tcase_create("s21_mult_matrix_test_case");
  suite_add_tcase(suite, s21_mult_matrix_test_case);
  tcase_add_test(s21_mult_matrix_test_case, s21_mult_matrix_test);

  TCase *s21_mult_matrix_test_2_case =
      tcase_create("s21_mult_matrix_test_2_case");
  suite_add_tcase(suite, s21_mult_matrix_test_2_case);
  tcase_add_test(s21_mult_matrix_test_2_case, s21_mult_matrix_test_2);

  TCase *s21_transpose_case = tcase_create("s21_transpose_case");
  suite_add_tcase(suite, s21_transpose_case);
  tcase_add_test(s21_transpose_case, s21_transpose_test);

  TCase *s21_transpose_2_case = tcase_create("s21_transpose_2_case");
  suite_add_tcase(suite, s21_transpose_2_case);
  tcase_add_test(s21_transpose_2_case, s21_transpose_test_2);

  TCase *s21_calc_complements_case = tcase_create("s21_calc_complements_case");
  suite_add_tcase(suite, s21_calc_complements_case);
  tcase_add_test(s21_calc_complements_case, s21_calc_complements_test);

  TCase *s21_calc_complements_2_case =
      tcase_create("s21_calc_complements_2_case");
  suite_add_tcase(suite, s21_calc_complements_2_case);
  tcase_add_test(s21_calc_complements_2_case, s21_calc_complements_test_2);

  TCase *s21_determinant_case = tcase_create("s21_determinant_case");
  suite_add_tcase(suite, s21_determinant_case);
  tcase_add_test(s21_determinant_case, s21_determinant_test);

  TCase *s21_inverse_matrix_case = tcase_create("s21_inverse_matrix_case");
  suite_add_tcase(suite, s21_inverse_matrix_case);
  tcase_add_test(s21_inverse_matrix_case, s21_inverse_matrix_test);

  TCase *s21_inverse_matrix_2_case = tcase_create("s21_inverse_matrix_2_case");
  suite_add_tcase(suite, s21_inverse_matrix_2_case);
  tcase_add_test(s21_inverse_matrix_2_case, s21_inverse_matrix_test_2);

  srunner_run_all(srunner, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return (number_failed == 0) ? 0 : 1;
}
