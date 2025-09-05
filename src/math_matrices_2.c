/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_matrices_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:09:54 by hallison          #+#    #+#             */
/*   Updated: 2025/09/06 00:00:09 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ONLY for multiplying two 4 X 4 matrices */
// Uses malloc()

float	**matrixmult(float **m1, float **m2)
{
	int		x;
	int		y;
	float	**m;

	m = alloc_matrix(4);
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			m[x][y] = m1[x][0] * m2[0][y]
				+ m1[x][1] * m2[1][y]
				+ m1[x][2] * m2[2][y]
				+ m1[x][3] * m2[3][y];
			x++;
		}
		y++;
	}
	return (m);
}

float	**mmultfree(float **m1, float **m2)
{
	int		x;
	int		y;
	float	**m;

	m = alloc_matrix(4);
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			m[x][y] = m1[x][0] * m2[0][y]
				+ m1[x][1] * m2[1][y]
				+ m1[x][2] * m2[2][y]
				+ m1[x][3] * m2[3][y];
			x++;
		}
		y++;
	}
	free_matrix(m1, 4);
	free_matrix(m2, 4);
	return (m);
}

/* Multiples one 4 X 4 matrix with one tuple*/

t_tuple	tmatrixmult(float **m, t_tuple t)
{
	t_tuple	tuple;

	tuple.x = matrixdot(m, 0, t);
	tuple.y = matrixdot(m, 1, t);
	tuple.z = matrixdot(m, 2, t);
	tuple.w = matrixdot(m, 3, t);
	return (tuple);
}

t_tuple	tmmultfree(float **m, t_tuple t)
{
	t_tuple	tuple;

	tuple.x = matrixdot(m, 0, t);
	tuple.y = matrixdot(m, 1, t);
	tuple.z = matrixdot(m, 2, t);
	tuple.w = matrixdot(m, 3, t);
	free_matrix(m, 4);
	return (tuple);
}
