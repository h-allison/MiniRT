/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:25:23 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 18:16:40 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* OLD FUNCTION PROTOTYPE */

t_tuple	local_normal_at(t_shape *s, t_tuple local_point)
{
	t_tuple	local_normal;

	(void)s;
	local_normal = tsub(local_point, point(0, 0, 0));
	return (local_normal);
}

/* ABSTRACT FUNCTIONS */

t_tuple	normal_at(t_shape *s, t_tuple world_point)
{
	t_tuple	local_point;
	t_tuple	local_normal;

	local_point = world_to_object(s, world_point);
	local_normal = s->local_normal_at(s, local_point);
	return (normal_to_world(s, local_normal));
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

	if (largs->material->pattern->status)
		col = pattern_at_shape(largs->material->pattern,
				largs->shape, largs->point);
	else
		col = largs->material->color;
	effective_color = cmult(col, largs->light->intensity);
	lightv = tnorm(tsub(largs->light->position, largs->point));
	ambient = cscale(effective_color, largs->material->ambient);
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
		diffuse = cscale(cscale(effective_color, largs->material->diffuse),
				light_dot_normal);
		reflectv = reflect(tneg(lightv), largs->normalv);
		reflect_dot_eye = dot(reflectv, largs->eyev);
		if (reflect_dot_eye <= 0)
			specular = color(0, 0, 0);
		else
		{
			factor = powf(reflect_dot_eye, largs->material->shininess);
			specular = cscale(cscale(largs->light->intensity,
						largs->material->specular), factor);
		}
	}
	ret = cadd(cadd(ambient, diffuse), specular);
	return (ret);
}
