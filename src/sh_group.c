/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_group.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:49:31 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 18:12:35 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*group(void)
{
	t_shape	*g;

	g = malloc(sizeof(t_shape));
	g->parent = NULL;
	g->group = NULL;
	g->triangle = NULL;
	g->transform = create_id_matrix();
	g->invtrans = minvert(g->transform, 4);
	g->local_normal_at = local_normal_at_group;
	g->local_intersect = local_intersect_group;
	g->m = material();
	return (g);
}

t_tuple	local_normal_at_group(t_shape *s, t_tuple local_point)
{
	(void)s;
	(void)local_point;
	ft_putstr_fd("local normal at group. this shouldn't happen!!", 2);
	exit(0);
}

t_intersection	*local_intersect_group(t_shape *s, t_ray r)
{
	int				i;
	t_intersection	*xs;

	if (!s->group || !s->group[0])
		return (intersections(intersection(0, NULL), intersection(0, NULL)));
	i = 0;
	while (s->group[i])
	{
		xs = intersect(s->group[i], r);
		i++;
	}
	sort_intersections(xs);
	return (xs);
}
