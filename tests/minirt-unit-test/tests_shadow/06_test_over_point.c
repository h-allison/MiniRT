/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_test_over_point.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:52:32 by smargine          #+#    #+#             */
/*   Updated: 2025/09/10 17:10:08 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow_tests.h"
#include "libunit.h"

int test_over_point(void)
{
	t_ray			r;
	t_shape			s;
	t_comps			c;
	t_intersection	i;

	r = ray(point(0, 0, -5), vector(0, 0, 1));
	s = sphere();
	s.transform = mmultfree(translation(0, 0, 1), s.transform);
	s.invtrans = minvert(s.transform, 4);
	i = intersection(5, &s);
	c = prepare_computations(&i, &r);
	if (c.over_point.z < -EPSILON/2 && c.point.z > c.over_point.z)
	{
		free_matrix(s.transform, 4);
		return (0);
	}
	free_matrix(s.transform, 4);
	return (-1);
}
