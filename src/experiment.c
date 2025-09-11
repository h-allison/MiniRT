#include <stdlib.h>
#include <stdio.h>

typedef struct {
	unsigned int rows, cols;
	float matrix[];
} matrix_t;

matrix_t *alloc_matrix(unsigned int rows, unsigned int cols)
{
	matrix_t *m = malloc(sizeof(matrix_t) + sizeof(float)*rows*cols);
	m->rows = rows;
	m->cols = cols;
	for (unsigned int i = 0; i < rows * cols; i++) {
		m->matrix[i] = 0.0;
	}
	return m;
}

// `ROW_COL(matrix, row, col)` is like `matrix[row][col]`
#define ROW_COL(matrixt, row, col) (matrixt->matrix[(row * matrixt->cols) + col])

float matrixmult_helper(matrix_t *m1, matrix_t *m2, unsigned int row, unsigned int col)
{
	float res = 0.0;
	for (unsigned int i = 0; i < m1->rows; i++) {
		for (unsigned int j = 0; j < m2->cols; j++) {
			// Unfinished
	//		printf("%u %u / %u %u / [%u %u] [%u %u] / %f %f\n", i, j, row, col, i, col, row, j, ROW_COL(m1, i, col), ROW_COL(m2, row, j));
//			res += ROW_COL(m1, i, col) * ROW_COL(m2, row, j);
		}
	}
	return res;
}

matrix_t *matrixmult(matrix_t *m1, matrix_t *m2)
{
	// Check if m1->cols == m2->rows

	matrix_t *res = alloc_matrix(m1->rows, m2->cols);
	for (unsigned int i = 0; i < m1->rows; i++) {
		for (unsigned int j = 0; j < m2->cols; j++) {
			ROW_COL(res, i, j) = matrixmult_helper(m1, m2, i, j);
		}
	}
	return res;
}

matrix_t copied_matrixmult(matrix_t *m1, matrix_t *m2)
{
	int x;
	int y;
	float **m;

	m = alloc_matrix(4, 4);
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			ROW_COL(m, x, y) = ROW_COL(m1, x, 0) * ROW_COL(m2, 0, y)
				+ ROW_COL(m1, x, 1) * ROW_COL(m2, 1, y)
				+ ROW_COL(m1, x, 2) * ROW_COL(m2, 2, y)
				+ ROW_COL(m1, x, 3) * ROW_COL(m2, 3, y)
			x++;
		}
		y++;
	}
	return(m);
}


int main() {
	matrix_t *m = alloc_matrix(2, 2);
	m->matrix[0] = 1.0;
	m->matrix[1] = 2.0;
	m->matrix[2] = 3.0;
	m->matrix[3] = 4.0;
	printf("%f %f\n", m->matrix[0], m->matrix[4]);
	printf("%f %f\n", ROW_COL(m, 0, 0), ROW_COL(m, 1, 0));

	matrix_t * result = matrixmult(m, m);
	printf("%f %f\n%f %f\n", result->matrix[0], result->matrix[1], result->matrix[2], result->matrix[3]);
}
