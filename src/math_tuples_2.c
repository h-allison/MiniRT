/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tuples_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:20:01 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/03 11:45:54 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Tuple Multiply */
// Multiples a vector by a "scalar value"
// which scales it uniformly

t_tuple	tmult(t_tuple a, float scalar)
{
	t_tuple	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;
	result.w = a.w * scalar;
	return (result);
}

/* Tuple Divide */
// Divides a vector by a scalar.

t_tuple	tdiv(t_tuple a, float scalar)
{
	t_tuple	result;

	result.x = a.x / scalar;
	result.y = a.y / scalar;
	result.z = a.z / scalar;
	result.w = a.w / scalar;
	return (result);
}
/* Tuple Magnitude */
// Magnitude = the length of a vector
// i.e. distance to walk from one end to the other in a straight line
// Requires Pythagorean theorem:
// magnitude(v) = square root of (x squared + y squared + z squared + w squared)

float	tmag(t_tuple a)
{
	return (sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2) + powf(a.w, 2)));
}

/* Tuple Normalization  */
// Normalization = turning arbitrary vector into a unit vector
// Keeps calculations anchored relative to a common scale
// A normalized vector is in the same direction but with a length of 1.

t_tuple	tnorm(t_tuple a)
{
	float	magnitude;
	t_tuple	result;

	magnitude = tmag(a);
	result.x = a.x / magnitude;
	result.y = a.y / magnitude;
	result.z = a.z / magnitude;
	result.w = a.w / magnitude;
	return (result);
}
