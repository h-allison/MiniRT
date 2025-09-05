/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_matrices_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:09:54 by hallison          #+#    #+#             */
/*   Updated: 2025/09/06 00:07:59 by mmillhof         ###   ########.fr       */
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

float	matrixdot(float **m, int y, t_tuple t)
{
	t_tuple	temp;

	temp.x = m[y][0];
	temp.y = m[y][1];
	temp.z = m[y][2];
	temp.w = m[y][3];
	return (dot(temp, t));
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

float	**mtransposefree(float **m, int size)
{
	int		x;
	int		y;
	float	**temp;

	temp = alloc_matrix(size);
	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			temp[x][y] = m[y][x];
			y++;
		}
		x++;
	}
	free_matrix(m, 4);
	return (temp);
}
