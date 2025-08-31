/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:55:04 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/31 18:41:05 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	*intersect(t_sphere s, t_ray r)
{
	t_tuple			sphere_to_ray;
	float			a;
	float			b;
	float			discriminant;
	t_intersection	*xs;

	sphere_to_ray = tsub(r.origin, s.origin);
	a = dot(r.direction, r.direction);
	b = 2 * dot(r.direction, sphere_to_ray);
	discriminant = powf(b, 2) - 4 * a * (dot(sphere_to_ray, sphere_to_ray) - 1);
	if (discriminant < 0)
		return (NULL);
	xs = intersections(intersection((-b - sqrtf(discriminant)) / (2 * a), &s),
			intersection((-b + sqrtf(discriminant)) / (2 * a), &s));
	return (xs);
}

t_intersection	intersection(float t, t_sphere *s)
{
	t_intersection	i;

	i.t = t;
	i.object = s;
	return (i);
}

//TODO FREE

t_intersection	*intersections(t_intersection i1, t_intersection i2)
{
	t_intersection	*xs;

	xs = malloc(3 * sizeof(t_intersection));
	if (!xs)
		exit (1);
	xs[0].object = i1.object;
	xs[0].t = i1.t;
	xs[1].object = i2.object;
	xs[1].t = i2.t;
	xs[2].object = NULL;
	return (xs);
}

//TODO FREE

t_intersection	*hit(t_intersection *xs)
{
	int				n;
	t_intersection	*hit;

	if (!xs)
		return (NULL);
	hit = malloc(sizeof(t_intersection));
	if (!hit)
		exit (1);
	hit->object = xs[0].object;
	hit->t = xs[0].t;
	n = 0;
	while (xs[n].object)
	{
		if (xs[n].t < hit->t || hit->t < 0)
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
