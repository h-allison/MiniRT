/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_matrices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:09:54 by hallison          #+#    #+#             */
/*   Updated: 2025/08/29 12:35:44 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	misequal(float **m1, float **m2, int size)
{
	int	x;
	int	y;

	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			if (!fisequal(m1[x][y], m2[x][y]))
				return (false);
			y++;
		}
		x++;
	}	
	return (true);
}

/* ONLY for multiplying two 4 X 4 matrices */
// Uses malloc()

float	**matrixmult(float **m1, float **m2)
{
	int	x;
	int	y;
	float **m;

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
	return(m);
}

float	matrixdot(float **m, int y, t_tuple t)
{
	t_tuple	temp;

	temp.x = m[y][0];
	temp.y = m[y][1];
	temp.z = m[y][2];
	temp.w = m[y][3];
	return (dot(temp, t));
}

/* Multiples one 4 X 4 matrix with one tuple*/

t_tuple	tmatrixmult(float **m, t_tuple t)
{
	t_tuple tuple;

	tuple.x = matrixdot(m, 0, t);
	tuple.y = matrixdot(m, 1, t);
	tuple.z = matrixdot(m, 2, t);
	tuple.w = matrixdot(m, 3, t);
	return(tuple);
}

float	**mtranspose(float **m1, int size)
{
	int		x;
	int		y;
	float	**m2;

	m2 = alloc_matrix(size);
	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			m2[x][y] = m1[y][x];
			y++;
		}
		x++;
	}	
	return (m2);
}
