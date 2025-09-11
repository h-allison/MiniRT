/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shading_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:30:13 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/09 17:03:56 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	shade_hit_double(t_world *w, t_comps *comps)
{
	t_largs	largs;
	t_rgb	ret_light;
	int	i;

	i = 0;
	ret_light = color(0, 0, 0);
	while (i < 2)
	{
		largs.material = comps->object->m;
		largs.light = w->light[i];
		largs.point = comps->over_point;
		largs.eyev = comps->eyev;
		largs.normalv = comps->normalv;
		largs.in_shadow = is_shadowed(w, i, comps->over_point);
		ret_light = cadd(ret_light, lighting(&largs));
		i++;
	}
	return(ret_light);
}

//TODO largs.point = comps->over_point
// Keeping 2 separate values (point & over_point)
// in both structs for now, for debugging & fine-tuning

t_rgb	shade_hit(t_world *w, t_comps *comps)
{
	t_largs	largs;
	bool	two_lights;

	two_lights = MULTILIGHT_ALLOWED;
	if (two_lights == true)
		return(shade_hit_double(w, comps));
	largs.material = comps->object->m;
	largs.light = w->light[0];
	largs.point = comps->over_point;
	largs.eyev = comps->eyev;
	largs.normalv = comps->normalv;
	largs.in_shadow = is_shadowed(w, 0, comps->over_point);
	return (lighting(&largs));
}

t_rgb	color_at(t_world *w, t_ray *r)
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
	comps = prepare_computations(ht, r);
	free(ht);
	xs[0].object = NULL;
	return (shade_hit(w, &comps));
}

bool	is_shadowed(t_world *world, int i, t_tuple point)
{
	t_tuple			v;
	float			distance;
	t_tuple 		direction;
	t_ray			r;
	t_intersection	*xs;
	t_intersection *ht;

	v = tsub(world->light[i].position, point);
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
