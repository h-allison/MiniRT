/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:55:04 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/05 16:26:35 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Calculates intersections with one object */

static t_ray	invtransform(t_ray r, float **t)
{
	t_ray	r2;
	float	**invt;

	invt = minvert(t, 4);
	r2 = transform(r, invt);
	free_matrix(invt, 4);
	return (r2);
}

t_intersection	*intersect(t_object *s, t_ray r)
{
	t_tuple			sphere_to_ray;
	float			a;
	float			b;
	float			discriminant;
	t_intersection	*xs;

	r = invtransform(r, s->transform);
	sphere_to_ray = tsub(r.origin, point(0, 0, 0));
	a = dot(r.direction, r.direction);
	b = 2 * dot(r.direction, sphere_to_ray);
	discriminant = powf(b, 2) - 4 * a * (dot(sphere_to_ray, sphere_to_ray) - 1);
	if (discriminant < 0)
		xs = intersections(intersection(0, NULL), intersection(0, NULL));
	else
		xs = intersections(intersection((-b - sqrtf(discriminant))
					/ (2 * a), s), intersection((-b + sqrtf(discriminant))
					/ (2 * a), s));
	return (xs);
}

/* Store 1 intersection in a t_intersect */

t_intersection	intersection(float t, t_object *s)
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
