/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_matrices_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:59:09 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 17:23:11 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	minvertable(float **m, int size)
{
	float	det;

	det = mdet(m, size);
	if (det == 0)
		return (false);
	return (true);
}

float	**minvert_free(float **m, int size)
{
	float	cofactor;
	float	det;
	float	**m2;
	int		y;
	int		x;

	m2 = alloc_matrix(size);
	det = mdet(m, size);
	if (!det)
		return (mcopy(&m2, &m, size), m2);
	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			cofactor = mcofactor4x4(m, size, y, x);
			m2[x][y] = cofactor / det;
			y++;
		}
		x++;
	}
	free_matrix(m, 4);
	return (m2);
}

float	**minvert(float **m, int size)
{
	float	cofactor;
	float	det;
	float	**m2;
	int		y;
	int		x;

	m2 = alloc_matrix(size);
	det = mdet(m, size);
	if (!det)
		return (mcopy(&m2, &m, size), m2);
	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			cofactor = mcofactor4x4(m, size, y, x);
			m2[x][y] = cofactor / det;
			y++;
		}
		x++;
	}
	return (m2);
}

void	mcopy(float ***dst, float ***src, int size)
{
	int	y;
	int	x;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			(*dst)[y][x] = (*src)[y][x];
			x++;
		}
		y++;
	}
}
