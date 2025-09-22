/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:07:25 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/22 16:49:51 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* OLD FUNCTIONS */

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

t_rgb	stripe_at_object(t_pattern *pat, t_shape *object, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	pattern_point;

	object_point = tmatrixmult(object->invtrans, world_point);
	pattern_point = tmatrixmult(pat->invtrans, object_point);
	return (stripe_at(pat, pattern_point));
}

/* TEST FUNCTION */

t_rgb	pattern_at(t_pattern *pat, t_tuple point)
{
	t_rgb	col;

	(void) pat;
	col.r = point.x;
	col.g = point.y;
	col.b = point.z;
	return (col);
}

/* ABSTRACT FUNCTION */

t_rgb	pattern_at_shape(t_pattern *pat, t_shape *shape, t_tuple world_point)
{
	t_tuple	shape_point;
	t_tuple	pattern_point;

	shape_point = world_to_object(shape, world_point);
	pattern_point = tmatrixmult(pat->invtrans, shape_point);
	return (pat->pattern_at(pat, pattern_point));
}

/* CONCRETE PATTERNS */

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

/* UV FUNCTIONS */

t_pattern	uv_checkers(float width, float height, t_rgb a, t_rgb b)
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

t_rgb	uv_checkers_at(t_pattern *checkers, t_tuple uv)
{
	float	u2;
	float	v2;
	
	u2 = floorf(uv.x * checkers->width);
	v2 = floorf(uv.y * checkers->height);
	if (fmod(u2 + v2,  2) == 0)
		return (checkers->a);
	return (checkers->b);
}

t_pattern texture_map(t_pattern uv_pattern, t_tuple (*map)(t_tuple))
{
	t_pattern	pattern;

	pattern.a = uv_pattern.a;
	pattern.b = uv_pattern.b;
	pattern.main = uv_pattern.main;
	pattern.ul = uv_pattern.ul;
	pattern.ur = uv_pattern.ur;
	pattern.bl = uv_pattern.bl;
	pattern.br = uv_pattern.br;
	pattern.width = uv_pattern.width;
	pattern.height = uv_pattern.height;
	pattern.transform = create_id_matrix();
	pattern.invtrans = minvert(pattern.transform, 4);
	pattern.pattern_at = texture_at;
	pattern.uv_pattern_at = uv_pattern.pattern_at;
	pattern.map = map;
	pattern.status = true;
	return (pattern);
}

t_rgb	texture_at(t_pattern *texture_map, t_tuple point)
{
	t_tuple	uv;
	
	uv = texture_map->map(point);
	return (texture_map->uv_pattern_at(texture_map, uv));
}

/* UV MAPS */

t_tuple	no_map(t_tuple p)
{
	t_tuple	uv;
	uv.x = p.x;
	uv.y = p.y;
	return (uv);
}

t_tuple	spherical_map(t_tuple p)
{
	float	theta;
	float	radius;
	float	phi;
	float	raw_u;
	t_tuple	 uv;

	theta = atan2f(p.x, p.z);
	radius = tmag(vector(p.x, p.y, p.z));
	phi = acosf(p.y / radius);
	raw_u = theta / (2 * M_PI);
	uv.x = 1 - (raw_u + 0.5);
	uv.y = 1 - phi / M_PI;
	return (uv);
}

t_tuple	cylindrical_map(t_tuple p)
{
	float	theta;
	float	raw_u;
	t_tuple	 uv;

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

t_tuple	cube_map(t_tuple point)
{
	float	abs_x;
	float	abs_y;
	float	abs_z;
	float	coord;

	abs_x = fabs(point.x);
	abs_y = fabs(point.y);
	abs_z = fabs(point.z);
	coord = maxf(abs_x, abs_y, abs_z);

	if (coord == point.x)
		return (cube_uv_right(point));
	else if (coord == -point.x)
		return (cube_uv_left(point));
	else if (coord == point.y)
		return (cube_uv_up(point));
	else if (coord == -point.y)
		return (cube_uv_down(point));
	else if (coord == point.z)
		return (cube_uv_front(point));
return (cube_uv_back(point));
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

/* PART OF TEST PATTERN 13 */

t_pattern	uv_align_check(t_rgb main, t_rgb ul, t_rgb ur, t_rgb bl, t_rgb br)
{
	t_pattern align_check;

	align_check.main = main;
	align_check.ul = ul;
	align_check.ur = ur;
	align_check.bl = bl;
	align_check.br = br;
	align_check.transform = create_id_matrix();
	align_check.invtrans = minvert(align_check.transform, 4);
	align_check.pattern_at = uv_align_check_at;
	align_check.status = true;
	return (align_check);
}

t_rgb	uv_align_check_at(t_pattern *align_check, t_tuple uv)
{
	if (uv.y > 0.8)
	{
		if (uv.x < 0.2)
			return (align_check->ul);
		if (uv.x > 0.8)
			return (align_check->ur);
	}
	else if(uv.y < 0.2)
	{
		if (uv.x < 0.2)
			return (align_check->bl);
		if (uv.x > 0.8)
			return (align_check->br);
	}
	return (align_check->main);
}

/* PART OF TEST PATTERNS 14 */

char	*face_from_point(t_tuple point)
{
	float	abs_x;
	float	abs_y;
	float	abs_z;
	float	coord;

	abs_x = fabs(point.x);
	abs_y = fabs(point.y);
	abs_z = fabs(point.z);
	coord = maxf(abs_x, abs_y, abs_z);

	if (coord == point.x)
		return ("right");
	if (coord == -point.x)
		return ("left");
	if (coord == point.y)
		return ("up");
	if (coord == -point.y)
		return ("down");
	if (coord == point.z)
		return ("front");
	return ("back");
}
