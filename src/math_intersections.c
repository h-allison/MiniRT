/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:55:04 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/01 18:34:44 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Calculates intersections with one object */

t_intersection	*intersect(t_sphere s, t_ray r)
{
	t_tuple			sphere_to_ray;
	float			a;
	float			b;
	float			discriminant;
	float			**inv;
	t_intersection	*xs;
	
	inv = minvert(s.transform, 4);
	r = *transform(r, inv);
	free_matrix(inv, 4);
	sphere_to_ray = tsub(r.origin, s.origin);
	a = dot(r.direction, r.direction);
	b = 2 * dot(r.direction, sphere_to_ray);
	discriminant = powf(b, 2) - 4 * a * (dot(sphere_to_ray, sphere_to_ray) - 1);
	if (discriminant < 0)
		xs = intersections(intersection(0, NULL), intersection(0, NULL));
	else
		xs = intersections(intersection((-b - sqrtf(discriminant))
					/ (2 * a), &s), intersection((-b + sqrtf(discriminant))
					/ (2 * a), &s));
	free(&r);
	return (xs);
}

/* Store 1 intersection in a t_intersect */

t_intersection	intersection(float t, t_sphere *s)
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
	static t_intersection	*xs;
	int						i;

	if (!xs)
	{
		xs = malloc(1000 * sizeof(t_intersection));
		xs[0].object = NULL;
	}
	if (!xs)
		exit (1);
	i = 0;
	while (xs[i].object)
	{
		if (i == 1000)
		{
			printf("You need to increase your xs malloc in intersections();");
			exit(1);
		}
		i++;
	}
	xs[i].object = i1.object;
	xs[i].t = i1.t;
	xs[i + 1].object = i2.object;
	xs[i + 1].t = i2.t;
	xs[i + 2].object = NULL;
	return (xs);
}

//TODO FREE

t_intersection	*hit(t_intersection *xs)
{
	int				n;
	t_intersection	*hit;

	if (!xs[0].object)
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
