/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tuples_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:20:01 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/19 23:06:52 by mmillhof         ###   ########.fr       */
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
	a.x = a.x + b.x;
	a.y = a.y + b.y;
	a.z = a.z + b.z;
	a.w = a.w + b.w;
	return (a);
}

/* Subtract 2 Tuples */

// point (w:1) - vector (w:0) = point (w:1)
// vector (w:0) - vector (w:0) = vector (w:0)
// point (w:1) - point (w:1) = vector (w:0)
// vector (w:0) - point (w:1) = nonsense (w: -1) !

t_tuple	tsub(t_tuple a, t_tuple b)
{
	a.x = a.x - b.x;
	a.y = a.y - b.y;
	a.z = a.z - b.z;
	a.w = a.w - b.w;
	return (a);
}

/* Negate Tuple */
// "given a vector that poitns frmo a surface toward a light source,
// what vector points from the light source back to the surface?

t_tuple	tneg(t_tuple a)
{
	a.x = -a.x;
	a.y = -a.y;
	a.z = -a.z;
	a.w = -a.w;
	return (a);
}
