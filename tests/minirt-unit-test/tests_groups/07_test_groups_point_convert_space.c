/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_test_groups_point_convert_space.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/21 03:54:50 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "groups_tests.h"

int test_groups_point_convert_space(void)
{
	t_shape			g1;
	t_shape			g2;
	t_shape			s;
	t_tuple			p;

	g1 = group();
	set_transform(&g1, rotation_y(M_PI / 2));
	g2 = group();
	set_transform(&g2, scaling(2, 2, 2));
	add_child(&g1, &g2);
	s = sphere();
	set_transform(&s, translation(5, 0, 0));
	add_child(&g2, &s);
	p = world_to_object(&s, point(-2, 0, -10));
	if (!fisequal(p.x, 0) || !fisequal(p.y, 0) || !fisequal(p.z, -1))
		return (-1);
	free_shape(&g1);
	return (0);
}
