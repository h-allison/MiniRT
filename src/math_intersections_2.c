/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_intersections_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:56:16 by hallison          #+#    #+#             */
/*   Updated: 2025/09/08 18:20:44 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	*intersect_world(t_world *w, t_ray *r)
{
	int				i;
	t_intersection	*xs;

	i = 0;
	while (w->s[i].transform)
	{
		xs = intersect(&w->s[i], *r);
		i++;
	}
	return (xs);
}

t_comps	prepare_computations(t_intersection *i, t_ray *r)
{
	t_comps	comps;

	comps.t = i->t;
	comps.object = i->object;
	comps.point = position(*r, comps.t);
	comps.eyev = tneg(r->direction);
	comps.normalv = normal_at(comps.object, comps.point);
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = tneg(comps.normalv);
	}
	else
		comps.inside = false;
	return (comps);
}
