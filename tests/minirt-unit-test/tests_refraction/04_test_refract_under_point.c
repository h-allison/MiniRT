/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_test_refract_under_point.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:02:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/23 03:00:17 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"

int test_refract_under_point(void)
{
	t_shape 		*s;
	t_ray			r;
	t_intersection	it;
	t_intersection	*xs;
	t_comps			comps;

	r = ray(point(0, 0, -5), vector(0, 0, 1));
	s = glass_sphere();
	set_transform(s, translation(0, 0, 1));
	it = intersection(5, s);
	xs = intersections(it, it);
	comps = prepare_computations(&it, &r, xs);
	if (comps.under_point.z > OFFSET && comps.point.z < comps.under_point.z)
	{
		free_shape(s);
		return (0);
	}
	return (-1);
}
