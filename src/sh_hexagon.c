/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hexagon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:39 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 19:46:00 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_shape	*hexagon_corner(void)
{
	t_shape	*corner;

	corner = sphere();
	corner->m->color = color(0, 0, 0);
	corner->m->diffuse = 0.8;
	corner->m->ambient = 0.7;
	corner->m->specular = 0.2;
	corner->m->reflective = 1;
	set_transform(corner, mmultfree(translation(0, 0, 1),
			scaling(0.25, 0.25, 0.25)));
	return (corner);
}

static t_shape	*hexagon_edge(void)
{
	t_shape	*edge;
	float	**t;

	edge = cylinder();
	edge->minimum = 0;
	edge->maximum = 1;
	edge->m->color = color(0, 0, 0);
	edge->m->diffuse = 0.8;
	edge->m->ambient = 0.7;
	edge->m->specular = 0.2;
	edge->m->reflective = 1;
	t = scaling(0.25, 1, 0.25);
	t = mmultfree(rotation_z(-(M_PI / 2)), t);
	t = mmultfree(rotation_y(-(M_PI / 6)), t);
	t = mmultfree(translation(0, 0, -1), t);
	set_transform(edge, t);
	return (edge);
}

static t_shape	*hexagon_side(void)
{
	t_shape	*side;
	t_shape	*corner;
	t_shape	*edge;

	corner = hexagon_corner();
	edge = hexagon_edge();
	side = group();
	add_child(side, corner);
	add_child(side, edge);
	return (side);
}

t_shape	*hexagon(void)
{
	t_shape	*hex;
	t_shape	**side;
	int		n;

	side = malloc(6 * sizeof(t_shape));
	if (!side)
		exit(1);
	n = 0;
	hex = group();
	while (n < 6)
	{
		side[n] = hexagon_side();
		side[n]->transform = mmultfree(rotation_y(n * M_PI / 3),
				side[n]->transform);
		free_matrix(side[n]->invtrans, 4);
		side[n]->invtrans = minvert(side[n]->transform, 4);
		add_child(hex, side[n]);
		n++;
	}
	return (hex);
}
