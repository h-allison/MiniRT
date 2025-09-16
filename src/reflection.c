/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:21:19 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/16 13:36:26 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	reflected_color(t_world *w, t_comps *comps, int remaining)
{
	t_ray	reflect_ray;
	t_rgb	col;

	if (comps->object->m.reflective == 0 || remaining <= 0)
		return (color(0, 0, 0));
	reflect_ray = ray(comps->over_point, comps->reflectv);
	col = color_at(w, &reflect_ray, remaining - 1);
	return (cscale(col, comps->object->m.reflective)); 
}

t_rgb	refracted_color(t_world *w, t_comps *comps, int remaining)
{
	float	n_ratio;
	float	cos_i;
	float	sin2_t;
	float	cos_t;
	t_tuple	direction;
	t_ray	refract_ray;
	t_rgb	col;

	if (comps->object->m.transparency == 0 || remaining <= 0)
		return (color(0, 0, 0));
	n_ratio = comps->n1 / comps->n2;
	cos_i = dot(comps->eyev, comps->normalv);
	sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
	if (sin2_t > 1)
		return (color(0, 0, 0));
	cos_t = sqrtf(1.0 - sin2_t);
	direction = tsub(tmult(comps->normalv, n_ratio * cos_i - cos_t),
			tmult(comps->eyev, n_ratio));
	refract_ray = ray(comps->under_point, direction);
	col = cscale(color_at(w, &refract_ray, remaining - 1),
			comps->object->m.transparency);
	return(col);
}
