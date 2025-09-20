/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_test_groups_object_normal.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/20 16:32:49 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "groups_tests.h"

int test_groups_object_normal(void)
{
	t_shape			g1;
	t_shape			g2;
	t_shape			s;
	t_tuple			n;

	g1 = group();
	set_transform(&g1, rotation_y(M_PI / 2));
	g2 = group();
	set_transform(&g2, scaling(1, 2, 3));
	add_child(&g1, &g2);
	s = sphere();
	set_transform(&s, translation(5, 0, 0));
	add_child(&g2, &s);
	n = normal_at(&s, point(1.7321 ,1.1547, -5.5774));
	if (!fisequal(n.x, 0.2857) || !fisequal(n.y, 0.4286) || !fisequal(n.z, -0.8571))
		return (-1);
	return (0);
}
