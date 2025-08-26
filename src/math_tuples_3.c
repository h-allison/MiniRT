/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tuples_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:20:01 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/25 12:44:23 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Get Dot Product */
// Takes 2 vectors, returns a scalar value
// The dot product (aka "scalar product" or "inner product")
// - will be relevant when intersecting rays w/ objects
// - is the sum of the products of each vector's components
// - is the cosine of the angle between vectors

// The smaller the dot product, the larger the angle between vectors.
// Dot product 1 means vectors are identical
// Dot product -1 means vectors point in opposite directions

float	dot(t_tuple a, t_tuple b)
{
	return (a.x * b.x
		+ a.y * b.y
		+ a.z * b.z
		+ a.w * b.w);
}

/* Get Cross Product */
// Takes 2 vectors, returns another vector
// The resulting vector is perpendicular to both of the original vectors.
// In 3-dimensional space, this is a right angle

t_tuple	cross(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	result.w = 0;
	return (result);
}
