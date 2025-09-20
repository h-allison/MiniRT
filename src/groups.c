/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:44:04 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/20 19:04:28 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_child(t_shape *g, t_shape *s)
{
	int		i;
	t_shape	**temp;

	i = 0;
	if (!g->group)
		g->group = malloc(2 * sizeof(t_shape *));
	else
	{
		while (g->group[i])
			i++;
		temp = malloc((i + 2) * sizeof(t_shape *));
		i = 0;
		while (g->group[i])
		{
			temp[i] = g->group[i];
			i++;
		}
		free(g->group);
		g->group = temp;
	}
	g->group[i] = s;
	g->group[i + 1] = NULL;
	s->parent = g;
	return ;
}

t_tuple	world_to_object(t_shape *s, t_tuple point)
{
	if (s->parent)
		point = world_to_object(s->parent, point);
	return (tmatrixmult(s->invtrans, point));
}

t_tuple	normal_to_world(t_shape *s, t_tuple norm)
{
	norm = tmmultfree(mtranspose(s->invtrans, 4), norm);
	norm.w = 0;
	norm = tnorm(norm);
	if (s->parent)
		norm = normal_to_world(s->parent, norm);
	return (norm);
}
