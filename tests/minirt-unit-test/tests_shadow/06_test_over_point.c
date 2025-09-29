/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_test_over_point.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 02:51:08 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/25 00:31:41 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow_tests.h"
#include "libunit.h"

int test_over_point(void)
{
	t_ray			r;
	t_shape			*s;
	t_comps			c;
	t_intersection	i;

	r = ray(point(0, 0, -5), vector(0, 0, 1));
	s = sphere();
	set_transform(s, translation(0, 0, 1));
	i = intersection(5, s);
	c = prepare_computations(&i, &r, NULL);
	free_shape(s);
	if (c.over_point.z < -EPSILON/2 && c.point.z > c.over_point.z)
	{
		return (0);
	}
	return (-1);
}
