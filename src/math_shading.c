/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_shading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:25:23 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/03 13:09:39 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// TODO tnorm(), can it be removes?

t_tuple	normal_at(t_sphere s, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;
	float	**m;

	object_point = tmmultfree(minvert(s.transform, 4), world_point);
	object_normal = tsub(object_point, s.origin);
	m = mtransposefree(minvert(s.transform, 4), 4);
	world_normal = tmmultfree(m, object_normal);
	world_normal.w = 0;
	return (tnorm(world_normal));
}
