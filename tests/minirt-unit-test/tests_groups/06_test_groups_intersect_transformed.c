/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_test_groups_intersect_transformed.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/19 19:41:47 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "groups_tests.h"

int test_groups_intersect_transformed(void)
{
	int				i;
	t_shape			g;
	t_shape			s;
	t_intersection	*xs;

	g = group();
	set_transform(&g, scaling(2, 2, 2));
	s = sphere();
	set_transform(&s, translation(5, 0, 0));
	add_child(&g, &s);
	g.saved_ray = ray(point(10, 0, -10), vector(0, 0, 1));
	xs = intersect(&g, g.saved_ray);
	i = 0;
	while (xs[i].object)
		i++;
	if (i != 2)
		return (-1);
	return (0);
}
