/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shading_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:30:13 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/09 14:40:39 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	shade_hit(t_world *w, t_comps *comps)
{
	t_largs	largs;

	largs.material = comps->object->m;
	largs.light = w->light[0];
	largs.point = comps->over_point;
	largs.eyev = comps->eyev;
	largs.normalv = comps->normalv;
	largs.in_shadow = is_shadowed(w, comps->over_point);
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

bool	is_shadowed(t_world *world, t_tuple point)
{
	t_tuple			v;
	float			distance;
	t_tuple 		direction;
	t_ray			r;
	t_intersection	*xs;
	t_intersection *ht;

	v = tsub(world->light->position, point);
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
