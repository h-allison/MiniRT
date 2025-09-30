/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_matrices_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:02:00 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/30 17:02:09 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	**msubmatrix(float **m, int size, int row, int col)
{
	float	**sub;
	int		y_m;
	int		y_sub;
	int		x_m;

	sub = alloc_matrix(size - 1);
	y_m = 0;
	y_sub = 0;
	while (y_m < size)
	{
		if (y_m != row)
		{
			x_m = 0;
			while (x_m < size)
			{
				if (x_m != col)
					sub[y_sub][x_m - (x_m > col)] = m[y_m][x_m];
				x_m++;
			}
			y_sub++;
		}
		y_m++;
	}
	return (sub);
}

float	mminor3x3(float **m, int row, int col)
{
	float	minor;
	float	**sub;

	sub = msubmatrix(m, 3, row, col);
	minor = mdet2x2(sub);
	free_matrix(sub, 2);
	return (minor);
}

float	mcofactor4x4(float **m, int size, int row, int col)
{
	float	cofactor;
	float	**sub;

	sub = msubmatrix(m, size, row, col);
	cofactor = mdet3x3(sub, 3); 
	free_matrix(sub, size - 1);
	if ((row + col) % 2)
		cofactor = -cofactor;
	return (cofactor);
}

float	mcofactor3x3(float **m, int row, int col)
{
	float	cofactor;

	cofactor = mminor3x3(m, row, col);
	if ((row + col) % 2)
		cofactor = -cofactor;
	return (cofactor);
}
