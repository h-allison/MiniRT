/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_test_over_point.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:52:32 by smargine          #+#    #+#             */
/*   Updated: 2025/09/12 13:29:30 by hallison         ###   ########.fr       */
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
	set_transform(&s, translation(0, 0, 1));
	i = intersection(5, &s);
	c = prepare_computations(&i, &r);
	if (c.over_point.z < -EPSILON/2 && c.point.z > c.over_point.z)
	{
		return (free_matrices_and_ret(&s, 0));
	}
	return (free_matrices_and_ret(&s, -1));
}
