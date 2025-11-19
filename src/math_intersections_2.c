/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_intersections_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:56:16 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 18:52:08 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	swap_xs(t_intersection *a, t_intersection *b)
{
	float		tmp_t;
	t_shape		*tmp_o;

	tmp_t = a->t;
	tmp_o = a->object;
	a->t = b->t;
	a->object = b->object;
	b->t = tmp_t;
	b->object = tmp_o;
	return ;
}

void	sort_intersections(t_intersection *xs)
{
	int		i;

	i = 0;
	while (xs[i + 1].object)
	{
		if (xs[i].t > xs[i + 1].t)
		{
			swap_xs(&xs[i], &xs[i + 1]);
			i = 0;
		}
		else
			i++;
	}
	return ;
}

t_intersection	*intersect_world(t_world *w, t_ray *r)
{
	int				i;
	t_intersection	*xs;

	xs = NULL;
	i = 0;
	while (w->s[i])
	{
		xs = intersect(w->s[i], *r);
		i++;
	}
	return (xs);
}

/* ABSTRACT FUNCTIONV */

t_tuple	normal_at(t_shape *s, t_tuple world_point)
{
	t_tuple	local_point;
	t_tuple	local_normal;

	local_point = world_to_object(s, world_point);
	local_normal = s->local_normal_at(s, local_point);
	return (normal_to_world(s, local_normal));
}

t_comps	prepare_computations(t_intersection *ht, t_ray *r, t_intersection *xs)
{
	t_comps	comps;

	comps.t = ht->t;
	comps.object = ht->object;
	comps.point = position(*r, comps.t);
	comps.eyev = tneg(r->direction);
	comps.normalv = normal_at(comps.object, comps.point);
	comps.reflectv = reflect(r->direction, comps.normalv);
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = tneg(comps.normalv);
	}
	else
		comps.inside = false;
	comps.over_point = tadd(comps.point, (tmult(comps.normalv, OFFSET)));
	comps.under_point = tsub(comps.point, (tmult(comps.normalv, OFFSET)));
	prepare_n(&comps, ht, xs);
	return (comps);
}
