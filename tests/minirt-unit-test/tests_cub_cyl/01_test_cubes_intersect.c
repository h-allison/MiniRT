/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_cubes_intersect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/22 15:53:27 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_cyl_tests.h"

int test_cubes_intersect(void)
{
	t_shape			c;
	t_ray			r;
	t_intersection	*xs;

	c = cube();
	r = ray(point(5, 0.5, 0), vector(-1, 0, 0));
	xs = local_intersect_cube(&c, r);
	if (xs[0].t != 4 || xs[1].t != 6)
		return (-1);
	xs[0].object = NULL;
	r = ray(point(-5, 0.5, 0), vector(1, 0, 0));
	xs = local_intersect_cube(&c, r);
	if (xs[0].t != 4 || xs[1].t != 6)
		return (-1);
	xs[0].object = NULL;
	r = ray(point(0.5, 5, 0), vector(0, -1, 0));
	xs = local_intersect_cube(&c, r);
	if (xs[0].t != 4 || xs[1].t != 6)
		return (-1);
	xs[0].object = NULL;
	r = ray(point(0.5, -5, 0), vector(0, 1, 0));
	xs = local_intersect_cube(&c, r);
	if (xs[0].t != 4 || xs[1].t != 6)
		return (-1);
	xs[0].object = NULL;
	r = ray(point(0.5, 0, 5), vector(0, 0, -1));
	xs = local_intersect_cube(&c, r);
	if (xs[0].t != 4 || xs[1].t != 6)
		return (-1);
	xs[0].object = NULL;
	r = ray(point(0.5, 0, -5), vector(0, 0, 1));
	xs = local_intersect_cube(&c, r);
	if (xs[0].t != 4 || xs[1].t != 6)
		return (-1);
	xs[0].object = NULL;
	r = ray(point(0, 0.5, 0), vector(0, 0, 1));
	xs = local_intersect_cube(&c, r);
	if (xs[0].t != -1 || xs[1].t != 1)
		return (-1);
	xs[0].object = NULL;
	free_shape(&c);
	return (0);
}
