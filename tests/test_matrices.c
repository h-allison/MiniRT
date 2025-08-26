/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_matrices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:59:07 by hallison          #+#    #+#             */
/*   Updated: 2025/08/26 17:39:22 by hallison         ###   ########.fr       */
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
	free_matrix(m, 4);
	printf("\n");
	
	/* Test Tuple Matrix Multiply */
	
	float m7[4][4] = {{1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}};
   	
	float *m8[4];
	for (int i = 0; i < 4; i++) {
        m8[i] = m7[i];
    }

	t_tuple	t = create_point(1, 2, 3); 
	t_tuple tuple = tmatrixmult(m8, t);
	print_tuple("t", tuple);
	return (0);
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
