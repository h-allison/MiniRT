/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:07:25 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/20 18:54:15 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	stripe_pattern(t_rgb a, t_rgb b)
{
	t_pattern	pat;

	pat.a = a;
	pat.b = b;
	pat.transform = create_id_matrix();
	pat.invtrans = minvert(pat.transform, 4);
	pat.pattern_at = stripe_at;
	pat.status = true;
	return (pat);
}

t_rgb	stripe_at(t_pattern *pat, t_tuple point)
{
	int	pint;

	pint = (int)floorf(point.x);
	if (pint % 2 == 0)
		return (pat->a);
	return (pat->b);
}

t_pattern	gradient_pattern(t_rgb a, t_rgb b)
{
	t_pattern	gradient;

	gradient.a = a;
	gradient.b = b;
	gradient.transform = create_id_matrix();
	gradient.invtrans = minvert(gradient.transform, 4);
	gradient.pattern_at = gradient_at;
	gradient.status = true;
	return (gradient);
}

t_rgb	gradient_at(t_pattern *gradient, t_tuple point)
{
	t_rgb	distance;
	float	fraction;

	distance = csub(gradient->b, gradient->a);
	fraction = point.x - floorf(point.x);
	return cadd(gradient->a, cscale(distance, fraction));
}

t_pattern	ring_pattern(t_rgb a, t_rgb b)
{
	t_pattern	ring;

	ring.a = a;
	ring.b = b;
	ring.transform = create_id_matrix();
	ring.invtrans = minvert(ring.transform, 4);
	ring.pattern_at = ring_at;
	ring.status = true;
	return (ring);
}

t_rgb	ring_at(t_pattern *ring, t_tuple point)
{
	if ((int)floorf(sqrtf(point.x * point.x + point.z * point.z)) % 2 == 0)
		return (ring->a);
	return (ring->b);
}

t_pattern	checkers_pattern(t_rgb a, t_rgb b)
{
	t_pattern	checkers;

	checkers.a = a;
	checkers.b = b;
	checkers.transform = create_id_matrix();
	checkers.invtrans = minvert(checkers.transform, 4);
	checkers.pattern_at = checkers_at;
	checkers.status = true;
	return (checkers);
}

t_rgb	checkers_at(t_pattern *checkers, t_tuple point)
{
	if ((int)(floorf(point.x) + floorf(point.y) + floorf(point.z)) % 2 == 0)
		return (checkers->a);
	return (checkers->b);
}

t_rgb	stripe_at_object(t_pattern *pat, t_shape *object, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple pattern_point;

	object_point = world_to_object(object, world_point);
	pattern_point = tmatrixmult(pat->invtrans, object_point);
	return (stripe_at(pat, pattern_point));
}

t_rgb	pattern_at(t_pattern *pat, t_tuple point)
{
	t_rgb	col;

	(void) pat;
	col.r = point.x;
	col.g = point.y;
	col.b = point.z;
	return (col);
}
t_rgb	pattern_at_shape(t_pattern *pat, t_shape *shape, t_tuple point)
{
	t_tuple	shape_point;
	t_tuple pattern_point;

	shape_point = world_to_object(shape, point);
	pattern_point = tmatrixmult(pat->invtrans, shape_point);
	return (pat->pattern_at(pat, pattern_point));
}

void	set_pattern_transform(t_pattern *pat, float **t)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			pat->transform[i][j] = t[i][j];
			j++;
		}
		i++;
	}
	free_matrix(t, 4);
	pat->invtrans = minvert(pat->transform, 4);
}
