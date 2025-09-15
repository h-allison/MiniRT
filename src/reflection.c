/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:21:19 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/16 00:14:31 by mmillhof         ###   ########.fr       */
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
	(void)w;
	if (comps->object->m.transparency == 0 || remaining <= 0)
		return (color(0, 0, 0));
	else
		return (color(255, 255, 255));
}
