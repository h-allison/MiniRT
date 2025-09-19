/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tuples_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:20:01 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/19 23:07:22 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Tuple Multiply */
// Multiples a vector by a "scalar value"
// which scales it uniformly

t_tuple	tmult(t_tuple a, float scalar)
{
	a.x = a.x * scalar;
	a.y = a.y * scalar;
	a.z = a.z * scalar;
	a.w = a.w * scalar;
	return (a);
}

/* Tuple Divide */
// Divides a vector by a scalar.

t_tuple	tdiv(t_tuple a, float scalar)
{
	a.x = a.x / scalar;
	a.y = a.y / scalar;
	a.z = a.z / scalar;
	a.w = a.w / scalar;
	return (a);
}
/* Tuple Magnitude */
// Magnitude = the length of a vector
// i.e. distance to walk from one end to the other in a straight line
// Requires Pythagorean theorem:
// magnitude(v) = square root of (x squared + y squared + z squared + w squared)

float	tmag(t_tuple a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w));
}

/* Tuple Normalization  */
// Normalization = turning arbitrary vector into a unit vector
// Keeps calculations anchored relative to a common scale
// A normalized vector is in the same direction but with a length of 1.

t_tuple	tnorm(t_tuple a)
{
	float	magnitude;

	magnitude = tmag(a);
	a.x = a.x / magnitude;
	a.y = a.y / magnitude;
	a.z = a.z / magnitude;
	a.w = a.w / magnitude;
	return (a);
}
