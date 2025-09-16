/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:55:04 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/16 23:24:45 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Calculates intersections with one object */

t_intersection	*local_intersect_sphere(t_shape *s)
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

t_intersection	*local_intersect_plane(t_shape *s)
{
	t_intersection	*xs;
	float			t;

	if (fabs(s->saved_ray.direction.y) < EPSILON)
		xs = intersections(intersection(0, NULL), intersection(0, NULL));
	else
	{
		t = -s->saved_ray.origin.y / s->saved_ray.direction.y;
		xs = intersections(intersection(t, s), intersection(0, NULL));
	}
	return (xs);
}

static void	swap(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static float	minf(float a, float b, float c)
{
	if (a < b && a < c)
		return (a);
	if (b < a && b < c)
		return (b);
	return (c);
}

float	maxf(float a, float b, float c)
{
	if (a > b && a > c)
		return (a);
	if (b > a && b > c)
		return (b);
	return (c);
}

static void	check_axis(float *tmin, float *tmax, float origin, float direction)
{
	float	tmin_numerator;
	float	tmax_numerator;

	tmin_numerator = (-1 - origin);
	tmax_numerator = (1 - origin);
	if (fabs(direction) >= EPSILON)
	{
		*tmin = tmin_numerator / direction;
		*tmax = tmax_numerator / direction;
	}
	else
	{
		*tmin = tmin_numerator * DBL_MAX;
		*tmax = tmax_numerator * DBL_MAX;
	}
	if (*tmin > *tmax)
		swap(tmin, tmax);
	return ;
}

t_intersection	*local_intersect_cube(t_shape *s)
{
	t_tminmax	t;
	float		tmin;
	float		tmax;

	check_axis(&t.xtmin, &t.xtmax,
		s->saved_ray.origin.x, s->saved_ray.direction.x);
	check_axis(&t.ytmin, &t.ytmax,
		s->saved_ray.origin.y, s->saved_ray.direction.y);
	check_axis(&t.ztmin, &t.ztmax,
		s->saved_ray.origin.z, s->saved_ray.direction.z);
	tmin = maxf(t.xtmin, t.ytmin, t.ztmin);
	tmax = minf(t.xtmax, t.ytmax, t.ztmax);
	if (tmin > tmax)
		return(intersections(intersection(0, NULL), intersection(0,NULL)));
	return (intersections(intersection(tmin, s), intersection(tmax, s)));
}

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

	local_r = transform(r, s->invtrans);;
	s->saved_ray = local_r;
	return (s->local_intersect(s));
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
