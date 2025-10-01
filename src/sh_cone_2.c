/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cone_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:49:31 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/01 23:28:03 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static bool	calc_xs(t_abc abc, t_shape *s, t_ray r, t_intersection *xs)
{
	float			disc;
	float			t0;
	float			t1;
	float			y0;
	float			y1;

	disc = abc.b * abc.b - 4 * abc.a * abc.c;
	if (disc < -EPSILON)
		return (1);
	if (disc < EPSILON)
		disc = 0;
	t0 = (-abc.b - sqrtf(disc)) / (2 * abc.a);
	t1 = (-abc.b + sqrtf(disc)) / (2 * abc.a);
	if (t0 > t1)
		swapf(&t0, &t1);
	y0 = r.origin.y + t0 * r.direction.y;
	if (s->minimum < y0 && y0 < s->maximum)
		xs = intersections(intersection(t0, s), intersection(t0, s));
	y1 = r.origin.y + t1 * r.direction.y;
	if (s->minimum < y1 && y1 < s->maximum)
		xs = intersections(intersection(t1, s), intersection(t1, s));
	return (0);
}

t_intersection	*local_intersect_cone(t_shape *s, t_ray r)
{
	t_intersection	*xs;
	t_abc			abc;
	float			t0;

	abc.a = r.direction.x * r.direction.x - r.direction.y * r.direction.y
		+ r.direction.z * r.direction.z;
	abc.b = 2 * r.origin.x * r.direction.x - 2 * r.origin.y * r.direction.y
		+ 2 * r.origin.z * r.direction.z;
	xs = intersections(intersection(0, NULL), intersection(0, NULL));
	if (abc.a == 0 && abc.b == 0)
		return (xs);
	abc.c = r.origin.x * r.origin.x - r.origin.y * r.origin.y
		+ r.origin.z * r.origin.z;
	if (fisequal (abc.a, 0) && !fisequal(abc.b, 0))
	{
		t0 = -abc.c / (2 * abc.b);
		xs = intersections(intersection(t0, s), intersection(t0, s));
	}
	else if (calc_xs(abc, s, r, xs))
		return (xs);
	intersect_caps_cone(s, xs, r);
	return (xs);
}
