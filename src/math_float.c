/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:20:01 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 17:58:09 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	fisequal(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	return (false);
}

void	swapf(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

float	minf(float a, float b, float c)
{
	float	min;

	min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return (min);
}

float	maxf(float a, float b, float c)
{
	float	max;

	max = a;
	if (b > max)
		max = b;
	if (c > max)
		max = c;
	return (max);
}
