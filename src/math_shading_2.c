/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shading_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:30:13 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/02 18:09:39 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_rgb	iterate_lights(t_world *w, t_comps *comps)
{
	int		i;
	t_largs	largs;
	t_rgb	surface;

	largs.shape = comps->object;
	largs.material = comps->object->m;
	largs.point = comps->over_point;
	largs.eyev = comps->eyev;
	largs.normalv = comps->normalv;
	surface = color(0, 0, 0);
	i = 0;
	while (1)
	{
		largs.in_shadow = is_shadowed(w, i, comps->over_point);
		largs.light = w->light[i];
		surface = cadd(surface, lighting(&largs, w));
		if (w->light[i]->last)
			break ;
		i++;
	}
	return (surface);
}

t_rgb	shade_hit(t_world *w, t_comps *comps, int remaining)
{
	t_rgb	surface;
	t_rgb	reflected;
	t_rgb	refracted;
	float	reflectance;

	surface = iterate_lights(w, comps);
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
	xs[0].object = NULL;
	return (shade_hit(w, &comps, remaining));
}

float	is_shadowed(t_world *world, int i, t_tuple point)
{
	t_tuple			v;
	float			ret;
	t_ray			r;
	t_intersection	*xs;
	t_intersection	*ht;

	v = tsub(world->light[i]->position, point);
	r = ray(point, tnorm(v));
	xs = intersect_world(world, &r);
	ht = hit(xs);
	if (ht && ht->t < tmag(v))
	{
		ret = ht->object->m->transparency;
		xs[0].object = NULL;
		return (ret);
	}
	xs[0].object = NULL;
	return (1);
}
