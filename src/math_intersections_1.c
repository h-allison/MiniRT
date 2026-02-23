/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:35:10 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 18:04:15 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* OLD FUNCTION, local intersect prototype */

t_intersection	*local_intersect(t_shape *s, t_ray r)
{
	t_tuple			sphere_to_ray;
	float			a;
	float			b;
	float			discriminant;
	t_intersection	*xs;

	(void)r;
	sphere_to_ray = tsub(r.origin, point(0, 0, 0));
	a = dot(r.direction, r.direction);
	b = 2 * dot(r.direction, sphere_to_ray);
	discriminant = b * b - 4 * a * (dot(sphere_to_ray, sphere_to_ray) - 1);
	if (discriminant < 0)
		xs = intersections(intersection(0, NULL), intersection(0, NULL));
	else
		xs = intersections(intersection((-b - sqrtf(discriminant))
					/ (2 * a), s), intersection((-b + sqrtf(discriminant))
					/ (2 * a), s));
	return (xs);
}

/* Calculates intersections with one object */

t_intersection	*intersect(t_shape *s, t_ray r)
{
	t_ray	local_ray;

	local_ray = transform(r, s->invtrans);
	return (s->local_intersect(s, local_ray));
}

/* Store single intersection in a t_intersect */

t_intersection	intersection(float t, t_shape *s)
{
	t_intersection	i;

	i.t = t;
	i.object = s;
	return (i);
}

/* Append to a list of all intersections */

t_intersection	*intersections(t_intersection i1, t_intersection i2)
{
	static __thread t_intersection	xs[100];
	int						i;

	i = 0;
	while (xs[i].object)
		i++;
	xs[i].object = i1.object;
	xs[i].t = i1.t;
	xs[i + 1].object = NULL;
	if (!fisequal(i1.t, i2.t))
	{
		xs[i + 1].object = i2.object;
		xs[i + 1].t = i2.t;
		xs[i + 2].object = NULL;
	}
	return (xs);
}

//TODO FREE

t_intersection	*hit(t_intersection *xs)
{
	int			n;
	int			best;

	if (!xs || !xs[0].object)
		return (NULL);
	best = 0;
	n = 0;
	while (xs[n].object)
	{
		if ((xs[n].t >= 0 && xs[n].t < xs[best].t) || xs[best].t < 0)
			best = n;
		n++;
	}
	if (xs[best].t < 0)
		return (NULL);
	return (&xs[best]);
}
