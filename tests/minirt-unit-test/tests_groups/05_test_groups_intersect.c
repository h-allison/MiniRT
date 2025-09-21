/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_test_groups_intersect.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/21 03:48:41 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "groups_tests.h"

int test_groups_intersect(void)
{
	int				i;
	float			prev_t;
	t_shape			g;
	t_shape			s1;
	t_shape			s2;
	t_shape			s3;
	t_intersection	*xs;

	g = group();
	s1 = sphere();
	s2 = sphere();
	set_transform(&s2, translation(0, 0, -3));
	s3 = sphere();
	set_transform(&s3, translation(5, 0, 0));
	add_child(&g, &s1);
	add_child(&g, &s2);
	add_child(&g, &s3);
	g.saved_ray = ray(point(0, 0, -5), vector(0, 0, 1));
	xs = local_intersect_group(&g);
	i = 0;
	prev_t = FLT_MIN;
	while (xs[i].object)
	{
		if (xs[i].t < prev_t)
			return (-1);
		prev_t = xs[i].t;
		i++;
	}
	if (xs[0].object != &s2 || xs[1].object != &s2)
		return (-1);
	if (xs[2].object != &s1 || xs[3].object != &s1)
		return (-1);
	if (i != 4)
		return (-1);
	free_shape(&g);
	return (0);
}
