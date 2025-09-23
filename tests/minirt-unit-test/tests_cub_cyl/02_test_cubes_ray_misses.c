/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_test_cubes_ray_misses.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/23 03:28:43 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_cyl_tests.h"

int test_cubes_ray_misses(void)
{
	t_shape			*c;
	t_ray			r;
	t_intersection	*xs;

	c = cube();
	r = ray(point(-2, 0, 0), vector(0.2673, 0.05345, 0.8018));
	xs = local_intersect_cube(c, r);
	if (xs[0].t != 0 && !xs[0].object)
		return (-1);
	xs[0].object = NULL;
	c->saved_ray = ray(point(0, -2, 0), vector(0.8018, 0.2673, 0.5345));
	xs = local_intersect_cube(c, r);
	if (xs[0].t != 0 && !xs[0].object)
		return (-1);
	xs[0].object = NULL;
	c->saved_ray = ray(point(0, 0, -2), vector(0.5345, 0.8018, 0.2673));
	xs = local_intersect_cube(c, r);
	if (xs[0].t != 0 && !xs[0].object)
		return (-1);
	xs[0].object = NULL;
	c->saved_ray = ray(point(2, 0, 2), vector(0, 0, -1));
	xs = local_intersect_cube(c, r);
	if (xs[0].t != 0 && !xs[0].object)
		return (-1);
	xs[0].object = NULL;
	c->saved_ray = ray(point(0, 2, 2), vector(0, -1, 0));
	xs = local_intersect_cube(c, r);
	if (xs[0].t != 0 && !xs[0].object)
		return (-1);
	xs[0].object = NULL;
	c->saved_ray = ray(point(2, 2, 0), vector(-1, 0, 0));
	xs = local_intersect_cube(c, r);
	if (xs[0].t != 0 && !xs[0].object)
		return (-1);
	xs[0].object = NULL;
	free_shape(c);
	return (0);
}
