/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shading_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:25:23 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/02 18:59:18 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	return (tsub(in, tmult(tmult(normal, 2), dot(in, normal))));
}

static t_rgb	calc_eff_col(t_largs *largs)
{
	t_rgb	col;
	t_rgb	effective_color;

	if (largs->material->pattern->status)
		col = pattern_at_shape(largs->material->pattern,
				largs->shape, largs->point);
	else
		col = largs->material->color;
	effective_color = cmult(col, largs->light->intensity);
	return (effective_color);
}

static t_rgb	calc_specular(t_largs *largs, float reflect_dot_eye)
{
	float	factor;
	t_rgb	specular;

	factor = powf(reflect_dot_eye, largs->material->shininess);
	specular = cscale(cscale(largs->light->intensity,
				largs->material->specular), factor);
	return (specular);
}

static void	calc_diff_spec(t_largs *largs, t_rgb eff_color,
		t_rgb *diff, t_rgb *spec)
{
	t_tuple	lightv;
	t_tuple	reflectv;
	float	light_dot_normal;
	float	reflect_dot_eye;

	lightv = tnorm(tsub(largs->light->position, largs->point));
	light_dot_normal = dot(lightv, largs->normalv);
	if (light_dot_normal < 0)
	{
		*diff = color(0, 0, 0);
		*spec = color(0, 0, 0);
	}
	else
	{
		*diff = cscale(cscale(eff_color, largs->material->diffuse),
				light_dot_normal);
		reflectv = reflect(tneg(lightv), largs->normalv);
		reflect_dot_eye = dot(reflectv, largs->eyev);
		if (reflect_dot_eye <= 0)
			*spec = color(0, 0, 0);
		else
			*spec = calc_specular(largs, reflect_dot_eye);
	}
}

t_rgb	lighting(t_largs *largs, t_world *w)
{
	t_rgb	effective_color;
	t_rgb	ambient;
	t_rgb	diffuse;
	t_rgb	specular;
	t_rgb	shape_color;

	effective_color = calc_eff_col(largs);
	ambient = cscale(effective_color, largs->material->ambient);
	calc_diff_spec(largs, effective_color, &diffuse, &specular);
	diffuse = cscale(diffuse, largs->in_shadow);
	specular = cscale(specular, largs->in_shadow);
	shape_color = cadd(cadd(ambient, diffuse), specular);
	shape_color = cscale(cadd(shape_color, w->ambient_total),
			0.5 + 0.5 * (1 - w->ambient_ratio));
	return (shape_color);
}
