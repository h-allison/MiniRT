/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:25:23 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/03 19:52:41 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	normal_at(t_sphere *s, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;
	float	**m;
	
	object_point = tmmultfree(minvert(s->transform, 4), world_point);
	object_normal = tsub(object_point, point(0, 0, 0));
	m = mtransposefree(minvert(s->transform, 4), 4);
	world_normal = tmmultfree(m, object_normal);
	world_normal.w = 0;
	return (tnorm(world_normal));
}


t_tuple	reflect(t_tuple in, t_tuple normal)
{
	return (tsub(in, tmult(tmult(normal, 2), dot(in, normal))));
}


t_rgb	lighting(t_largs *largs)
{
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

	effective_color = cmult(largs->material.color, largs->light.intensity);
	lightv = tnorm(tsub(largs->light.position, largs->point));
	ambient = cscale(effective_color, largs->material.ambient);
	light_dot_normal = dot(lightv, largs->normalv);
	if (light_dot_normal < 0)
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
	if (ret.r > 1)
		ret.r = 1;
	if (ret.g > 1)
		ret.g = 1;
	if (ret.b > 1)
		ret.b = 1;
	return (ret);
}
