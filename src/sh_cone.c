/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:49:31 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 20:40:28 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*cone(void)
{
	t_shape	*s;

	s = malloc(sizeof(t_shape));
	s->parent = NULL;
	s->group = NULL;
	s->triangle = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at_cone;
	s->local_intersect = local_intersect_cone;
	s->m = material();
	s->minimum = -FLT_MAX;
	s->maximum = FLT_MAX;
	s->closed = false;
	return (s);
}

t_tuple	local_normal_at_cone(t_shape *s, t_tuple local_point)
{
	float	dist;
	float	y;

	(void)s;
	dist = local_point.x * local_point.x + local_point.z * local_point.z;
	if (dist <= 1 && local_point.y >= s->maximum - EPSILON)
		return (vector(0, 1, 0));
	else if (dist <= 1 && local_point.y <= s->minimum + EPSILON)
		return (vector(0, -1, 0));
	y = sqrtf(dist);
	y *= -(local_point.y > 0);
	return (vector(local_point.x, y, local_point.z));
}

static bool	check_cap_cone(t_ray r, float t, float y)
{
	float	x;
	float	z;

	x = (r.origin.x + t * r.direction.x);
	z = (r.origin.z + t * r.direction.z);
	return ((x * x + z * z) < fabs(y));
}

static void	intersect_caps_cone(t_shape *cyl, t_intersection *xs, t_ray r)
{
	float	t;

	(void)xs;
	if (!cyl->closed || fisequal(r.direction.y, 0))
		return ;
	t = (cyl->minimum - r.origin.y) / r.direction.y;
	if (check_cap_cone(r, t, cyl->minimum))
		xs = intersections(intersection(t, cyl), intersection(t, cyl));
	t = (cyl->maximum - r.origin.y) / r.direction.y;
	if (check_cap_cone(r, t, cyl->maximum))
		xs = intersections(intersection(t, cyl), intersection(t, cyl));
}

t_intersection	*local_intersect_cone(t_shape *s, t_ray r)
{
	t_intersection	*xs;
	float			a;
	float			b;
	float			c;
	float			disc;
	float			t0;
	float			t1;
	float			y0;
	float			y1;

	a = r.direction.x * r.direction.x
		- r.direction.y * r.direction.y
		+ r.direction.z * r.direction.z;
	b = 2 * r.origin.x * r.direction.x
		- 2 * r.origin.y * r.direction.y
		+ 2 * r.origin.z * r.direction.z;
	xs = intersections(intersection(0, NULL), intersection(0, NULL));
	if (a == 0 && b == 0)
		return (xs);
	c = r.origin.x * r.origin.x
		- r.origin.y * r.origin.y
		+ r.origin.z * r.origin.z;
	if (fisequal (a, 0) && !fisequal(b, 0))
	{
		t0 = -c / (2 * b);
		xs = intersections(intersection(t0, s), intersection(t0, s));
	}
	else
	{
		disc = b * b - 4 * a * c;
		if (disc < -EPSILON)
			return (xs);
		if (disc < EPSILON)
			disc = 0;
		t0 = (-b - sqrtf(disc)) / (2 * a);
		t1 = (-b + sqrtf(disc)) / (2 * a);
		if (t0 > t1)
			swapf(&t0, &t1);
		y0 = r.origin.y + t0 * r.direction.y;
		if (s->minimum < y0 && y0 < s->maximum)
			xs = intersections(intersection(t0, s), intersection(t0, s));
		y1 = r.origin.y + t1 * r.direction.y;
		if (s->minimum < y1 && y1 < s->maximum)
			xs = intersections(intersection(t1, s), intersection(t1, s));
	}
	intersect_caps_cone(s, xs, r);
	return (xs);
}
