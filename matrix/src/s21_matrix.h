#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_EPS 1e-07
#define SUCCESS 1
#define FAILURE 0
#define OK 0
#define INCORRECT 1
#define CALCULATION_ERROR 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
void s21_minor(int row, int column, matrix_t *A, matrix_t *result);
double matrix_of_minor(matrix_t *A);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
int valide_matrix(matrix_t *A);
int twins(matrix_t *A, matrix_t *B);
void s21_minor_det(matrix_t *A, int index_row, int index_column,
                   matrix_t *result);

#endif  // SRC_S21_MATRIX_H_
