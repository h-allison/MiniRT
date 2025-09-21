/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:07:25 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/21 12:08:36 by mmillhof         ###   ########.fr       */
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
	if (fmod(floorf(point.x), 2) == 0)
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
	return (cadd(gradient->a, cscale(distance, fraction)));
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

t_tuple	spherical_map(t_tuple p)
{
	float	theta;
	float	radius;
	float	phi;
	float	raw_u;
	t_tuple uv;

	theta = atan2f(p.x, p.z);
	radius = tmag(vector(p.x, p.y, p.z));
	phi = acosf(p.y / radius);
	raw_u = theta / (2 * M_PI);
	uv.x = 1 - (raw_u + 0.5);
	uv.y = 1 - phi / M_PI;
	return (uv);
}

t_tuple cylindrical_map(t_tuple p)
{
	float	theta;
	float	raw_u;
	t_tuple uv;

	theta = atan2f(p.x, p.z);
	raw_u = theta / (2 * M_PI);
	uv.x = 1 - (raw_u + 0.5);
	uv.y = fmod(p.y, 1);
	return (uv);
}

t_tuple	planar_map(t_tuple p)
{
	t_tuple	uv;

	uv.x = fmod(p.x, 1);
	uv.y = fmod(p.z, 1);
	return (uv);
}

t_pattern	uv_checkers_pattern(float width, float height, t_rgb a, t_rgb b)
{
	t_pattern	checkers;

	checkers.a = a;
	checkers.b = b;
	checkers.width = width;
	checkers.height = height;
	checkers.transform = create_id_matrix();
	checkers.invtrans = minvert(checkers.transform, 4);
	checkers.pattern_at = uv_checkers_at;
	checkers.status = true;
	return (checkers);
}

t_rgb	uv_checkers_at(t_pattern *checkers, t_tuple point)
{
	float	u2;
	float	v2;
	t_tuple	uv;
	
	uv = spherical_map(point);
	u2 = floorf(uv.x * checkers->width);
	v2 = floorf(uv.y * checkers->height);
	if (fmod(u2 + v2,  2) == 0)
		return (checkers->a);
	return (checkers->b);
}

t_pattern	uv_planar_pattern(float width, float height, t_rgb a, t_rgb b)
{
	t_pattern	planar;

	planar.a = a;
	planar.b = b;
	planar.width = width;
	planar.height = height;
	planar.transform = create_id_matrix();
	planar.invtrans = minvert(planar.transform, 4);
	planar.pattern_at = uv_planar_at;
	planar.status = true;
	return (planar);
}

t_rgb	uv_planar_at(t_pattern *planar, t_tuple point)
{
	float	u2;
	float	v2;
	t_tuple	uv;
	
	uv = planar_map(point);
	u2 = floorf(uv.x * planar->width);
	v2 = floorf(uv.y * planar->height);
	if ((int)(u2 + v2) % 2 == 0)
		return (planar->a);
	return (planar->b);
}


t_pattern	uv_cylindrical_pattern(float width, float height, t_rgb a, t_rgb b)
{
	t_pattern	cylindrical;

	cylindrical.a = a;
	cylindrical.b = b;
	cylindrical.width = width;
	cylindrical.height = height;
	cylindrical.transform = create_id_matrix();
	cylindrical.invtrans = minvert(cylindrical.transform, 4);
	cylindrical.pattern_at = uv_cylindrical_at;
	cylindrical.status = true;
	return (cylindrical);
}

t_rgb	uv_cylindrical_at(t_pattern *cylindrical, t_tuple point)
{
	float	u2;
	float	v2;
	t_tuple	uv;
	
	uv = cylindrical_map(point);
	u2 = floorf(uv.x * cylindrical->width);
	v2 = floorf(uv.y * cylindrical->height);
	if ((int)(u2 + v2) % 2 == 0)
		return (cylindrical->a);
	return (cylindrical->b);
}

t_rgb	stripe_at_object(t_pattern *pat, t_shape *object, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	pattern_point;

	object_point = tmatrixmult(object->invtrans, world_point);
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

t_rgb	pattern_at_shape(t_pattern *pat, t_shape *shape, t_tuple world_point)
{
	t_tuple	shape_point;
	t_tuple	pattern_point;

	shape_point = world_to_object(shape, world_point);
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
