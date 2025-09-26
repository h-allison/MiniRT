/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_matrices_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:59:09 by hallison          #+#    #+#             */
/*   Updated: 2025/09/27 00:24:35 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* determinants */

float	mdet2x2(float **m)
{
	return ((m[0][0] * m[1][1]) - (m[0][1] * m[1][0]));
}

float	mdet3x3(float **m, int size)
{
	int		i;
	float	det;

	if (size == 2)
		return (mdet2x2(m));
	i = 0;
	det = 0;
	while (i < size)
	{
		det += m[0][i] * mcofactor3x3(m, 0, i);
		i++;
	}
	return (det);
}

float	mdet(float **m, int size)
{
	int		i;
	float	det;
	float	cofactor;
	float	**sub;

	if (size == 2 || size == 3)
		return (mdet3x3(m, size));
	i = 0;
	det = 0;
	while (i < size)
	{
		sub = msubmatrix(m, 4, 0, i);
		cofactor = mdet3x3(sub, 3);
		free_matrix(sub, 3);
		if (i % 2)
			cofactor = -cofactor;
		det += cofactor * m[0][i];
		i++;
	}
	return (det);
}

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

	det = mdet(m, size);
	if (!det)
		return (m);
	m2 = alloc_matrix(size);
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
	{
		mcopy(&m, &m2, size);
		return (m2);
	}
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

void	mcopy(float ***m, float ***m2, int size)
{
	int	y;
	int	x;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			*m[y][x] = *m2[y][x];
			x++;
		}
		y++;
	}
}
