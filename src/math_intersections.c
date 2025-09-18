/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:35:10 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/18 14:13:36 by matthias         ###   ########.fr       */
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

void	swapf(float *a, float *b)
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
		*tmin = tmin_numerator * FLT_MAX;
		*tmax = tmax_numerator * FLT_MAX;
	}
	if (*tmin > *tmax)
		swapf(tmin, tmax);
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

static bool	check_cap(t_ray *r, float t)
{
	float	x;
	float	z;

	x = r->origin.x + t * r->direction.x;
	z = r->origin.z + t * r->direction.z;
	return ((x * x + z * z) < 1 + EPSILON);
}

void	intersect_caps(t_shape *cyl, t_intersection *xs)
{
	float	t;
	
	(void)xs;
	if (!cyl->closed || fisequal(cyl->saved_ray.direction.y, 0))
		return ;
	t = (cyl->minimum - cyl->saved_ray.origin.y) / cyl->saved_ray.direction.y;
	if (check_cap(&cyl->saved_ray, t))
		xs = intersections(intersection(t, cyl), intersection(t, cyl));
	t = (cyl->maximum - cyl->saved_ray.origin.y) / cyl->saved_ray.direction.y;
	if (check_cap(&cyl->saved_ray, t))
		xs = intersections(intersection(t, cyl), intersection(t, cyl));
	return ;
}

t_intersection	*local_intersect_cyl(t_shape *s)
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

	a = s->saved_ray.direction.x * s->saved_ray.direction.x +
		s->saved_ray.direction.z * s->saved_ray.direction.z;
	xs = intersections(intersection(0, NULL), intersection(0, NULL));
	if (!fisequal(a, 0))
	{
		b = 2 * s->saved_ray.origin.x * s->saved_ray.direction.x +
			2 * s->saved_ray.origin.z * s->saved_ray.direction.z;
		c = s->saved_ray.origin.x * s->saved_ray.origin.x +
			s->saved_ray.origin.z * s->saved_ray.origin.z - 1;
		disc = b * b - 4 * a * c;
		if (disc < 0)
			return (xs);
		t0 = (-b - sqrtf(disc)) / (2 * a);
		t1 = (-b + sqrtf(disc)) / (2 * a);
		if (t0 > t1)
			swapf(&t0, &t1);
		y0 = s->saved_ray.origin.y + t0 * s->saved_ray.direction.y;
		if ((s->minimum) < y0 && y0 < s->maximum)
			xs = intersections(intersection(t0, s), intersection(t0, s));
		y1 = s->saved_ray.origin.y + t1 * s->saved_ray.direction.y;
		if (s->minimum < y1 && y1 < s->maximum)
			xs = intersections(intersection(t1, s), intersection(t1, s));
	}
	intersect_caps(s, xs);
	return (xs);
}

static bool	check_cap_cone(t_ray *r, float t, float y)
{
	float	x;
	float	z;

	x = (r->origin.x + t * r->direction.x);
	z = (r->origin.z + t * r->direction.z);
	return ((x * x + z * z) < fabs(y));
}

void	intersect_caps_cone(t_shape *cyl, t_intersection *xs)
{
	float	t;

	(void)xs;
	if (!cyl->closed || fisequal(cyl->saved_ray.direction.y, 0))
		return ;
	t = (cyl->minimum - cyl->saved_ray.origin.y) / cyl->saved_ray.direction.y;
	if (check_cap_cone(&cyl->saved_ray, t, cyl->minimum))
		xs = intersections(intersection(t, cyl), intersection(t, cyl));
	t = (cyl->maximum - cyl->saved_ray.origin.y) / cyl->saved_ray.direction.y;
	if (check_cap_cone(&cyl->saved_ray, t, cyl->maximum))
		xs = intersections(intersection(t, cyl), intersection(t, cyl));
}

t_intersection	*local_intersect_cone(t_shape *s)
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

	a = s->saved_ray.direction.x * s->saved_ray.direction.x -
		s->saved_ray.direction.y * s->saved_ray.direction.y +
		s->saved_ray.direction.z * s->saved_ray.direction.z;
	b = 2 * s->saved_ray.origin.x * s->saved_ray.direction.x -
		2 * s->saved_ray.origin.y * s->saved_ray.direction.y +
		2 * s->saved_ray.origin.z * s->saved_ray.direction.z;
	xs = intersections(intersection(0, NULL), intersection(0, NULL));
	if (a == 0 && b == 0)
		return (xs);
	c = s->saved_ray.origin.x * s->saved_ray.origin.x -
		s->saved_ray.origin.y * s->saved_ray.origin.y +
		s->saved_ray.origin.z * s->saved_ray.origin.z;
	if (a == 0 && b != 0)
	{
		t0 = -c / (2 * b);
		xs = intersections(intersection(t0, s), intersection(t0, s));
	}
	else
	{
		disc = b * b - 4 * a * c;
		if (disc < 0)
			return (xs);
		t0 = (-b - sqrtf(disc)) / (2 * a);
		t1 = (-b + sqrtf(disc)) / (2 * a);
		if (t0 > t1)
			swapf(&t0, &t1);
		y0 = s->saved_ray.origin.y + t0 * s->saved_ray.direction.y;
		if (s->minimum < y0 && y0 < s->maximum)
			xs = intersections(intersection(t0, s), intersection(t0, s));
		y1 = s->saved_ray.origin.y + t1 * s->saved_ray.direction.y;
		if (s->minimum < y1 && y1 < s->maximum)
			xs = intersections(intersection(t1, s), intersection(t1, s));
	}
	intersect_caps_cone(s, xs);
	return (xs);
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
