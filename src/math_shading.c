/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:25:23 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/17 17:07:38 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	local_normal_at_sphere(t_shape *s, t_tuple local_point)
{
	t_tuple	local_normal;

	(void)s;
	local_normal = tsub(local_point, point(0, 0, 0));
	return (local_normal);
}

t_tuple	local_normal_at_plane(t_shape *s, t_tuple local_point)
{
	(void)s;
	(void)local_point;
	return (vector(0, 1, 0));
}

t_tuple	local_normal_at_cube(t_shape *s, t_tuple local_point)
{
	float	maxc;

	(void)s;
	maxc = maxf(fabs(local_point.x), fabs(local_point.y), fabs(local_point.z));
	if (maxc == fabs(local_point.x))
		return (vector(local_point.x, 0, 0));
	if (maxc == fabs(local_point.y))
		return (vector(0, local_point.y, 0));
	return (vector(0, 0, local_point.z));
}

t_tuple	local_normal_at_cyl(t_shape *s, t_tuple local_point)
{
	(void)s;

	float	dist;

	dist = local_point.x * local_point.x + local_point.z * local_point.z;
	if (dist < 1 && local_point.y >= s->maximum - EPSILON)
		return (vector(0, 1, 0));
	else if (dist < 1 && local_point.y <= s->minimum + EPSILON)
		return (vector(0, -1, 0));
	return (vector(local_point.x, 0, local_point.z));
}

t_tuple	local_normal_at(t_shape *s, t_tuple local_point)
{
	t_tuple	local_normal;

	(void)s;
	local_normal = tsub(local_point, point(0, 0, 0));
	return (local_normal);
}

t_tuple	normal_at(t_shape *s, t_tuple world_point)
{
	t_tuple	local_point;
	t_tuple	local_normal;
	t_tuple	world_normal;
	float	**m;

	local_point = tmatrixmult(s->invtrans, world_point);
	local_normal = s->local_normal_at(s, local_point);
	m = mtranspose(s->invtrans, 4);
	world_normal = tmmultfree(m, local_normal);
	world_normal.w = 0;
	return (tnorm(world_normal));
}

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	return (tsub(in, tmult(tmult(normal, 2), dot(in, normal))));
}

t_rgb	lighting(t_largs *largs)
{
	t_rgb	col;
	t_rgb	effective_color;
	t_rgb	ambient;
	t_rgb	diffuse;
	t_rgb	specular;
	t_tuple	lightv;
	t_tuple	reflectv;
	float	light_dot_normal;
	float	reflect_dot_eye;
	float	factor;
	t_rgb	ret;

	if (largs->material.pattern.status)
		col = pattern_at_shape(&largs->material.pattern, largs->shape, largs->point);
	else
		col = largs->material.color;
	effective_color = cmult(col, largs->light.intensity);
	lightv = tnorm(tsub(largs->light.position, largs->point));
	ambient = cscale(effective_color, largs->material.ambient);
	if (largs->in_shadow)
		return (ambient);
	light_dot_normal = dot(lightv, largs->normalv);
	if (light_dot_normal < 0 || largs->in_shadow)
	{
		diffuse = color(0, 0, 0);
		specular = color(0, 0, 0);
	}
	else
	{
		diffuse = cscale(cscale(effective_color, largs->material.diffuse),
				light_dot_normal);
		reflectv = reflect(tneg(lightv), largs->normalv);
		reflect_dot_eye = dot(reflectv, largs->eyev);
		if (reflect_dot_eye <= 0)
			specular = color(0, 0, 0);
		else
		{
			factor = powf(reflect_dot_eye, largs->material.shininess);
			specular = cscale(cscale(largs->light.intensity,
						largs->material.specular), factor);
		}
	}
	ret = cadd(cadd(ambient, diffuse), specular);
	return (ret);
}
