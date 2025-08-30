/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_matrices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:59:07 by hallison          #+#    #+#             */
/*   Updated: 2025/08/30 17:11:48 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_matrix(float **m, int size);
void	fill_matrix(float **m, int size, float steps);
static void print_tuple(char *str, t_tuple a);

int	main(void)
{
	float	**m;
	float	**m1;
	float	**m2;

	m = alloc_matrix(4);
	fill_matrix(m, 4, 0.3);
	print_matrix(m, 4);
	free_matrix(m, 4);
	printf("\n");

	m = alloc_matrix(3);
	fill_matrix(m, 3, 0.6);
	print_matrix(m, 3);
	free_matrix(m, 3);
	printf("\n");

	m = alloc_matrix(10);
	fill_matrix(m, 10, 1);
	print_matrix(m, 10);
	free_matrix(m, 10);
	printf("\n");

	/* Test Matrices Equal? */

	m1 = alloc_matrix(4);
	m2 = alloc_matrix(4);
	fill_matrix(m1, 4, 0.300001);
	fill_matrix(m2, 4, 0.3);
	printf("m1 and m2 are equal %i", misequal(m1, m2, 4));
	free_matrix(m1, 4);
	free_matrix(m2, 4);
	printf("\n");

	m1 = alloc_matrix(5);
	m2 = alloc_matrix(5);
	fill_matrix(m1, 5, 0.3);
	fill_matrix(m2, 5, 0.7);
	printf("m1 and m2 are equal %i", misequal(m1, m2, 5));
	free_matrix(m1, 5);
	free_matrix(m2, 5);
	printf("\n");
	printf("\n");

	/* Test Matrix Multiply */

	float m3[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}};
	float m4[4][4] = {{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}};

	float *m5[4];

	for (int i = 0; i < 4; i++) {
		m5[i] = m3[i];
	}

	float *m6[4];

	for (int i = 0; i < 4; i++) {
		m6[i] = m4[i];
	}
	m = matrixmult(m5, m6);
	print_matrix(m, 4);
	printf("\n");
	free_matrix(m, 4);

	/* Test Tuple Matrix Multiply */

	float m7[4][4] = {{1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}};

	float *m8[4];
	for (int i = 0; i < 4; i++) {
		m8[i] = m7[i];
	}

	t_tuple	t = point(1, 2, 3); 
	t_tuple tuple = tmatrixmult(m8, t);
	print_tuple("t", tuple);
	printf("\n");

	/* Test Identity Matrix */

	float	**id;

	id = create_id_matrix();
	t = point(1, 2, 3); 
	tuple = tmatrixmult(id , t);
	print_tuple("t", tuple);
	printf("\n");
	free_matrix(id,4);


	float	**mt;

	m1 = alloc_matrix(4);
	fill_matrix(m1, 4, 0.11111);
	mt = mtranspose(m1, 4);
	print_matrix(mt, 4);
	printf("\n");
	free_matrix(m1, 4);
	free_matrix(mt, 4);


	float	**submatrix;

	m1 = alloc_matrix(4);
	fill_matrix(m1, 4, 1);
	submatrix = msubmatrix(m1, 4, 1, 2);
	print_matrix(m1, 4);
	printf("\n");
	print_matrix(submatrix, 3);
	printf("\n");
	free_matrix(m1, 4);
	free_matrix(submatrix, 3);

	m1 = alloc_matrix(3);
	fill_matrix(m1, 3, 1);
	submatrix = msubmatrix(m1, 3, 0, 2);
	print_matrix(m1, 3);
	printf("\n");
	print_matrix(submatrix, 2);
	printf("\n");
	free_matrix(m1, 3);
	free_matrix(submatrix, 2);

	float mtemp[3][3] = {{3, 5, 0}, {2, -1, -7}, {6, -1, 5}};

	float *mminor[3];
	for (int i = 0; i < 3; i++) {
		mminor[i] = mtemp[i];
	}
	print_matrix(mminor, 3);
	printf("\n");
	printf("minor (0, 0): %f\n", mminor3x3(mminor, 0 ,0));
	printf("minor (1, 0): %f\n", mminor3x3(mminor, 1 ,0));
	printf("\n");
	printf("cofactor (0, 0): %f\n", mcofactor3x3(mminor, 0 ,0));
	printf("cofactor (1, 0): %f\n", mcofactor3x3(mminor, 1 ,0));
	printf("\n");

	float temp_det_4x4[4][4] = {{-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}};

	float *m_det_4x4[4];
	for (int i = 0; i < 4; i++) {
		m_det_4x4[i] = temp_det_4x4[i];
	}
	print_matrix(m_det_4x4, 4);
	printf("\n");
	printf("determinant: %f\n", mdet(m_det_4x4, 4));
	printf("\n");

	/* Test Matrix Inversion */

	float temp_m_toinvert[4][4] = {{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}};

	float *m_toinvert[4];
	for (int i = 0; i < 4; i++) {
		m_toinvert[i] = temp_m_toinvert[i];
	}
	print_matrix(m_toinvert, 4);
	printf("\nInverted:\n");
	float **m_inverted;
	m_inverted = minvert(m_toinvert, 4);
	print_matrix(m_inverted, 4);
	printf("\n");
	
	//

	float a_temp_m_toinvert[4][4] = {{8, -5, 9, 2}, {7, 5, 6, 1}, {-6, 0, 9, 6}, {-3, 0, -9, -4}};

	float *a_m_toinvert[4];
	for (int i = 0; i < 4; i++) {
		a_m_toinvert[i] = a_temp_m_toinvert[i];
	}
	print_matrix(a_m_toinvert, 4);
	printf("\nInverted:\n");
	float **a_m_inverted;
	a_m_inverted = minvert(a_m_toinvert, 4);
	print_matrix(a_m_inverted, 4);
	printf("\n");

	//

	float b_temp_m_toinvert[4][4] = {{9, 3, 0, 9}, {-5, -2, -6, -3}, {-4, 9, 6, 4}, {-7, 6, 6, 2}};

	float *b_m_toinvert[4];
	for (int i = 0; i < 4; i++) {
		b_m_toinvert[i] = b_temp_m_toinvert[i];
	}
	print_matrix(b_m_toinvert, 4);
	printf("\nInverted:\n");
	float **b_m_inverted;
	b_m_inverted = minvert(b_m_toinvert, 4);
	print_matrix(b_m_inverted, 4);
	printf("\n");
	
	//

	float **multiplied_matrix;
	multiplied_matrix = matrixmult(a_m_toinvert, b_m_toinvert);
	printf("\nA * B = C:\n");
	print_matrix(multiplied_matrix, 4);
	float **original_matrix;
	printf("\nA:\n");
	print_matrix(a_m_toinvert, 4);
	original_matrix = matrixmult(multiplied_matrix, b_m_inverted);
	printf("\nC * inverse of B should equal A:\n");
	print_matrix(original_matrix, 4);
	free_matrix(original_matrix, 4);
	free_matrix(multiplied_matrix, 4);

	//
	float **is_it_id;
	printf("\nMultiplying a matrix by its inverse =\n");
	is_it_id = matrixmult(a_m_toinvert, a_m_inverted);
	print_matrix(is_it_id, 4);
	free_matrix(is_it_id, 4);
}

void	print_matrix(float **m, int size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
			printf("%f ", m[y][x++]);
		printf("\n");
		y++;
	}
}

void	fill_matrix(float **m, int size, float steps)
{
	int		i;
	int		j;
	float	fill;

	i = 0;
	fill = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			m[i][j++] = fill;
			fill += steps;
		}
		i++;
	}
}

static void print_tuple(char *str, t_tuple a)
{
	printf("%s x = %f ", str, a.x);
	printf("y = %f ", a.y);
	printf("z = %f ", a.z);
	printf("w = %f", a.w);
	if (a.w == 0)
		printf("  > is a vector\n");
	else if (a.w == 1)
		printf("  > is a point\n");
	else
		printf("\n");
}
