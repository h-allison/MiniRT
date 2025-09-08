/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shading_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:30:13 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/08 16:24:10 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	shade_hit(t_world *w, t_comps *comps)
{
	t_largs	largs;

	largs.material = comps->object->m;
	largs.light = w->light[0];
	largs.point = comps->point;
	largs.eyev = comps->eyev;
	largs.normalv = comps->normalv;
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
		return (color(0, 0, 0));
	free(ht);
	comps = prepare_computations(xs, r);
	xs[0].object = NULL;
	return (shade_hit(w, &comps));
}
