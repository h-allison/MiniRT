/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tuples_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:20:01 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/26 15:26:52 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Tuple is equal */
// err = inequality found
// if err, returns 0 ("isequal" is false)
// if no err, returns 1 ("isequal" is true)

bool	tisequal(t_tuple a, t_tuple b)
{
	int	err;

	err = 0;

	err += !fisequal(a.x, b.x);
	err += !fisequal(a.y, b.y);
	err += !fisequal(a.z, b.z);
	err += !fisequal(a.w, b.w);
	return (!err);
}

/* Add 2 Tuples */

// point (w:1) + vector (w:0) = point (w:1)
// vector (w:1) + vector (w:0) = vector (w:1)
// point (w:1) + point (w:1) = nonsense (w:2) !

t_tuple	tadd(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return (result);
}

/* Subtract 2 Tuples */

// point (w:1) - vector (w:0) = point (w:1)
// vector (w:0) - vector (w:0) = vector (w:0)
// point (w:1) - point (w:1) = vector (w:0)
// vector (w:0) - point (w:1) = nonsense (w: -1) !

t_tuple	tsub(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return (result);
}

/* Negate Tuple */
// "given a vector that poitns frmo a surface toward a light source,
// what vector points from the light source back to the surface?

t_tuple	tneg(t_tuple a)
{
	t_tuple	result;

	result.x = -a.x;
	result.y = -a.y;
	result.z = -a.z;
	result.w = -a.w;
	return (result);
}
