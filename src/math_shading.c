/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:25:23 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/12 14:41:05 by mmillhof         ###   ########.fr       */
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

// new lighting function
/*
void	set_spec_diffuse_black(t_lcalc *lcalc)
{
	lcalc->diffuse = color(0, 0, 0);
	lcalc->specular = color(0, 0, 0);
}

void	calculate_lighting(t_lcalc *lcalc, t_largs *largs)
{
	lcalc->effective_color = cmult(largs->material.color,
			largs->light.intensity);
	lcalc->lightv = tnorm(tsub(largs->light.position, largs->point));
	lcalc->ambient = cscale(lcalc->effective_color, largs->material.ambient);
	lcalc->light_dot_normal = dot(lcalc->lightv, largs->normalv);
	if (lcalc->light_dot_normal < 0)
		set_spec_diffuse_black(lcalc);
	else
	{
		lcalc->diffuse = cscale(cscale(lcalc->effective_color,
					largs->material.diffuse), lcalc->light_dot_normal);
		lcalc->reflectv = reflect(tneg(lcalc->lightv), largs->normalv);
		lcalc->reflect_dot_eye = dot(lcalc->reflectv, largs->eyev);
		if (lcalc->reflect_dot_eye <= 0)
			lcalc->specular = color(0, 0, 0);
		else
		{
			lcalc->factor = powf(lcalc->reflect_dot_eye,
					largs->material.shininess);
			lcalc->specular = cscale(cscale(largs->light.intensity,
						largs->material.specular), lcalc->factor);
		}
	}
}

t_rgb	lighting(t_largs *largs)
{
	t_lcalc	lcalc;
	t_rgb	ret;

	calculate_lighting(&lcalc, largs);
	ret = cadd(cadd(lcalc.ambient, lcalc.diffuse), lcalc.specular);
	return (ret);
}
*/
// original lighting function before refactor


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
		col = stripe_at_object(&largs->material.pattern, largs->object, largs->point);
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
