#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = INCORRECT;
  if (rows > 0 && columns > 0) {
    error = OK;
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++)
    if (A->columns > 0 && A->rows > 0 && A->matrix[i] != NULL)
      free(A->matrix[i]);
  if (A->columns > 0 && A->rows > 0 && A->matrix != NULL) free(A->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (valide_matrix(A) && valide_matrix(B) && twins(A, B)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >
            s21_EPS * fabs(B->matrix[i][j])) {
          result = FAILURE;
        }
      }
    }
  } else {
    result = FAILURE;
  }
  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = INCORRECT;
  if (valide_matrix(A) && valide_matrix(B)) {
    error = OK;
    if (twins(A, B)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = (A->matrix[i][j] + B->matrix[i][j]);
        }
      }
    } else {
      error = CALCULATION_ERROR;
    }
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = INCORRECT;
  if (valide_matrix(A) && valide_matrix(B)) {
    error = OK;
    if (twins(A, B)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = (A->matrix[i][j] - B->matrix[i][j]);
        }
      }
    } else {
      error = CALCULATION_ERROR;
    }
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = INCORRECT;
  if (valide_matrix(A)) {
    error = OK;
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = (A->matrix[i][j] * number);
      }
    }
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = INCORRECT;
  if (valide_matrix(A) && valide_matrix(B)) {
    error = OK;
    if (A->columns == B->rows) {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] =
                result->matrix[i][j] + A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      error = CALCULATION_ERROR;
    }
  }
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = INCORRECT;
  if (valide_matrix(A)) {
    error = OK;
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return error;
}

void s21_minor(int row, int column, matrix_t *A, matrix_t *result) {
  s21_create_matrix(A->columns - 1, A->columns - 1, result);
  int a = 0, b = 0;
  for (int m = 0; m < A->rows; m++)
    for (int n = 0; n < A->columns; n++)
      if (m != row && n != column) {
        result->matrix[a][b++] = A->matrix[m][n];
        if (b == result->columns) a++, b = 0;
      }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (valide_matrix(A) == 1) {
    if (A->rows == A->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      double det = 0.0;
      matrix_t minor = {NULL, 0, 0};
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
          s21_minor_det(A, i, j, &minor);
          s21_determinant(&minor, &det);
          result->matrix[i][j] = pow(-1, i + j) * det;
          det = 0.0;
          s21_remove_matrix(&minor);
        }
      }
    } else {
      error = CALCULATION_ERROR;
    }
  } else {
    error = INCORRECT;
  }
  return error;
}

void s21_minor_det(matrix_t *A, int index_row, int index_column,
                   matrix_t *result) {
  int res_i = 0;
  for (int i = 0; i < result->rows; i++) {
    if (i == index_row) {
      res_i = 1;
    }
    int res_j = 0;
    for (int j = 0; j < result->columns; j++) {
      if (j == index_column) {
        res_j = 1;
      }
      result->matrix[i][j] = A->matrix[i + res_i][j + res_j];
    }
  }
}

double matrix_of_minor(matrix_t *M) {
  double result = 0.0;
  if (M->columns == M->rows) {
    if (M->columns == 1) {
      result = M->matrix[0][0];
    } else if (M->columns == 2) {
      result =
          M->matrix[0][0] * M->matrix[1][1] - M->matrix[0][1] * M->matrix[1][0];
    } else {
      for (int j = 0; j < M->columns; ++j) {
        matrix_t matrix_tmp = {NULL, 0, 0};
        s21_minor(0, j, M, &matrix_tmp);
        result += M->matrix[0][j] * pow(-1, j) * matrix_of_minor(&matrix_tmp);
        s21_remove_matrix(&matrix_tmp);
      }
    }
  }
  return result;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = INCORRECT;
  if (A->matrix != NULL && A->columns >= 1 && A->rows >= 1) {
    error = OK;
    if (A->rows == A->columns) {
      if (A->rows == 1) {
        *result = A->matrix[0][0];
      } else {
        matrix_t minor = {NULL, 0, 0};
        for (int i = 0; i < A->rows; i++) {
          s21_minor(0, i, A, &minor);
          *result += A->matrix[0][i] * pow(-1, i) * matrix_of_minor(&minor);
          s21_remove_matrix(&minor);
        }
      }
    } else {
      error = CALCULATION_ERROR;
    }
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = INCORRECT;
  if (valide_matrix(A) == 1) {
    error = OK;
    if (A->rows == A->columns) {
      double det = 0.0;
      s21_determinant(A, &det);
      if (det != 0) {
        matrix_t new = {NULL, 0, 0};
        s21_calc_complements(A, &new);
        matrix_t trans = {NULL, 0, 0};
        s21_transpose(&new, &trans);
        s21_mult_number(&trans, 1 / det, result);
        s21_remove_matrix(&new);
        s21_remove_matrix(&trans);
      } else {
        error = CALCULATION_ERROR;
      }
    } else {
      error = CALCULATION_ERROR;
    }
  }
  return error;
}

int valide_matrix(matrix_t *A) {
  int flag = 0;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    flag = 1;
  }
  return flag;
}

int twins(matrix_t *A, matrix_t *B) {
  int flag = 0;
  if (A->rows == B->rows && A->columns == B->columns) {
    flag = 1;
  }
  return flag;
}
