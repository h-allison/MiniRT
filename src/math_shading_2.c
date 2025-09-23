/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shading_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:30:13 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/23 01:28:51 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	shade_hit(t_world *w, t_comps *comps, int remaining)
{
	t_largs	largs;
	int		i;
	t_rgb	surface;
	t_rgb	reflected;
	t_rgb	refracted;
	float	reflectance;

	surface = color(0, 0, 0);
	i = 0;
	while (1)
	{
		largs.shape = comps->object;
		largs.material = comps->object->m;
		largs.light = w->light[i];
		largs.point = comps->over_point;
		largs.eyev = comps->eyev;
		largs.normalv = comps->normalv;
		largs.in_shadow = is_shadowed(w, i, comps->over_point);
		surface = cadd(surface, lighting(&largs));
		if (w->light[i]->last)
			break ;
		i++;
	}
	reflected = reflected_color(w, comps, remaining);
	refracted = refracted_color(w, comps, remaining);
	if (comps->object->m->reflective > 0 && comps->object->m->transparency > 0)
	{
		reflectance = schlick(comps);
		return (cadd(cadd(surface, cscale(reflected, reflectance)),
				cscale(refracted, 1 - reflectance)));
	}
	return (cadd(cadd(surface, reflected), refracted));
}

t_rgb	color_at(t_world *w, t_ray *r, int remaining)
{
	t_intersection	*xs;
	t_intersection	*ht;
	t_comps			comps;

	xs = intersect_world(w, r);
	ht = hit(xs);
	if (!ht)
	{
		xs[0].object = NULL;
		return (color(0, 0, 0));
	}
	comps = prepare_computations(ht, r, xs);
	free(ht);
	xs[0].object = NULL;
	return (shade_hit(w, &comps, remaining));
}

bool	is_shadowed(t_world *world, int i, t_tuple point)
{
	t_tuple			v;
	float			distance;
	t_tuple			direction;
	t_ray			r;
	t_intersection	*xs;
	t_intersection	*ht;

	v = tsub(world->light[i]->position, point);
	distance = tmag(v);
	direction = tnorm(v);
	r = ray(point, direction);
	xs = intersect_world(world, &r);
	ht = hit(xs);
	xs[0].object = NULL;
	if (ht && ht->t < distance)
	{
		free(ht);
		return (true);
	}
	free(ht);
	return (false);
}
