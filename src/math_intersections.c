/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:55:04 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/10 10:43:45 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Calculates intersections with one object */

t_intersection	*local_intersect(t_shape *s)
{
	t_tuple			sphere_to_ray;
	float			a;
	float			b;
	float			discriminant;
	t_intersection	*xs;

	sphere_to_ray = tsub(s->saved_ray.origin, point(0, 0, 0));
	a = dot(s->saved_ray.direction, s->saved_ray.direction);
	b = 2 * dot(s->saved_ray.direction, sphere_to_ray);
	discriminant = b * b - 4 * a * (dot(sphere_to_ray, sphere_to_ray) - 1);
	if (discriminant < 0)
		xs = intersections(intersection(0, NULL), intersection(0, NULL));
	else
		xs = intersections(intersection((-b - sqrtf(discriminant))
					/ (2 * a), s), intersection((-b + sqrtf(discriminant))
					/ (2 * a), s));
	return (xs);
}

t_intersection	*intersect(t_shape *s, t_ray r)
{
	t_ray	local_r;
	float	**invt;

	invt = minvert(s->transform, 4);
	local_r = transform(r, invt);;
	s->saved_ray = local_r;
	return (local_intersect(s));
}

/* Store 1 intersection in a t_intersect */

t_intersection	intersection(float t, t_shape *s)
{
	t_intersection	i;

	i.t = t;
	i.object = s;
	return (i);
}

//TODO FREE

/* Append to a list of all intersections */

t_intersection	*intersections(t_intersection i1, t_intersection i2)
{
	static t_intersection	xs[100];
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
	int				n;
	t_intersection	*hit;

	if (!xs || !xs[0].object)
		return (NULL);
	hit = malloc(sizeof(t_intersection));
	if (!hit)
		exit (1);
	hit->object = xs[0].object;
	hit->t = xs[0].t;
	n = 0;
	while (xs[n].object)
	{
		if ((xs[n].t >= 0 && xs[n].t < hit->t) || hit->t < 0)
		{
			hit->object = xs[n].object;
			hit->t = xs[n].t;
		}
		n++;
	}
	if (hit->t < 0)
		return (free(hit), NULL);
	return (hit);
}
